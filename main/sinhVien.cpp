#include "SinhVien.h"

SinhVien::SinhVien(const string &hoVaTenDV, const string &maDV, const thoiGianNTN &ngaySinhDV) : Nguoi(hoVaTenDV, maDV, ngaySinhDV)
{
    ngayBatDauO = {0, 0, 2000};
    maPhong = "";
    thoiGianO = 0;
}
void SinhVien::cNgayBatDauO(const thoiGianNTN &thoiGianDV) { ngayBatDauO = thoiGianDV; }
void SinhVien::cMaPhong(const string &maPhongDV) { maPhong = maPhongDV; }
void SinhVien::cThoiGianO(const int &thoiGianODV) { thoiGianO = thoiGianODV; }
thoiGianNTN SinhVien::lNgayBatDauO() { return ngayBatDauO; }
string SinhVien::lMaPhong() { return maPhong; }
double SinhVien::lThoiGianO() { return thoiGianO; }
void SinhVien::bieuDien()
{
    cout << "Ten: " << hoVaTen << endl;
    cout << "Ma Sinh Vien: " << ma << endl;
    cout << "Ngay Sinh: " << ngaySinh.ngay << "/" << ngaySinh.thang << "/" << ngaySinh.nam << endl;
    cout << "ma Phong" << maPhong << endl;
}

SinhVien::~SinhVien() {}
