#include <iostream>
#include <utility>

// 独占式智能指针简化实现
template<typename T>
class Unique_ptr {
public:
    // 构造函数：接收裸指针，默认初始化为空指针
    explicit Unique_ptr(T* ptr = nullptr) : m_ptr_(ptr) {
        std::cout << "Unique_ptr 构造,指针地址： " << m_ptr_<< std::endl;
    }

    // 析构函数：释放资源（核心！ RAII机制）
    ~Unique_ptr() {
        if(m_ptr_) {
            delete m_ptr_;
            m_ptr_ = nullptr;
            std::cout << "Unique_ptr 析构，释放内存" << m_ptr_ <<std::endl;
        }
    }

    // 禁用拷贝构造函数
    Unique_ptr(const Unique_ptr &other) = delete;

    // 禁止拷贝赋值
    Unique_ptr &operator=(const Unique_ptr &other) = delete;

    // 移动构造
    Unique_ptr(Unique_ptr&& other) noexcept : m_ptr_(other.m_ptr_){
        other.m_ptr_ = nullptr;
        std::cout << "Unique_ptr 移动构造，转移指针地址： " << m_ptr_ << std::endl;
    }

    // 移动赋值
    Unique_ptr& operator=(Unique_ptr&& other) noexcept {
        if(this != &other) {
            if(m_ptr_) {
                delete m_ptr_;
            }
            m_ptr_ = other.m_ptr_;
            other.m_ptr_ = nullptr;
            std::cout << "Unique_ptr 移动赋值，转移指针地址： " << m_ptr_ << std::endl;
        }
        return *this;
    }

    T& operator*() const {
        if(!m_ptr_) {
            throw std::runtime_error("Dereferencing null pointer");
        }

        return *m_ptr_;
    }

    T* operator->() const {
        return m_ptr_;
    }

private:
    T *m_ptr_;
};

int main(int argc, char *argv[]) {
    Unique_ptr<int> ptr1(new int(5));
    std::cout << "ptr1 value: " << *ptr1 << std::endl;

    Unique_ptr<int> ptr2 = std::move(ptr1);

    return 0;
}