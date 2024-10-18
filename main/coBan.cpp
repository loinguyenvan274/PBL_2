#include "coBan.h"

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
    if (this->doLon < 0)
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
T *Vector<T>::viTriDau() const
{
    return conTro;
}
template <typename T>
T *Vector<T>::viTriCuoi() const
{
    return conTro + soPhanTu;
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
    doLon *= 2;
    T *tamThoi = new T[doLon];

    for (size_t i = 0; i < soPhanTu; i++)
    {

        tamThoi[i] = conTro[i];
    }

    delete[] conTro;
    cout << "here" << endl;

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
size_t Vector<T>::tim(const T &phanTuTim) const
{
    for (size_t i = 0; i < soPhanTu; i++)
    {
        if ( this->conTro[i] == phanTuTim)
            return i;
    }
    return KHONG_TIM_THAY;
}
template <typename T>
void Vector<T>::xoa(const T &phanTuXoa)
{
    for (size_t i = 0; i < soPhanTu; i++)
    {
        if (phanTuXoa == conTro[i])
        {
            keoLui(i);
            soPhanTu--;
        }
    }
}

template <typename T>
void Vector<T>::chen(const size_t &viTri, const T &phanTuThem)
{

    if (soPhanTu == doLon)
        capPhat();
    dayToi(viTri);
    conTro[viTri] = phanTuThem;
    soPhanTu++;
}
