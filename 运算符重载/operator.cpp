#include <iostream>

/*
核心定位: operator 是 C++ 关键字，用于重载（重定义）内置运算符，
让自定义类型（如类 / 结构体）支持 +/-/=/<< 等运算符操作
（比如让两个自定义的 Point 类对象用 p1 + p2 计算坐标和）。
本质是 “以函数形式实现运算符逻辑”，分为成员函数重载和全局函数重载两类。
*/

// 成员函数重载（推荐用于单目 / 赋值类运算符）
class Point {
public:
    Point(int x, int y) : x_(x), y_(y) {}

    // 前置递增运算符：++p1，返回引用（高效，无临时对象）
    Point& operator++() {
        this->x_++;
        this->y_++;
        return *this;
    }

    // 后置递增运算符：p1++，返回旧值的副本（有临时对象开销）
    // 注意：参数 int 仅用于区分前置和后置，不实际使用
    Point operator++(int) {
        Point old = *this;  // 保存旧值
        this->x_++;
        this->y_++;
        return old;  // 返回旧值（临时对象）
    }

    // 成员函数重载（双目）：左操作数必须是当前类对象
    // 用途：Point + Point
    Point operator+(const Point& other) const {
        return Point(x_ + other.x_, y_ + other.y_);
    }

    // ===================== 友元函数（friend）的作用 =====================
    // 问题：全局函数无法直接访问类的私有成员（x_、y_）
    // 解决：在类内声明 friend，授予全局函数访问私有成员的权限
    // 
    // friend 的作用：
    // 1. 允许全局函数访问类的私有/受保护成员
    // 2. 不影响类的封装性（友元是"受控的例外"）
    // 3. 常用于运算符重载（如流运算符 <<、>> 必须用全局函数）
    // 
    // 注意：friend 声明在类内，但函数定义在类外（全局作用域）
    friend Point operator+(const Point& lhs, int delta);
    friend Point operator+(int delta, const Point& rhs);
    
    // 流运算符 << 必须用全局函数重载（因为左操作数是 ostream，不是 Point）
    // 需要 friend 才能访问私有成员 x_、y_
    friend std::ostream& operator<<(std::ostream& os, const Point& p);

    void print() const {
        std::cout << "Point x " << x_ << " y " << y_ << std::endl;
    }

private:
    int x_;
    int y_;
};

// ===================== 全局函数重载（需要 friend 才能访问私有成员）=====================
// 全局函数重载：Point + int
// 注意：这里能访问 lhs.x_ 和 lhs.y_，是因为在 Point 类中声明了 friend
// 如果没有 friend 声明，这里会编译错误：无法访问私有成员
Point operator+(const Point& lhs, int delta) {
    return Point(lhs.x_ + delta, lhs.y_ + delta);  // ✅ 可以访问私有成员（因为有 friend）
}

// 全局函数重载：int + Point
Point operator+(int delta, const Point& rhs) {
    return Point(rhs.x_ + delta, rhs.y_ + delta);  // ✅ 可以访问私有成员（因为有 friend）
}

// ===================== 流运算符重载（典型友元函数应用）=====================
// 流运算符 << 必须用全局函数，因为左操作数是 std::ostream，不是 Point
// 需要 friend 才能访问 Point 的私有成员
std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "Point(" << p.x_ << ", " << p.y_ << ")";  // ✅ 可以访问私有成员（因为有 friend）
    return os;  // 返回流引用，支持链式调用：cout << p1 << p2
}

/*
// ===================== 如果没有 friend 会怎样？=====================
// 错误示例：如果删除 friend 声明，下面的代码会编译失败
Point operator+(const Point& lhs, int delta) {
    // ❌ 编译错误：'x_' 是 Point 类的私有成员，无法访问
    // return Point(lhs.x_ + delta, lhs.y_ + delta);
    
    // 解决方案1：使用公有接口（如果有的话）
    // return Point(lhs.getX() + delta, lhs.getY() + delta);
    
    // 解决方案2：在类内声明 friend（推荐，性能更好）
}
*/

int main(int argc, char* argv[]) {
    Point p1(1, 2);
    
    std::cout << "===== 前置递增 ++p1 =====" << std::endl;
    ++p1;  // 调用 operator++()，直接修改p1并返回引用
    p1.print();
    
    std::cout << "\n===== 后置递增 p1++ =====" << std::endl;
    Point p2 = p1++;  // 调用 operator++(int)，返回旧值
    std::cout << "p1（递增后）: ";
    p1.print();
    std::cout << "p2（旧值）: ";
    p2.print();
    
    std::cout << "\n===== 成员函数重载：Point + Point =====" << std::endl;
    Point p3 = p1 + p2;  // 成员函数，左操作数必须是 Point
    p3.print();

    std::cout << "\n===== 全局函数重载：Point + int =====" << std::endl;
    Point p4 = p3 + 5;   // 右操作数是基础类型，由全局函数处理
    p4.print();

    std::cout << "\n===== 全局函数重载：int + Point =====" << std::endl;
    Point p5 = 10 + p4;  // 左操作数不是 Point，只能走全局函数
    p5.print();

    std::cout << "\n===== 友元函数应用：流运算符 << =====" << std::endl;
    std::cout << "使用流运算符输出: " << p5 << std::endl;  // 使用友元函数重载的 <<
    std::cout << "链式调用: " << p1 << " + " << p2 << " = " << p3 << std::endl;

    return 0;
}

