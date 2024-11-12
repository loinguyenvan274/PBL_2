#include <iostream>
#include "gui/quanLyGiaoDien.h"
#include "app/QuanLyKTX.h"
#include <random>

Font giaoDien::font26;

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
    giaoDien::font26 = LoadFontEx(dDFileFontChu, 26, const_cast<int *>(vietnameseCodepoints), sizeof(vietnameseCodepoints) / sizeof(int));
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

    Vector<SinhVien> sinhVienKTX = layDuLieu<SinhVien>(dDFileSinhVien);
    Vector<Phong> phongKTX = layDuLieu<Phong>(dDFilePhong);

    QuanLyKTX quanLyKTX;
 
    for (size_t i = 0; i < phongKTX.lSoPhanTu(); i++)
    {
        quanLyKTX.themPhong(phongKTX[i]);
    }
    for (size_t i = 0; i < sinhVienKTX.lSoPhanTu(); i++)
    {
        quanLyKTX.themSinhVien(sinhVienKTX[i]);
    }
   

    khoiTaoCuaSo();

    runApp(quanLyKTX);

    UnloadFont(giaoDien::font26);
    CloseWindow();

    luuDuLieu(dDFileSinhVien, quanLyKTX.lDanhSachSinhVien());

    luuDuLieu(dDFilePhong, quanLyKTX.lDanhSachPhong());

    /*---------------------------------tao case du lieu --------------------------------------*/
    // long soDoiTuong = 1000000;

    // const char *dDfilePhongTest = "test/Phong.csv";

    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::uniform_int_distribution<> dist(0, 32000 - 1);
    // std::uniform_int_distribution<> randomSoNguoiTD(1, 8);
    // std::uniform_int_distribution<> rdsd(100, 99999);
    // std::uniform_int_distribution<> clcs(30, 150);

    // Vector<Phong> phongTest(soDoiTuong);

    // fstream docFile("test/ten.txt", ios::in | ios::app);
    // Vector<string> ten(32000);
    // string tamThoi;
    // long i = 0;
    // while (getline(docFile, tamThoi) && i < 32000)
    // {
    //     ten[i++] = tamThoi;
    // }

    // for (i = 0; i < soDoiTuong; i++)
    // {
    //     string b = to_string(i + soDoiTuong);
    //     b = b.substr(1);
    //     phongTest[i] = Phong("A" + b, randomSoNguoiTD(gen), ten[dist(gen)]);
    //     float sss = rdsd(gen);
    //     phongTest[i].cDienCSDT(sss);
    //     phongTest[i].cDienCSCT(sss + clcs(gen));
    //     sss = rdsd(gen);
    //     phongTest[i].cNuocCSDT(sss);
    //     phongTest[i].cNuocCSCT(sss + clcs(gen));
    // }
    // luuDuLieu(dDFilePhong, phongTest);

    /*----------------------------------end---------------------------------------------------------*/
    return 0;

}
