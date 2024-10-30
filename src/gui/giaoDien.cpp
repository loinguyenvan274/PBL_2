#include "giaoDien.h"
#include <cmath>
giaoDien::giaoDien(QuanLyKTX &quanLyKTX) : quanLyKTX(quanLyKTX) {}
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