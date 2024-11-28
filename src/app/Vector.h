// QuanLy.h
#ifndef _VECTOR
#define _VECTOR

#include <iostream>
#include <string.h>
#define KHONG_TIM_THAY nullptr

typedef unsigned long long size_t;
using namespace std;

#include <iostream>
#include <string>
using namespace std;

struct NTN
{
    int ngay;
    int thang;
    int nam;
    NTN()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        this->nam = 1900 + ltm->tm_year;
        this->thang = 1 + ltm->tm_mon;
        this->ngay = ltm->tm_mday;
    }
    int laySoNgayTrongThang(int thang, int nam) const
    {
        if (thang == 4 || thang == 6 || thang == 9 || thang == 11)
            return 30;
        if (thang == 2)
        {
            if ((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0))
                return 29;
            else
                return 28;
        }
        return 31;
    }

    string chuyenSangString() const
    {
        return to_string(ngay) + "/" + to_string(thang) + "/" + to_string(nam);
    }
    NTN &operator+=(int soThang)
    {
        thang += soThang;
        while (thang > 12)
        {
            thang -= 12;
            nam++;
        }
        while (thang < 1)
        {
            thang += 12;
            nam--;
        }

        int soNgayTrongThang = laySoNgayTrongThang(thang, nam);
        if (ngay > soNgayTrongThang)
            ngay = soNgayTrongThang;

        return *this;
    }
    bool operator<(const NTN &khac) const
    {
        if (nam != khac.nam)
            return nam < khac.nam;
        if (thang != khac.thang)
            return thang < khac.thang;
        return ngay < khac.ngay;
    }
    bool operator>(const NTN &khac) const
    {
        return khac < *this;
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
#endif 