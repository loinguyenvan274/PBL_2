
// #include <string>
// #include <iostream>
// #include "gui/quanLyGiaoDien.h"
// #include "gui/giaoDienChinh.h"
// #include "raylib.h"
// using namespace std;
// int main()
// {
//     InitWindow(1480, 880, "làm quen");
//     SetWindowPosition(45, 45);
//     quanLyGiaoDien dD;

//     dD.them(new giaoDienChinh(dD));

//     while (!WindowShouldClose())
//     {
//         dD.capNhatTT();
//         BeginDrawing();
//         ClearBackground(RAYWHITE);
//         dD.bieuDien();
//         EndDrawing();
//     }

//     CloseWindow();
//     return 0;
// }

#include <iostream>
#include "QuanLy.h"
#include "Nguoi.h"
#include "SinhVien.h"
// #include "Phong.h"
#include "docGhiFile.h"
using namespace std;
int main()
{

    docGhiFile docGhi("sinhVien.csv");

    QuanLy<QuanLy<string>> ddSSVBK = docGhi.docData();

    QuanLy<SinhVien> sVBK(ddSSVBK.lSoPhanTu());
    for (int i = 0; i < ddSSVBK.lSoPhanTu(); i++)
    {
        sVBK[i].cThongTin(ddSSVBK[i]);
    }

    // sVBK.them(SinhVien("maikow jason", "99999999"));
    // sVBK[2].cHoVaTen("Tran-Dang-Huy");
    // sVBK[2].cThoiGianO(8.7);

    sVBK.xoa(sVBK.tim(SinhVien("", "102230444")));
    for (int i = 0; i < sVBK.lSoPhanTu(); i++)
    {

        cout << "\n\n";
        cout << i << endl;
        sVBK[i].bieuDien();
    }

    // Ghi
    QuanLy<QuanLy<string>> dSSVBK(sVBK.lSoPhanTu());
    for (int i = 0; i < sVBK.lSoPhanTu(); i++)
    {
        dSSVBK[i] = sVBK[i].lThongTin();
    }

    docGhi.ghiData(dSSVBK);

    // QuanLy<Phong> phongKTX(1);
    // phongKTX[0].cMaPhong("001");
    // phongKTX.chen(phongKTX.lDCDau(), Phong("002"));
    // phongKTX.chen(phongKTX.lDCDau(), Phong("003", 5, "PHONG BAN VA HOI HAM"));
    // phongKTX.chen(phongKTX.lDCDau(), Phong("003", 6, "PHONG GIANH CHO CON GAI"));

    // cout << "\n\n";
    // cout << "Thong Tin Phong";
    // for (int i = 0; i < phongKTX.lSoPhanTu(); i++)
    // {
    //     cout << "\n\n";
    //     phongKTX[i].hienThiThongTin();
    // }
    return 0;
}
