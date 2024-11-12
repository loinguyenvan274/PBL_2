#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int *> a(5);
    int b = 10;
    a[0] = &b;
    b = 9;
    cout << *a[0];

    return 0;
}