#ifndef _MABAM
#define _MABAM
#define _MAX_PHAN_TU 1e6
#include <string>
#include "Vector.h"
#define Size_t unsigned long long

template <typename T>
struct Diem
{
    T DuLieu;
    std::string maBam;
    Diem *tiepTheo;
    Diem() : tiepTheo(nullptr) {}
    Diem(const std::string &maBam, const T &phanTu) : maBam(maBam), DuLieu(phanTu), tiepTheo(nullptr) {}
};

template <typename T>
class BangBam
{
private:
    Diem<T> **mang;
    Size_t khoiLuong;
    Size_t soPhanTu;

    void khoiTao();
    Size_t hamBam(const std::string &) const;

public:
    BangBam(const Size_t & = _MAX_PHAN_TU);
    void themPhanTu(const T &, const std::string &);
    const Vector<T> layCacGiaTri();
    const Vector<T *> layCacPhanTu();
    Diem<T> *timDiem(const std::string &) const;
    T *timPhanTu(const std::string &) const;
    void thayThe(const T &,const std::string &, const std::string &);
    bool xoaPhanTu(const std::string &);
    void xoaTatCa();
    ~BangBam();
};

#include "BangBam.cpp"

#endif