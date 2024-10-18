#include <iostream>
#include "sinhVien.cpp"
#include "nguoi.cpp"
#include "coBan.cpp"
#include <stdexcept>
// #include <vector>
using namespace std;

int main()
{

    int n = 10; // cout << "here" << endl;
    Vector<sinhVien> a(n);

    a[1].cDanhTinh("Phan Van B", "102230324", {7, 9, 1995});
    a[2].cDanhTinh("Tran Van C", "102230111", {8, 5, 2000});
    a[3].cDanhTinh("Le Thi D", "102230222", {9, 12, 1998});
    a[4].cDanhTinh("Hoang Van E", "102230333", {14, 3, 2001});
    a[5].cDanhTinh("Nguyen Thi F", "102230444", {22, 7, 1997});
    a[6].cDanhTinh("Phan Van G", "102230555", {1, 1, 1990});
    a[7].cDanhTinh("Tran Thi H", "102230666", {25, 4, 1999});

    a[8].cDanhTinh("Le Van I", "102230777", {30, 8, 2002});
    // a[9].cDanhTinh("Hoang Thi J", "102230888", {19, 11, 1985});

    a.chen(4, sinhVien("Nguyen Van K", "102230999", {12, 10, 2003}));
    a.tim(a[5]);
    // a.xoa(a[5]);

    //     .cDanhTinh("Nguyen Van K", "102230999", {12, 10, 2003});
    // a[11].cDanhTinh("Phan Van L", "102231000", {5, 6, 1996});
    // a[12].cDanhTinh("Tran Van M", "102231111", {21, 2, 2004});
    // a[13].cDanhTinh("Le Thi N", "102231222", {18, 12, 1989});
    // a[14].cDanhTinh("Hoang Van O", "102231333", {9, 3, 2000});
    // a[15].cDanhTinh("Nguyen Thi P", "102231444", {15, 9, 1993});
    // a[16].cDanhTinh("Phan Van Q", "102231555", {3, 8, 1991});
    // a[17].cDanhTinh("Tran Thi R", "102231666", {28, 11, 1992});
    // a[18].cDanhTinh("Le Van S", "102231777", {6, 4, 1988});
    // a[19].cDanhTinh("Hoang Thi T", "102231888", {14, 1, 1994});

    for (int i = 0; i < a.lSoPhanTu(); ++i)
    {
        cout << "sinh vien thu: " << i << endl;
        a[i].bieuDien();
        cout << endl
             << endl;
    }
    return 0;
}