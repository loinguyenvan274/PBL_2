#include "nguoi.h"

nguoi::nguoi(const string &hoVaTenDV, const string &maDV, const thoiGianNTN &ngaySinhDV) : hoVaTen(hoVaTenDV), ma(maDV), ngaySinh(ngaySinhDV) {}

void nguoi::cDanhTinh(const string &hoVaTenDV, const string &maDV, const thoiGianNTN &ngaySinhDV)
{
    hoVaTen = hoVaTenDV;
    ma = maDV;
    ngaySinh = ngaySinhDV;
}
void nguoi::cHoVaTen(const string &hoVaTenDV) { hoVaTen = hoVaTenDV; }
void nguoi::cMa(const string &maDV) { ma = maDV; }
void nguoi::cNgaySinh(const thoiGianNTN &ngaySinhDV) { ngaySinh = ngaySinhDV; }
string nguoi::lHoVaTen() { return hoVaTen; }
string nguoi::lMa() { return ma; }
thoiGianNTN nguoi::lngaySinh() { return ngaySinh; }
bool nguoi::operator==(const nguoi &n)
{
    if (this->ma == n.ma)
        return true;
    return false;
};
nguoi::~nguoi() {}