#include <iostream>
#include "QuanLy.h"
#include "Nguoi.h"
#include "SinhVien.h"
#include "Phong.h"
using namespace std;
int main()
{
    QuanLy<SinhVien> sVBK(8);

    sVBK[0].cDanhTinh("Phan Van L", "102231000", {5, 6, 1996});
    sVBK[1].cDanhTinh("Phan Van B", "102230324", {7, 9, 1995});
    sVBK[2].cDanhTinh("Tran Van C", "102230111", {8, 5, 2000});
    sVBK[3].cDanhTinh("Le Thi D", "102230222", {9, 12, 1998});
    sVBK[4].cDanhTinh("Hoang Van E", "102230333", {14, 3, 2001});
    sVBK[5].cDanhTinh("Nguyen Thi F", "102230444", {22, 7, 1997});
    sVBK[6].cDanhTinh("Phan Van G", "102230555", {1, 1, 1990});
    sVBK[7].cDanhTinh("Tran Thi H", "102230666", {25, 4, 1999});
    sVBK.chen(sVBK.lDCCuoi(), SinhVien("Nguyen Thanh Hau", "102230000", {23, 7, 2005}));
    sVBK.chen(sVBK.lDCCuoi(), SinhVien("Nguyen Van Loi", "102230026", {7, 9, 2005}));

    QuanLy<Phong> phongKTX(1);
    phongKTX[0].cMaPhong("001");
    phongKTX.chen(phongKTX.lDCDau(), Phong("002"));
    phongKTX.chen(phongKTX.lDCDau(), Phong("003", 5, "PHONG BAN VA HOI HAM"));
    phongKTX.chen(phongKTX.lDCDau(), Phong("003", 6, "PHONG GIANH CHO CON GAI"));

    for (int i = 0; i < sVBK.lSoPhanTu(); i++)
    {
        cout << "\n\n";
        sVBK[i].bieuDien();
    }
    cout << "\n\n";
    cout << "Thong Tin Phong";
    for (int i = 0; i < phongKTX.lSoPhanTu(); i++)
    {
        cout << "\n\n";
        phongKTX[i].hienThiThongTin();
    }
    return 0;
}