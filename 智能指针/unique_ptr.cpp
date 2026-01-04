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

void func() {
    std::unique_ptr<Test> uptr(new Test(10));
    uptr->show();
    // 模拟异常场景
    if(true){
        throw std::runtime_error("模拟异常");
    }
    // 即使抛出异常，uptr 的析构函数仍会执行，不会内存泄漏
}

int main(int argc, char *argv[])
{
    std::unique_ptr<Test> uptr1(new Test(1));
    uptr1->show();

    // 禁止拷贝（编译报错）
    // std::unique_ptr<Test> uptr2 = uptr1;

    std::unique_ptr<Test> uptr3 = std::move(uptr1); // 转移所有权
    if(uptr1 == nullptr) {
        std::cout << "uptr1为空指针" << std::endl;
    }
    uptr3->show();

    // 数组管理版本
    std::unique_ptr<Test[]> uptr4(new Test[2]{Test(2), Test(3)});
    uptr4[0].show();
    uptr4[1].show();

    // c++14及以上推荐使用方法
    auto uptr5 = std::make_unique<Test>(5);
    uptr5->show();

    auto uptr6 = std::make_unique<Test[]>(5);

    std::unique_ptr<Test> uptr7;
    std::cout << "ptr7" << std::endl;
    uptr7.reset(new Test(7));
    uptr7->show();

    try{
        func();
    }
    catch (const std ::exception &e) {
        std::cout << "捕获异常" << e.what() << std :: endl;
    }

    return 0;
}