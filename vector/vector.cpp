#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[])
{
    // 初始化方式
    std::vector<int> v1;    // 空vector，初始容量0
    std::vector<int> v2(5,10);  // 5个元素，每个值为10
    std::vector<int> v3 = {1,2,3,4};    // 列表初始化(c++11起支持)
    std::vector<int> v4(v3.begin(), v3.end());  // 通过迭代器区间拷贝初始化

    // 常用操作
    v1.push_back(1);    //尾部添加元素：v1 = [1]
    v1.push_back(2);    //尾部添加元素：v1 = [1,2]
    v1.push_back(3);     //尾部删除元素：v1 = [1,2,3]

    std::cout << "v1元素个数：" << v1.size() << std::endl;   //获取元素个数
    std::cout << "v1容量大小：" << v1.capacity() << std::endl;  //底层分配的内存容量（通常≥size，比如可能是4）
    std::cout << "第二个元素:" << v1.at(1) << std::endl;    // 安全访问（越界会抛异常）：3
    std::cout << "第二个元素:" << v1[1] << std::endl;   // 随机访问：2（下标从0开始）

    v1.pop_back();  //尾部删除元素：v1 = [1,2]
    v1.insert(v1.begin() + 1, 5); //在第二个位置插入5：v1 = [1,5,2]
    v1.erase(v1.begin() + 1);   //删除第二个位置元素：v1 = [1,2]

    // 遍历元素
    std::cout << "下标遍历";
    for (int i = 0; i < v1.size(); i++) {
        std::cout << v1[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "迭代器遍历: ";
    for (std::vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "范围for遍历：";
    for(int num : v1) {
        std::cout << num << " ";
    }
    std::cout << std ::endl;

    // 常用算法(需要包含<algorithm>)
    v3.push_back(2);
    sort(v3.begin(), v3.end()); //排序：v3 = [1,2,2,3,4]
    auto it = std::find(v3.begin(), v3.end(), 2); //查找元素2
    if(it != v3.end()) {
        std::cout << "找到元素2，下标： " << it - v3.begin() << std::endl;  // 输出1
    }

    // 清空与释放内存
    v1.clear(); //清空元素，但不释放内存(size=0，capacity不变)
    std::vector<int>().swap(v1); //交换清空并释放内存(size=0，capacity=0)

    return 0;
}