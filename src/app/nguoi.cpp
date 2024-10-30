#include "Nguoi.h"

Nguoi::Nguoi(const string &hoVaTenDV, const string &maDV, const string &ngaySinhDV) : hoVaTen(hoVaTenDV), ma(maDV), ngaySinh(ngaySinhDV) {}

void Nguoi::cDanhTinh(const string &hoVaTenDV, const string &maDV, const string &ngaySinhDV)
{
    hoVaTen = hoVaTenDV;
    ma = maDV;
    ngaySinh = ngaySinhDV;
}
void Nguoi::cHoVaTen(const string &hoVaTenDV) { hoVaTen = hoVaTenDV; }
void Nguoi::cMa(const string &maDV) { ma = maDV; }
void Nguoi::cNgaySinh(const string &ngaySinhDV) { ngaySinh = ngaySinhDV; }
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