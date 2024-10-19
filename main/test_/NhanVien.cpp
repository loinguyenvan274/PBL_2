#include "nhanVien.h"

nhanVien::nhanVien(const string &hoVaTenDV, const string &maDV, const thoiGianNTN &ngaySinhDV) : nguoi(hoVaTenDV, maDV, ngaySinhDV)
{
    ngayBatDauO = {0, 0, 2000};
    maPhong = "";
    thoiGianO = 0;
}
void nhanVien::cThoiGianLam(const int &thoiGian) { thoiGianLam = thoiGian; }
void nhanVien::cMoTaCongViec(const string &) {}
void nhanVien::cthoiGianLam(const int &) {}
thoiGianGPG nhanVien::lThoiGianLam() const {}
string nhanVien::lMoTaCongViec() const {}
int nhanVien::lthoiGianLam() const {}
nhanVien::~nhanVien() {}