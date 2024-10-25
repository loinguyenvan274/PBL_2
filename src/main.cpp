#include <iostream>

#include "app/quanLyGiaoDien.h"

#include "app/giaoDienChinh.h"
#include "app/giaoDienPhong.h"
// #include "giaoDien.h"
Font giaoDien::font28;

// đọc dữ liệu từ file và trả về mảng hai chiều (dòng chứa các đối tượng , cột chứa các thuộc tính của đối tương)
template <typename type>
QuanLy<type> lay(const char *duongDan)
{
    docGhiFile docGhi(duongDan);
    QuanLy<QuanLy<string>> dSDoc = docGhi.docData();

    QuanLy<type> qL(dSDoc.lSoPhanTu());
    for (int i = 0; i < dSDoc.lSoPhanTu(); i++)
    {
        qL[i].cThongTin(dSDoc[i]);
    }
    return qL;
}
// lưu dữ liệu từ danh sách quản lý
template <typename type>
void luu(const char *duongDan, const QuanLy<type> &danhSach)
{
    docGhiFile docGhi(duongDan);

    QuanLy<QuanLy<string>> dSGhi(danhSach.lSoPhanTu());

    for (int i = 0; i < dSGhi.lSoPhanTu(); i++)
    {
        dSGhi[i] = danhSach[i].lThongTin();
    }

    docGhi.ghiData(dSGhi);
}

int main()
{
    const char *tieuDeChuongTrinh = "Quản Lý Sinh Viên Ký Túc Xá [ PBL2 Nguyễn Văn Lợi 102230026 - Nguyễn Thanh Hậu 102230013 ]";

    const char *dDFileFontChu = "assets/roboto.ttf";
    const char *dDFileSinhVien = "data/sinhVien.csv";
    const char *dDFilePhong = "data/Phong.csv";
    const char *dDFileTien = "data/tien.csv";

    InitWindow(1480, 880, tieuDeChuongTrinh);
    SetWindowPosition(45, 45);

    giaoDien::font28 = LoadFontEx(dDFileFontChu, 26, const_cast<int *>(vietnameseCodepoints), sizeof(vietnameseCodepoints) / sizeof(int));

    QuanLy<SinhVien> sinhVienKTX = lay<SinhVien>(dDFileSinhVien);
    QuanLy<Phong> phongKTX = lay<Phong>(dDFilePhong);
    cout << "\n\n\n\nhere";
    quanLyGiaoDien gD(&sinhVienKTX, &phongKTX);

    // thêm giao chính vào ngăn xếp (lớp trên cùng sẽ được biểu diễn)

    while (!WindowShouldClose())
    {
        gD.capNhatTT();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        gD.bieuDien();

        EndDrawing();
    }

    // lưu file
    luu(dDFileSinhVien, sinhVienKTX);
    luu(dDFilePhong, phongKTX);

    UnloadFont(giaoDien::font28);
    CloseWindow();
    return 0;
}