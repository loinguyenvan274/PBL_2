#include "nhanVien.h"

nhanVien::nhanVien(const string &hoVaTenDV, const string &maDV, const string &ngaySinhDV) : nguoi(hoVaTenDV, maDV, ngaySinhDV)
{

    luongMoiGio = 0;
    moTaCongViec = ""
}
void nhanVien::cThoiGianLam(const int &thoiGian) { thoiGianLam = thoiGian; }
void nhanVien::cMoTaCongViec(const string &) {}
void nhanVien::cthoiGianLam(const int &) {}
thoiGianGPG nhanVien::lThoiGianLam() const {}
string nhanVien::lMoTaCongViec() const {}
int nhanVien::lthoiGianLam() const {}
nhanVien::~nhanVien() {}