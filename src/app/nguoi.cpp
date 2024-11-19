#include "Nguoi.h"

Nguoi::Nguoi(const string &hoVaTenDV, const string &maDV, const string &ngaySinhDV) : hoVaTen(hoVaTenDV), ma(maDV), ngaySinh(ngaySinhDV)
{
    sDT = "";
    gioiTinh = "";
}

void Nguoi::cDanhTinh(const string &hoVaTenDV, const string &maDV, const string &ngaySinhDV)
{
    hoVaTen = hoVaTenDV;
    ma = maDV;
    ngaySinh = ngaySinhDV;
}
void Nguoi::cHoVaTen(const string &hoVaTenDV) { hoVaTen = hoVaTenDV; }
void Nguoi::cMa(const string &maDV) { ma = maDV; }
void Nguoi::cNgaySinh(const string &ngaySinhDV) { ngaySinh = ngaySinhDV; }
void Nguoi::cSDT(const string &sDT) { this->sDT = sDT; }
void Nguoi::cGioiTinh(const string &gioiTinh) { this->gioiTinh = gioiTinh; }
string Nguoi::lSDT() const { return sDT; }
string Nguoi::lGioiTinh() const { return gioiTinh; }
string Nguoi::lHoVaTen() const { return hoVaTen; }
string Nguoi::lMa() const { return ma; }
string Nguoi::lngaySinh() const { return ngaySinh; }
bool operator==(const Nguoi &nguoi1, const Nguoi &nguoi2)
{
    if (nguoi1.ma == nguoi2.ma)
        return true;
    return false;
};
Nguoi::~Nguoi() {}