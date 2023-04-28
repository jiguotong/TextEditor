#include <iostream>
#include <exception>
#include "testForCallback.h"
using namespace std;

const string errorCode = "I don't like this number.";

// 定义自己的异常处理类
class MyException : public logic_error {
public:
    explicit MyException(const string& s = errorCode) :logic_error(s) {}
};

typedef int (*p_fun)(const int a, const int b);
int Add(const int a, const int b);
int operateFun(const int, const int, p_fun);


void TestExceptions() {
    int input;
    while (1) {
        try {
            cout << "Please type in a number between 1 and 100." << endl;
            cin >> input;
            if (!cin.good()) {
                cin.clear();
                cin.ignore();
                throw invalid_argument("The input should be a number!");
            }
            if (input >= 100)
                throw length_error("The input should be less than 100!");
            if (input < 0)
                throw out_of_range("The input should be Non-negative number!");
            if (input == 44)
                throw MyException();
            cout << "Your input is " << input << ". there isn't error\n";
        }
        catch (invalid_argument e) {
            cout << "*********************************" << endl;
            cout << "There is an invalid argument error occured" << endl;
            cout << "info:" << e.what() << endl;
            cout << "*********************************" << endl;
        }
        catch (length_error e) {
            cout << "*********************************" << endl;
            cout << "There is a length error occured" << endl;
            cout << "info:" << e.what() << endl;
            cout << "*********************************" << endl;
        }
        catch (out_of_range e) {
            cout << "*********************************" << endl;
            cout << "There is an out of range error occured" << endl;
            cout << "info:" << e.what() << endl;
            cout << "*********************************" << endl;
        }
        catch (MyException e) {
            cout << "*********************************" << endl;
            cout << "There is an error occured" << endl;
            cout << "info:" << e.what() << endl;
            cout << "*********************************" << endl;
        }
        catch (exception e) {
            cout << "*********************************" << endl;
            cout << "There is an undefined error occured" << endl;
            cout << "info:" << e.what() << endl;
            cout << "*********************************" << endl;
        }
        cout << endl;
    }
}

void TestFunPointer() {
    int result = Add(5, 7);
    std::cout << result << std::endl;

    int (*ptr)(const int, const int);
    ptr = Add;
    result = ptr(8, 9);
    std::cout << result << std::endl;

    p_fun fun;
    fun = &Add;
    result = fun(10, 5);
    std::cout << result << std::endl;

    std::cout << operateFun(19, 27, fun) << std::endl;
}

void TestCallBack() {
    B b;
    b.excute();
}


int main() {
    //TestExceptions();
    //TestFunPointer();
    TestCallBack();
    return 0;
}

// test for callback
int Add(const int a, const int b) {
    return a + b;
}
int operateFun(const int a, const int b, p_fun ptr) {
    return ptr(a, b);
}
