#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
int main()
{

    float tienDien = 0;
    float mucBacDien[] = {50, 100, 200,300,400,500};
    float luongDienTT = 500;
    float giaTienDien[] = {1678, 1734, 2014, 2536, 2834, 2834};

    if (mucBacDien[0] < luongDienTT)
    {
        int j;
        tienDien += mucBacDien[0] * giaTienDien[0];
        for (j = 1; j < 5 && mucBacDien[j] < luongDienTT; j++)
        {
            tienDien += (mucBacDien[j] - mucBacDien[j - 1]) * giaTienDien[j];
        }
        tienDien += (luongDienTT - mucBacDien[j - 1]) * giaTienDien[j];
    }
    else
    {
        tienDien = luongDienTT * giaTienDien[0];
    }

    // tienDien += (mucBacDien[0] < luongDienTT) ? mucBacDien[0] * giaTienDien[0] : luongDienTT * giaTienDien[0];
    // for (j = 1; j < 5; j++)
    // {
    //     if (mucBacDien[j] < luongDienTT)
    //         tienDien += (mucBacDien[j] - mucBacDien[j - 1]) * giaTienDien[j];
    // }
    // tienDien += (j == 1) ? 0 : (luongDienTT - mucBacDien[j - 1]) * giaTienDien[j];

    cout << tienDien;
    return 0;
}
