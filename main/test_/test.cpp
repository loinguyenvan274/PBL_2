#include <iostream>
#include <vector>
using namespace std;
class animal
{
protected:
    int a;

public:
    animal(int a) : a(a) {}
    void print()
    {
        std::cout << a;
        std::cout << "hello";
    }
};
class dog : public animal
{
protected:
    int a;
    int b;

public:
    dog(int a) : animal(a) {}
    void print()
    {
        std::cout << a;
        std::cout << "meo meo ";
    }
};
int a = 9;
const int *f()
{

    return &a;
}
int main()
{
    // int *const b = f();
    throw -1;
    // cout << b << endl;
    // b = 6;
    // cout << b;
    return 0;
}