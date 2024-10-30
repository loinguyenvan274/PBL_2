#include <iostream>

int a = 5;
using namespace std;
int &soNguyen()
{
    return a;
}
int main()
{
    soNguyen() = 6;
    cout << a;
    return 0;
}