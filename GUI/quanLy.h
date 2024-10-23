// QuanLy.h
#ifndef _QUANLY
#define _QUANLY

#include <iostream>
#include <string.h>
#define KHONG_TIM_THAY nullptr

// typedef unsigned long long size_t;
using namespace std;

struct NC
{
    bool nghi = true;
    double thoiGianLam;
    string duocPhanCong;
};
struct dienNuoc
{
    double dien;
    double nuoc;
};
struct thoiGianNT
{
    int ngay;
    int thang;
};
struct thoiGianNTN
{
    int ngay;
    int thang;
    int nam;
};
struct thoiGianGPG
{
    int gio;
    int phut;
    int giay;
};

template <typename T>
class QuanLy
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
    QuanLy(const size_t & = 0);
    QuanLy(const size_t &, const T &);
    T &operator[](size_t) const;
    T &operator=(const T &);
    QuanLy<T> &operator=(const QuanLy<T> &);
    const T *lDCDau() const;
    const T *lDCCuoi() const;

    size_t lDoLon() const;
    size_t lSoPhanTu() const;

    const T *tim(const T &) const;

    void xoa(const T *);
    void xoa(const T *, const T *);
    void chen(const T *, const T &);
    void them(const T &);
    ~QuanLy();
};

template <typename T>
QuanLy<T>::QuanLy(const size_t &doLon) : doLon(doLon), soPhanTu(doLon)
{
    conTro = nullptr;
    if (this->doLon > 0)
    {
        conTro = new T[this->doLon];
    }
    if (this->doLon < 0)
        throw -1;
}

template <typename T>
QuanLy<T>::QuanLy(const size_t &doLon, const T &gT) : doLon(doLon), soPhanTu(doLon)
{
    conTro = new T[this->doLon];
    for (size_t i = 0; i < this->doLon; i++)
    {
        conTro[i] = gT;
    }
    if (this->doLon <= 0)
        throw -1;
}

template <typename T>
T &QuanLy<T>::operator[](size_t i) const
{
    if (i >= soPhanTu)
        throw -1;
    return *(conTro + i);
}

template <typename T>
QuanLy<T>::~QuanLy()
{
    delete[] conTro;
}

template <typename T>
const T *QuanLy<T>::lDCDau() const
{
    return conTro;
}

template <typename T>
const T *QuanLy<T>::lDCCuoi() const
{
    return conTro + soPhanTu - 1;
}

template <typename T>
size_t QuanLy<T>::lDoLon() const { return doLon; }

template <typename T>
size_t QuanLy<T>::lSoPhanTu() const { return soPhanTu; }

template <typename T>
void QuanLy<T>::doi(T &phanTu_1, T &phanTu_2)
{
    T tamThoi = phanTu_1;
    phanTu_1 = phanTu_2;
    phanTu_2 = tamThoi;
}

template <typename T>
void QuanLy<T>::capPhat()
{
    if (doLon == 0)
        doLon = 1;
    else
        doLon *= 2;
    T *tamThoi = new T[doLon];

    for (size_t i = 0; i < soPhanTu; i++)
    {
        tamThoi[i] = conTro[i];
    }
    delete[] conTro;
    conTro = tamThoi;
}

template <typename T>
void QuanLy<T>::keoLui(const size_t &viTri)
{
    for (size_t i = viTri; i < soPhanTu - 1; i++)
    {
        doi(conTro[i], conTro[i + 1]);
    }
}

template <typename T>
void QuanLy<T>::dayToi(const size_t &viTri)
{
    if (soPhanTu == doLon)
        capPhat();
    for (size_t i = soPhanTu; i > viTri; i--)
    {
        doi(conTro[i], conTro[i - 1]);
    }
}

template <typename T>
const T *QuanLy<T>::tim(const T &phanTuTim) const
{
    for (size_t i = 0; i < soPhanTu; i++)
    {
        if (this->conTro[i] == phanTuTim)
            return conTro + i;
    }
    return KHONG_TIM_THAY;
}

template <typename T>
void QuanLy<T>::xoa(const T *dCXoa)
{
    if (lDCDau() <= dCXoa && dCXoa <= lDCCuoi())
    {
        keoLui(dCXoa - lDCDau());
        soPhanTu--;
    }
}

template <typename T>
void QuanLy<T>::xoa(const T *dCXoaBatDau, const T *dCXoaKetThuc)
{
    size_t KhoangCach = dCXoaKetThuc - dCXoaBatDau + 1;
    size_t viTriBatDauX = dCXoaBatDau - lDCDau();

    if (dCXoaKetThuc >= dCXoaBatDau && lDCDau() <= dCXoaBatDau && dCXoaKetThuc <= lDCCuoi())
    {
        for (size_t i = viTriBatDauX; i < soPhanTu - KhoangCach; i++)
        {
            doi(conTro[i], conTro[i + KhoangCach]);
        }
        soPhanTu -= KhoangCach;
    }
}

template <typename T>
void QuanLy<T>::chen(const T *dCChen, const T &phanTuThem)
{
    size_t viTri = dCChen - lDCDau();
    if (soPhanTu == doLon)
        capPhat();
    dayToi(viTri);
    conTro[viTri] = phanTuThem;
    soPhanTu++;
}
template <typename T>
void QuanLy<T>::them(const T &phanTuThem)
{
    if (soPhanTu == doLon)
        capPhat();
    conTro[soPhanTu] = phanTuThem;
    soPhanTu++;
}

template <typename T>
QuanLy<T> &QuanLy<T>::operator=(const QuanLy<T> &doiTuongCP)
{

    size_t sPhanTuDTCP = doiTuongCP.lSoPhanTu();
    for (size_t i = 0; i < sPhanTuDTCP; i++)
    {
        if (doLon < sPhanTuDTCP)
            capPhat();

        soPhanTu += (sPhanTuDTCP > soPhanTu) ? 1 : 0;
        conTro[i] = doiTuongCP[i];
    }
    return *this;
}

#endif // _QUANLY
