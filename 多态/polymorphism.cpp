#include <iostream>

/*
核心定位: 多态（Polymorphism）是 C++ 面向对象编程的核心特性
本质：一个接口，多种实现
分类：静态多态（编译期）和动态多态（运行期）
*/

// ===================== 一、静态多态（编译期多态）=====================
// 实现方式：函数重载、模板
// 特点：编译器在编译阶段确定调用哪个函数

// 函数重载示例
void print(int value) {
    std::cout << "整数: " << value << std::endl;
}

void print(double value) {
    std::cout << "浮点数: " << value << std::endl;
}

void print(const std::string& value) {
    std::cout << "字符串: " << value << std::endl;
}

// ===================== 二、动态多态（运行期多态）=====================
// 实现方式：虚函数（virtual）+ 继承 + 父类指针/引用
// 特点：程序运行时才确定调用哪个函数

// 基类：定义虚函数接口
class Animal {
public:
    // 虚函数：允许子类重写，实现多态
    virtual void makeSound() const {
        std::cout << "动物发出声音" << std::endl;
    }
    
    // 虚析构函数：确保子类对象正确释放
    virtual ~Animal() {
        std::cout << "Animal 析构函数" << std::endl;
    }
    
    // 普通函数：不会触发多态
    void eat() const {
        std::cout << "动物在吃东西" << std::endl;
    }
};

// 子类1：重写虚函数
class Dog : public Animal {
public:
    // override 关键字：明确表示重写父类虚函数（C++11）
    void makeSound() const override {
        std::cout << "汪汪汪！" << std::endl;
    }
    
    ~Dog() override {
        std::cout << "Dog 析构函数" << std::endl;
    }
};

// 子类2：重写虚函数
class Cat : public Animal {
public:
    void makeSound() const override {
        std::cout << "喵喵喵！" << std::endl;
    }
    
    ~Cat() override {
        std::cout << "Cat 析构函数" << std::endl;
    }
};

// ===================== 三、多态的核心条件演示 =====================
void demonstratePolymorphism() {
    std::cout << "\n===== 多态演示：通过父类指针调用虚函数 =====" << std::endl;
    
    // 条件1：继承关系 ✓（Animal -> Dog/Cat）
    // 条件2：虚函数 ✓（makeSound 是虚函数）
    // 条件3：父类指针指向子类对象 ✓
    
    Animal* animal1 = new Dog();   // 父类指针指向子类对象
    Animal* animal2 = new Cat();  // 父类指针指向子类对象
    
    // ✅ 触发多态：运行时根据实际对象类型调用对应函数
    animal1->makeSound();  // 输出：汪汪汪！（调用 Dog::makeSound）
    animal2->makeSound();  // 输出：喵喵喵！（调用 Cat::makeSound）
    
    // ✅ 通过引用也能触发多态
    Dog dog;
    Cat cat;
    Animal& ref1 = dog;
    Animal& ref2 = cat;
    ref1.makeSound();  // 输出：汪汪汪！
    ref2.makeSound();  // 输出：喵喵喵！
    
    delete animal1;
    delete animal2;
}

// ===================== 四、对比：多态 vs 非多态 =====================
void comparePolymorphism() {
    std::cout << "\n===== 对比：多态 vs 非多态 =====" << std::endl;
    
    Dog dog;
    Cat cat;
    
    // ❌ 非多态：直接用对象调用，静态绑定（编译时确定）
    std::cout << "\n直接对象调用（非多态）：" << std::endl;
    dog.makeSound();  // 静态绑定，但结果相同（因为对象类型明确）
    cat.makeSound();
    
    // ✅ 多态：通过指针/引用调用，动态绑定（运行时确定）
    std::cout << "\n通过指针调用（多态）：" << std::endl;
    Animal* ptr1 = &dog;
    Animal* ptr2 = &cat;
    ptr1->makeSound();  // 动态绑定，运行时确定调用 Dog::makeSound
    ptr2->makeSound();  // 动态绑定，运行时确定调用 Cat::makeSound
    
    // 普通函数不会触发多态
    std::cout << "\n普通函数调用（非多态）：" << std::endl;
    ptr1->eat();  // 调用 Animal::eat（静态绑定）
    ptr2->eat();  // 调用 Animal::eat（静态绑定）
}

// ===================== 五、实际应用场景：统一接口处理不同对象 =====================
void processAnimals(Animal* animals[], int count) {
    std::cout << "\n===== 实际应用：统一接口处理不同对象 =====" << std::endl;
    for (int i = 0; i < count; i++) {
        animals[i]->makeSound();  // 多态：根据实际对象类型调用对应函数
    }
}

int main(int argc, char* argv[]) {
    std::cout << "===== 静态多态：函数重载 =====" << std::endl;
    print(10);           // 调用 print(int)
    print(3.14);         // 调用 print(double)
    print("Hello");      // 调用 print(const std::string&)
    
    // 动态多态演示
    demonstratePolymorphism();
    comparePolymorphism();
    
    // 实际应用场景
    Animal* animals[] = {new Dog(), new Cat(), new Dog()};
    processAnimals(animals, 3);
    
    // 清理内存
    for (int i = 0; i < 3; i++) {
        delete animals[i];
    }
    
    return 0;
}
