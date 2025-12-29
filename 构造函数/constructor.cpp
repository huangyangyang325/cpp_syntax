#include <iostream>
#include <cstring>

class MyString {
public:
    // ===================== 1. 默认构造函数 (Default Constructor) =====================
    // 定义：无参数/所有参数都有默认值的构造函数，编译器会自动生成（若未自定义任何构造函数）
    // 作用：创建空对象，初始化成员变量
    MyString() : m_data_(new char[1]()), m_size_(0) {
        std::cout << " 默认构造函数 " << std::endl;
    }

    // ===================== 2. 隐式构造函数 (Implicit Constructor) =====================
    // 定义：无explicit关键字的单参数构造函数，允许隐式类型转换（风险：可能意外转换）
    // 注意：多参数构造函数不会触发隐式转换，仅单参数（含默认参数）会
    MyString(const char* str) : m_size_(strlen(str)) {
        m_data_ = new char[m_size_ + 1];
        strcpy(m_data_, str);
        std::cout << " 隐式构造函数 " << m_data_ << std::endl;
    }

    // ===================== 3. 显式构造函数 (Explicit Constructor) =====================
    // 定义：加explicit关键字的单参数构造函数，禁止隐式类型转换（推荐：避免意外行为）
    explicit MyString(size_t len) : m_size_(len) {
        m_data_ = new char[m_size_ + 1];
        std::cout << " 显式构造函数 " << m_size_ << std::endl;
    }

    // ===================== 4. 浅拷贝构造函数 (Shallow Copy Constructor) =====================
    // 定义：仅拷贝指针地址，不拷贝指针指向的堆内存（编译器默认生成的拷贝构造函数就是浅拷贝）
    // 风险：多个对象共享同一块堆内存，析构时重复释放导致崩溃
    // MyString(const MyString& other) : m_data_(other.m_data_), m_size_(other.m_size_) {
    //     std::cout << " 浅拷贝构造函数,共享内存： " << (void*)m_data_ << std::endl;
    // }

     // ===================== 5. 深拷贝构造函数 (Deep Copy Constructor) =====================
    // 定义：手动分配新的堆内存，拷贝原对象的实际数据，而非仅拷贝指针
    // 作用：解决浅拷贝的内存共享问题，每个对象拥有独立内存
    // （注：实际开发中会用深拷贝替代浅拷贝，此处为演示保留浅拷贝，需注释掉浅拷贝才能运行深拷贝）
    MyString(const MyString& other) {
        m_size_ = other.m_size_;
        m_data_ = new char[m_size_ + 1];
        strcpy(m_data_, other.m_data_);
        std::cout << " 深拷贝构造函数,other内存" << (void*)other.m_data_ << " 独立内存： " << (void*)m_data_ << std::endl;
    }

    // ===================== 6. 移动构造函数 (Move Constructor) =====================
    // 定义：接收右值引用（T&&）的构造函数，“窃取”原对象的资源（堆内存），而非拷贝
    // 作用：避免不必要的深拷贝，提升性能（尤其针对大对象）
    MyString(MyString&& other) noexcept : m_data_(other.m_data_), m_size_(other.m_size_) {
        // 关键：将原对象的指针空置，避免析构时释放已转移的资源
        other.m_data_ = nullptr;
        other.m_size_ = 0;
        std::cout << "[移动构造函数] 转移资源：" << (void*)m_data_ << "other内存 :" << (void*)other.m_data_<< std::endl;
    }

    // 辅助函数：打印字符串内容
    void print() const {
        std::cout << "字符串内容：" << (m_data_ ? m_data_ : "空") 
                  << " | 内存地址：" << (void*)m_data_ << "\n";
    }

private:
    char* m_data_;
    size_t m_size_;
};

int main(int argc, char* argv[]) {
    std::cout << "===== 1. 默认构造函数 =====" << std::endl;
    MyString s1;
    s1.print();
    std::cout << "\n===== 2. 隐式构造函数（允许隐式转换） =====" << std::endl;
    MyString s2("hello");
    s2.print();
    std::cout << "\n===== 3. 显式构造函数（禁止隐式转换） =====" << std::endl;
    MyString s3(10);
    s3.print();
    std::cout << "\n===== 4. 深拷贝构造函数（独立内存） =====" << std::endl;
    MyString s4 = s2;
    s4.print();
    std::cout << "\n===== 5. 移动构造函数（资源转移） =====" << std::endl;
    MyString s5 = std::move(s2);
    s5.print();

    return 0;
}