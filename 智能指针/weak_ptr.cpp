#include <iostream>
#include <memory>

class A{
    std::shared_ptr<int> ptr_;
    A()
    {
        std::cout << "A 构造函数调用" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    return 0;
}