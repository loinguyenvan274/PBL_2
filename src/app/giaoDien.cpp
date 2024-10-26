#include "giaoDien.h"
const string giaoDien::float_string(const float &soThuc)
{
    ostringstream ss;
    ss << std::defaultfloat << soThuc;
    return ss.str();
}