#include <iostream>

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
int main()
{
    animal a(4);
    animal b(5);
    dog d(3);
    a = d;
    a.print();
    return 0;
}