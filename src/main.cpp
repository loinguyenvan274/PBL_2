#include <iostream>
#include "app/quanLyGiaoDien.h"

Font giaoDien::font28;

const char *dDFileFontChu = "assets/roboto.ttf";
const char *dDFileSinhVien = "data/sinhVien.csv";
const char *dDFilePhong = "data/Phong.csv";

template <typename Type>
QuanLy<Type> layDuLieu(const char *duongDan)
{
    docGhiFile docGhi(duongDan);
    QuanLy<QuanLy<std::string>> dSDoc = docGhi.docData();

    QuanLy<Type> qL(dSDoc.lSoPhanTu());
    for (int i = 0; i < dSDoc.lSoPhanTu(); i++)
    {
        qL[i].cThongTin(dSDoc[i]);
    }
    return qL;
}

template <typename Type>
void luuDuLieu(const char *duongDan, const QuanLy<Type> &danhSach)
{
    docGhiFile docGhi(duongDan);
    QuanLy<QuanLy<std::string>> dSGhi(danhSach.lSoPhanTu());

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
    SetWindowPosition(400, 200);
    giaoDien::font28 = LoadFontEx(dDFileFontChu, 26, const_cast<int *>(vietnameseCodepoints), sizeof(vietnameseCodepoints) / sizeof(int));
}

void runApp(QuanLy<SinhVien> &sinhVienKTX, QuanLy<Phong> &phongKTX)
{
    quanLyGiaoDien gD(&sinhVienKTX, &phongKTX);

    while (!WindowShouldClose())
    {
        gD.capNhatTT();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        gD.bieuDien();
        EndDrawing();
    }
}

int main()
{
    khoiTaoCuaSo();

    QuanLy<SinhVien> sinhVienKTX = layDuLieu<SinhVien>(dDFileSinhVien);
    QuanLy<Phong> phongKTX = layDuLieu<Phong>(dDFilePhong);

    runApp(sinhVienKTX, phongKTX); // chạy chương trình đồ họa

    luuDuLieu(dDFileSinhVien, sinhVienKTX);
    luuDuLieu(dDFilePhong, phongKTX);

    UnloadFont(giaoDien::font28);
    CloseWindow();
    return 0;
}
