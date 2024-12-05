#include <iostream>
#include <iomanip> // Để định dạng số thập phân

int main()
{
    for (int i = 1; i <= 100000; i++)
    {
        std::cout << i << "~6~0~Phong quat bi hong~0.000000~0.000000~0.000000~0.000000~1~3000000~ ;" << std::endl;
    }
    std::cout << "A01~4~0~~0.000000~0.000000~0.000000~0.000000~0~1000000~ ;";
    return 0;
}
