#include <iostream>
#include <utility>
#include <mutex>    // 可选，用于线程安全的引用计数

// 第一步：定义引用计数控制块
template<typename T>
struct RefCount {
    T* resource;    // 指向实际资源
    int ref_count;  // 引用计数
    // 构造函数
    RefCount(T* ptr) : resource(ptr), ref_count(1) {
        std::cout << "RefCount 构造函数调用" << std::endl;
    }
    // 析构函数
    ~RefCount() {
        delete resource;
        std::cout << "资源已释放" << std::endl;
    }
    // 增加引用计数
    void add_ref() {
        ref_count++;
    }
    // 减少引用计数并返回当前计数
    bool release_ref() {
        ref_count--;
        return ref_count == 0;
    }
};

// 第二步：实现自定义 shared_ptr 类
template<typename T>
class SharedPtr {
public:
    // 1. 构造函数：接收裸指针
    explicit SharedPtr(T* ptr = nullptr) : m_ptr_(ptr) {
        if(ptr) {
            cb = new RefCount<T>(ptr);
        } else {
            cb = nullptr;
        }
        std::cout << "SharedPtr 构造函数调用" << std::endl;
    }
    // 2. 拷贝构造函数：共享资源，计数+1
    SharedPtr(const SharedPtr<T>& other) {
        m_ptr_ = other.m_ptr_;
        cb = other.cb;
        if (cb) {
            cb->add_ref();  // 引用计数+1
        }
    }

    // 3. 拷贝赋值运算符：先释放当前资源，再共享新资源
    SharedPtr<T>& operator=(const SharedPtr<T>& other) {
        if (this == &other) {  // 防止自赋值
            return *this;
        }

        // 释放当前资源：计数-1，若为0则销毁控制块
        if (cb && cb->release_ref()) {
            delete cb;
        }

        // 共享新资源
        m_ptr_ = other.m_ptr_;
        cb = other.cb;
        if (cb) {
            cb->add_ref();
        }

        return *this;
    }

    // 4. 析构函数：计数-1，若为0则销毁控制块
    ~SharedPtr() {
        if (cb && cb->release_ref()) {
            delete cb;  // 控制块析构时会释放资源
        }
    }

    // 5. 重载解引用和箭头运算符：模拟原生指针行为
    T& operator*() const { return *m_ptr_; }
    T* operator->() const { return m_ptr_; }

    // 6. 获取引用计数（辅助函数）
    int use_count() const {
        return cb ? cb->ref_count : 0;
    }

    // 7. 判断是否独占资源
    bool unique() const {
        return use_count() == 1;
    }
private:
    T* m_ptr_;
    RefCount<T>* cb;
};

// 测试代码
int main() {
    // 测试1：基本使用
    SharedPtr<int> p1(new int(100));
    std::cout << "p1 引用计数：" << p1.use_count() << std::endl;  // 输出：1
    std::cout << "*p1 = " << *p1 << std::endl;                    // 输出：100

    // 测试2：拷贝构造，计数+1
    SharedPtr<int> p2 = p1;
    std::cout << "p1 引用计数：" << p1.use_count() << std::endl;  // 输出：2
    std::cout << "p2 引用计数：" << p2.use_count() << std::endl;  // 输出：2

    // 测试3：修改资源（共享资源，p1/p2都会看到变化）
    *p2 = 200;
    std::cout << "*p1 = " << *p1 << std::endl;                    // 输出：200

    // 测试4：赋值运算符
    SharedPtr<int> p3(new int(300));
    p3 = p1;
    std::cout << "p3 引用计数：" << p3.use_count() << std::endl;  // 输出：3
    std::cout << "*p3 = " << *p3 << std::endl;                    // 输出：200

    // 测试5：析构时自动释放资源
    {
        SharedPtr<int> p4(new int(400));
        std::cout << "p4 引用计数：" << p4.use_count() << std::endl;  // 输出：1
    }  // p4析构，计数减为0，资源释放（输出"资源已释放"）

    return 0;
}
