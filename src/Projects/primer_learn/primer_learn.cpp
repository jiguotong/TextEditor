// primer_learn.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <ctime>
#include <string>
class Base{
public:
    Base() {
        std::cout << "调用一次不带参的默认构造函数。" << std::endl;
        this->m_value = 100;
        this->arr = new char[10];
    }
    Base(int value) {
        std::cout << "调用一次带参的默认构造函数。" << std::endl;
        this->m_value = value;
        this->arr = new char[10];
    }
    Base(const Base& base){
        std::cout << "调用一次拷贝构造函数。" << std::endl;
        this->arr = new char[10];
        strcpy(this->arr,base.arr);
        this->m_value = base.m_value;
    }
    Base(Base&& base) {
        this->arr = base.arr;
        this->m_value = base.m_value;
        base.arr = nullptr;
        std::cout << "调用一次移动构造函数" << std::endl;
    }
    Base& operator=(const Base& base) {
        std::cout << "调用一次拷贝复制运算。" << std::endl;
        this->arr = new char[10];
        strcpy(this->arr, base.arr);
        this->m_value = base.m_value;
        return *this;
    }
    Base& operator=(Base&& base) {
        this->arr = base.arr;
        base.arr = nullptr;
        std::cout << "调用一次移动构造运算" << std::endl;
        return *this;
    }

    ~Base() {
        delete arr;
        std::cout << "调用一次析构函数" << std::endl;
    }
public:
    int m_value;
    char* arr;
};
Base getBase() {
    Base base(1000);
    base.arr[0] = 'a';
    return base;
}

// 类模板定义
template<typename T>
class Display
{
public:
    Display(T val) :_value(val) {}
    void display() {
        std::cout << _value << std::endl;
    }
private:
    T _value;
};

template <typename T>
int compare(const T& v1, const T& v2) {
    if (v1 < v2)
        return -1;
    if (v2 < v1)
        return 1;
    return 0;
}

template int compare<int>(const int& v1, const int& v2);

void TestClass(){
    //Base base1;
    //base1.m_value = 10;
    //Base base2(100);
    //Base base3;
    //Base base4(base3);
    //Base base5 = base2;
    //clock_t startTime, endTime;
    //startTime = clock();
    ////for (size_t i = 0; i < 1000000; i++)
    ////{
    ////    std::string temp = "hello";
    ////    //Base base6 = base2;
    ////}
    ////endTime = clock();
    ////std::cout << "拷贝初始化Total Time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;

    ////startTime = clock();
    ////for (size_t i = 0; i < 1000000; i++)
    ////{
    ////    std::string temp("hello");
    ////    //Base base7(base2);
    ////}
    ////endTime = clock();
    ////std::cout << "直接初始化Total Time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;

    //Base base6;
    //base6 = base2;
    //Base* base7 = new Base;
    //Base base8(getBase());
    /*Base base9(10000);
    base9 = getBase();
    std::cout << "Hello World!\n";*/
    //delete base7;
}

void Template() {
    // 实例化一个类模板对象
    Display<std::string> d("hello world");
    d.display();

    std::cout << compare<int>(1, 2.4) << std::endl;
}
int main()
{
    Template();
}
