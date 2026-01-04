#include <iostream>
#include <memory>


class Test {
public:
    Test() {
        std::cout << "Test 默认构造函数调用" << std::endl;
    }
    Test(int id) : id_(id) {
        std::cout << "Test 构造函数调用" << std::endl;
    }
    ~Test() {
        std::cout << "Test 析构函数调用" << std::endl;
    }
    void show() {
        std::cout << "Test show id " << id_ <<std::endl;
    }
private:
    int id_;
};

int main(int argc, char *argv[])
{
    // 初始化
    std::shared_ptr<Test> ptr1(new Test(1));
    std::cout << "ptr1引用计数: " << ptr1.use_count() << std::endl;

    //拷贝（计数+1）
    std::shared_ptr<Test> ptr2 = ptr1;
    std::cout << "ptr1引用计数: " << ptr1.use_count() << std::endl;
    std::cout << "ptr2引用计数: " << ptr2.use_count() << std::endl;

    //重置
    ptr1.reset();
    std::cout << "ptr1重置后引用计数: " << ptr1.use_count() << std::endl;
    std::cout << "ptr2引用计数: " << ptr2.use_count() << std::endl;

    ptr2 = nullptr; // 释放资源
    std::cout << "ptr2置空后引用计数: " << ptr2.use_count() << std::endl;

    // c++14及以上推荐使用方法
    auto ptr3 = std::make_shared<Test>(3);
    ptr3->show();
    std::cout << "ptr3引用计数: " << ptr3.use_count() << std::endl;

    return 0;
}