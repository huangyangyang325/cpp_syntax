#include <iostream>

// 模板声明：template <模板参数列表>
template <typename T> // T是类型参数（可替换任意类型：如int/string/自定义类）
class MyContainer {
public:
    // 1.构造函数：使用模板参数T
    // MyContainer(T val) : m_data_(val) {}
    MyContainer(T val);

    // 2.成员函数：返回值/参数使用T
    // T getValue() const {return m_data_;}
    T getValue() const;
    void setValue(T val) {m_data_ = val;}

private:
    T m_data_;
};

// 类外定义：必须重复template <typename T>,且类名写MyContainer<T>
template <typename T>
MyContainer<T>::MyContainer(T val) : m_data_(val) {}

template <typename T>
T MyContainer<T>::getValue() const {
    return m_data_;
}

int main(int argc, char *argv[])
{
    // 1.实例化：将T替换为int
    MyContainer<int> int_container(10);
    std::cout << "int container value " << int_container.getValue() << std::endl;

    // 2.实例化：将T替换成std::string
    MyContainer<std::string> string_container("hello");
    std::cout << "string container value " << string_container.getValue() << std::endl;

    return 0;
}