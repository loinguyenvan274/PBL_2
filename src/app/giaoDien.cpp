#include "giaoDien.h"
#include <cmath>
const string giaoDien::float_string(const float &soThuc, const int &soSoLamTron)
{
    float sThuc = double(long((soThuc * pow(10.0, soSoLamTron) / pow(10.0, soSoLamTron))));
    ostringstream ss;
    ss << std::defaultfloat << sThuc;
    return ss.str();
}