#include "sinhVien.h"

sinhVien::sinhVien(const string &hoVaTenDV, const string &maDV, const thoiGianNTN &ngaySinhDV) : nguoi(hoVaTenDV, maDV, ngaySinhDV)
{
    ngayBatDauO = {0, 0, 2000};
    maPhong = "";
    thoiGianO = 0;
}
void sinhVien::cNgayBatDauO(const thoiGianNTN &thoiGianDV) { ngayBatDauO = thoiGianDV; }
void sinhVien::cMaPhong(const string &maPhongDV) { maPhong = maPhongDV; }
void sinhVien::cThoiGianO(const int &thoiGianODV) { thoiGianO = thoiGianODV; }
thoiGianNTN sinhVien::lNgayBatDauO() { return ngayBatDauO; }
string sinhVien::lMaPhong() { return maPhong; }
double sinhVien::lThoiGianO() { return thoiGianO; }
void sinhVien::bieuDien()
{
    cout << "Ten: " << hoVaTen << endl;
    cout << "Ma Sinh Vien: " << ma << endl;
    cout << "Ngay Sinh: " << ngaySinh.ngay << "/" << ngaySinh.thang << "/" << ngaySinh.nam << endl;
    cout << "ma Phong" << maPhong << endl;
}

sinhVien::~sinhVien() {}
