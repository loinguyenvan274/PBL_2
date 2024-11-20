#include "giaoDien.h"
#include <cmath>
giaoDien::giaoDien(QuanLyKTX &quanLyKTX, HeThong &heThong) : quanLyKTX(quanLyKTX), heThong(&heThong), chuoiTimSoSanh("") {}
const string giaoDien::floatSangString(const float &soThuc, const int &soSoLamTron)
{
    float sThuc = double(long((soThuc * pow(10.0, soSoLamTron) / pow(10.0, soSoLamTron))));
    ostringstream ss;
    ss << std::defaultfloat << sThuc;
    return ss.str();
}
const float giaoDien::stringSangFloat(const string &chuoi)
{
    if (chuoi == "")
        return 0.0f;
    return stof(chuoi);
}
NutTuyChon::NutTuyChon() : nutBiRangBuot(0) {}
void NutTuyChon::bieuDien()
{
    for (int i = 0; i < dSNut.lSoPhanTu(); i++)
    {
        dSNut[i].bieuDien();
    }
}
void NutTuyChon ::capNhatTT()
{
    for (int i = 0; i < dSNut.lSoPhanTu(); i++)
    {
        dSNut[i].capNhatTT();
        if (dSNut[i].laDuocChon())
        {
            dSNut[i].cTrangThaiChon(false);
            nutBiRangBuot = i;
            for (int j = 0; j < dSNut.lSoPhanTu(); j++)
            {
                dSNut[j].cRangBuoc(false);
            }
        }
        dSNut[nutBiRangBuot].cRangBuoc(true);
    }
}