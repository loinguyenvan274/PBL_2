#ifndef _VECTOR_CPP
#define _VECTOR_CPP
#include "Vector.h"

template <typename T>
Vector<T>::Vector(const size_t &doLon) : doLon(doLon), soPhanTu(doLon)
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
Vector<T>::Vector(const size_t &doLon, const T &gT) : doLon(doLon), soPhanTu(doLon)
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
T &Vector<T>::operator[](size_t i) const
{
    if (i >= soPhanTu)
        throw -1;
    return *(conTro + i);
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] conTro;
}

template <typename T>
const T *Vector<T>::lDCDau() const
{
    return conTro;
}

template <typename T>
const T *Vector<T>::lDCCuoi() const
{
    return conTro + soPhanTu - 1;
}

template <typename T>
size_t Vector<T>::lDoLon() const { return doLon; }

template <typename T>
size_t Vector<T>::lSoPhanTu() const { return soPhanTu; }

template <typename T>
void Vector<T>::doi(T &phanTu_1, T &phanTu_2)
{
    T tamThoi = phanTu_1;
    phanTu_1 = phanTu_2;
    phanTu_2 = tamThoi;
}

template <typename T>
void Vector<T>::capPhat()
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
void Vector<T>::keoLui(const size_t &viTri)
{
    for (size_t i = viTri; i < soPhanTu - 1; i++)
    {
        doi(conTro[i], conTro[i + 1]);
    }
}

template <typename T>
void Vector<T>::dayToi(const size_t &viTri)
{
    if (soPhanTu == doLon)
        capPhat();
    for (size_t i = soPhanTu; i > viTri; i--)
    {
        doi(conTro[i], conTro[i - 1]);
    }
}

template <typename T>
T *Vector<T>::tim(const T &phanTuTim) const
{
    for (size_t i = 0; i < soPhanTu; i++)
    {
        if (this->conTro[i] == phanTuTim)
            return conTro + i;
    }
    return KHONG_TIM_THAY;
}

template <typename T>
void Vector<T>::xoa(const T *dCXoa)
{
    if (lDCDau() <= dCXoa && dCXoa <= lDCCuoi())
    {
        keoLui(dCXoa - lDCDau());
        soPhanTu--;
    }
}
template <typename T>
void Vector<T>::xoa(const size_t &viTriXoa)
{
    if (0 <= viTriXoa && viTriXoa <= soPhanTu - 1)
    {
        keoLui(viTriXoa);
        soPhanTu--;
    }
}
template <typename T>
void Vector<T>::xoa(const T *dCXoaBatDau, const T *dCXoaKetThuc)
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
void Vector<T>::chen(const T *dCChen, const T &phanTuThem)
{
    size_t viTri = dCChen - lDCDau();
    if (soPhanTu == doLon)
        capPhat();
    dayToi(viTri);
    conTro[viTri] = phanTuThem;
    soPhanTu++;
}
template <typename T>
void Vector<T>::them(const T &phanTuThem)
{
    if (soPhanTu == doLon)
        capPhat();
    conTro[soPhanTu] = phanTuThem;
    soPhanTu++;
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &doiTuongCP)
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
template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T> &doiTuongCong) const
{
    Vector<T> doiTuongTraVe(soPhanTu + doiTuongCong.soPhanTu);
    size_t j = 0;
    for (size_t i = 0; i < soPhanTu; i++)
    {
        doiTuongTraVe.conTro[j++] = conTro[i];
    }
    for (size_t i = 0; i < doiTuongCong.soPhanTu; i++)
    {
        doiTuongTraVe.conTro[j++] = doiTuongCong.conTro[i];
    }
    return doiTuongTraVe;
}
template <typename T>
size_t Vector<T>::soPhanTuTrung(const T & phanTuKiemTra) const
{
    size_t dem = 0;
    for (size_t i = 0; i < soPhanTu; i++)
    {
        if (conTro[i] == phanTuKiemTra)
            dem++;
    }
    return dem;
}
#endif