#include <iostream>
#include <string>

// 分配 + 构造
// 类名* 指针 = new 类名(构造参数); 
// 析构 + 释放
// delete 指针;

// 分配数组 + 调用每个元素的构造
// 类名* 指针 = new 类名[数组大小]{构造参数列表}; 
// 调用每个元素的析构 + 释放数组内存
// delete[] 指针; 

class Person {
public:
    Person(const std::string& name, int age) :name_(name), age_(age) {
        std::cout << "构造函数调用" << std::endl;
    }

    ~Person() {
        std::cout << "析构函数调用" << std::endl;
    }

    void print() const {
        std::cout << "name: " << name_ << " age: " << age_ << std::endl;
    }

private:
    std::string name_;
    int age_;
};

int main(int argc, char* argv[]) {
    // 1. 基础类型动态分配（无构造/析构，但仍需delete）
    int* num = new int(10); // 分配int内存，初始化为10
    std::cout << *num << std::endl;   // 输出10
    delete num;             // 释放内存

    // 单个对象的动态分配 / 释放
    std::string name = "张三";
    Person* p = new Person(name, 20);
    p->print();
    delete p;

    // 分配数组 + 调用每个元素的构造
    Person* peoples = new Person[5]{Person("张三", 20), Person("李四", 21), Person("王五", 22), Person("赵六", 23), Person("孙七", 24)};
    for (int i = 0; i < 5; i++) {
        peoples[i].print();
    }
    delete[] peoples;
    
    return 0;
}