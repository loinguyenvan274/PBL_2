// QuanLy.h
#ifndef _VECTOR
#define _VECTOR

#include <iostream>
#include <string.h>
#define KHONG_TIM_THAY nullptr

typedef unsigned long long size_t;
using namespace std;

struct NTN
{
    int ngay;
    int thang;
    int nam;
    string chuyenSangString() const
    {
        return to_string(ngay) + "/" + to_string(thang) + "/" + to_string(nam);
    }
};

template <typename T>
class Vector
{
private:
    size_t doLon;
    size_t soPhanTu;
    T *conTro;
    void keoLui(const size_t &);
    void dayToi(const size_t &);
    void doi(T &, T &);
    void capPhat();

public:
    Vector(const size_t & = 0);
    Vector(const size_t &, const T &);
    T &operator[](size_t) const;
    T &operator=(const T &);
    Vector<T> &operator=(const Vector<T> &);
    Vector<T> operator+(const Vector<T> &) const;
    const T *lDCDau() const;
    const T *lDCCuoi() const;

    size_t soPhanTuTrung(const T &) const;

    size_t lDoLon() const;
    size_t lSoPhanTu() const;

    T *tim(const T &) const;

    void xoa(const T *);
    void xoa(const size_t &);
    void xoa(const T *, const T *);
    void chen(const T *, const T &);
    void them(const T &);
    ~Vector();
};
#include "Vector.cpp"
#endif // _QUANLY
       // huynh nhu bao nhan\\