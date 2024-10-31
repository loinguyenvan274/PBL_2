#include <iostream>
#include "gui/quanLyGiaoDien.h"
#include "app/QuanLyKTX.h"

Font giaoDien::font28;

const char *dDFileFontChu = "assets/roboto.ttf";
const char *dDFileSinhVien = "data/sinhVien.csv";
const char *dDFilePhong = "data/Phong.csv";

template <typename Type>
const Vector<Type> layDuLieu(const char *duongDan)
{
    docGhiFile docGhi(duongDan);
    Vector<Vector<std::string>> dSDoc = docGhi.docData();

    Vector<Type> qL(dSDoc.lSoPhanTu());
    for (int i = 0; i < dSDoc.lSoPhanTu(); i++)
    {
        qL[i].cThongTin(dSDoc[i]);
    }
    return qL;
}

template <typename Type>
void luuDuLieu(const char *duongDan, const Vector<Type> &danhSach)
{
    docGhiFile docGhi(duongDan);
    Vector<Vector<std::string>> dSGhi(danhSach.lSoPhanTu());

    for (int i = 0; i < dSGhi.lSoPhanTu(); i++)
    {
        dSGhi[i] = danhSach[i].lThongTin();
    }

    docGhi.ghiData(dSGhi);
}

void khoiTaoCuaSo()
{
    const char *tieuDeChuongTrinh = "Quản Lý Sinh Viên Ký Túc Xá [ PBL2 Nguyễn Văn Lợi 102230026 - Nguyễn Thanh Hậu 102230013 ]";
    InitWindow(1480, 880, tieuDeChuongTrinh);
    SetWindowPosition(200, 200);
    giaoDien::font28 = LoadFontEx(dDFileFontChu, 26, const_cast<int *>(vietnameseCodepoints), sizeof(vietnameseCodepoints) / sizeof(int));
}

void runApp(QuanLyKTX &quanLyKTX)
{
    quanLyGiaoDien gD(quanLyKTX);

    while (!WindowShouldClose())
    {
        gD.capNhatTT();
        BeginDrawing();
        ClearBackground(Color{224, 255, 255, 255});
        gD.bieuDien();
        EndDrawing();
    }
}

int main()
{
    khoiTaoCuaSo();

    Vector<SinhVien> sinhVienKTX = layDuLieu<SinhVien>(dDFileSinhVien);
    Vector<Phong> phongKTX = layDuLieu<Phong>(dDFilePhong);

    QuanLyKTX quanLyKTX;
 for (int i = 0; i < phongKTX.lSoPhanTu(); i++)
    {
        // cout <<  << endl;
        quanLyKTX.themPhong(phongKTX[i]);
    }
    for (int i = 0; i < sinhVienKTX.lSoPhanTu(); i++)
    {
        // cout <<  << endl;
        quanLyKTX.themSinhVien(sinhVienKTX[i]);
    }
    runApp(quanLyKTX);


    luuDuLieu(dDFileSinhVien, quanLyKTX.lDanhSachSinhVien());

    luuDuLieu(dDFilePhong, quanLyKTX.lDanhSachPhong());

    UnloadFont(giaoDien::font28);
    CloseWindow();
    return 0;
}
