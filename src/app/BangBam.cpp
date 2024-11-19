#ifndef _MABAMCPP
#define _MABAMCPP

#include "BangBam.h"
#include <cmath>
template <typename T>
void BangBam<T>::khoiTao()
{
	for (Size_t i = 0; i < khoiLuong; i++)
	{
		mang[i] = nullptr;
	}
}

template <typename T>
BangBam<T>::BangBam(const Size_t &khoiLuong) : khoiLuong(khoiLuong), soPhanTu(0)
{
	mang = new Diem<T> *[khoiLuong];
	khoiTao();
}

template <typename T>
Size_t BangBam<T>::hamBam(const std::string &maBam) const
{
	Size_t hash = 3;
	for (Size_t i = 0; i < maBam.size(); i++)
	{
		hash += maBam[i] * (i * (i + maBam[i]) + 1) * pow(khoiLuong * (i + 1), 1.3f);
	}
	return hash % khoiLuong;
}
template <typename T>
void BangBam<T>::xoaTatCa()
{
	Diem<T> *tamThoi;
	for (Size_t i = 0; i < khoiLuong; i++)
	{
		while (mang[i] != nullptr)
		{
			tamThoi = mang[i];
			mang[i] = mang[i]->tiepTheo;
			delete tamThoi;
		}
	}
	soPhanTu = 0;
}
template <typename T>
BangBam<T>::~BangBam()
{
	xoaTatCa();
	delete[] mang;
}
template <typename T>
void BangBam<T>::themPhanTu(const T &phanTu, const std::string &maBam)
{
	Size_t chiSo = hamBam(maBam);
	Diem<T> *phanTuMoi = new Diem(maBam, phanTu);
	if (mang[chiSo] == nullptr)
	{
		mang[chiSo] = phanTuMoi;
	}
	else
	{
		phanTuMoi->tiepTheo = mang[chiSo]->tiepTheo;
		mang[chiSo]->tiepTheo = phanTuMoi;
	}
	soPhanTu++;
}
template <typename T>
const Vector<T> BangBam<T>::layCacGiaTri()
{
	Vector<T> mangTraVe(soPhanTu);
	Size_t j = 0;
	Diem<T> *truyTheo;
	for (Size_t i = 0; i < khoiLuong; i++)
	{
		truyTheo = mang[i];
		while (truyTheo != nullptr)
		{
			mangTraVe[j++] = truyTheo->DuLieu;
			truyTheo = truyTheo->tiepTheo;
		}
	}
	return mangTraVe;
}
template <typename T>
const Vector<T *> BangBam<T>::layCacPhanTu()
{
	Vector<T *> mangTraVe(soPhanTu);
	Size_t j = 0;
	Diem<T> *truyTheo;
	for (Size_t i = 0; i < khoiLuong; i++)
	{
		truyTheo = mang[i];
		while (truyTheo != nullptr)
		{
			mangTraVe[j++] = &truyTheo->DuLieu;
			truyTheo = truyTheo->tiepTheo;
		}
	}
	return mangTraVe;
}
static int count = 0;
template <typename T>
Diem<T> *BangBam<T>::timDiem(const std::string &maBam) const
{
	Size_t chiSo = hamBam(maBam);
	Diem<T> *truyTheo = mang[chiSo];
	while (truyTheo != nullptr)
	{
		if (truyTheo->maBam == maBam)
			return truyTheo;
		truyTheo = truyTheo->tiepTheo;
	}
	return nullptr;
}
template <typename T>
T *BangBam<T>::timPhanTu(const std::string &maBam) const
{
	Diem<T> *DiemTim = timDiem(maBam);
	if (DiemTim != nullptr)
		return &DiemTim->DuLieu;
	return nullptr;
}
template <typename T>
bool BangBam<T>::xoaPhanTu(const std::string &maBam)
{

	Size_t chiSo = hamBam(maBam);

	Diem<T> *truyTheo = mang[chiSo];
	Diem<T> *diemGiu;
	if (mang[chiSo] != nullptr && mang[chiSo]->maBam == maBam)
	{
		diemGiu = mang[chiSo]->tiepTheo;
		delete mang[chiSo];
		mang[chiSo] = diemGiu;
		soPhanTu--;
		return true;
	}
	while (truyTheo->tiepTheo != nullptr)
	{
		if (truyTheo->tiepTheo->maBam == maBam)
		{
			diemGiu = truyTheo->tiepTheo;
			truyTheo->tiepTheo = diemGiu->tiepTheo;
			delete diemGiu;
			soPhanTu--;
			return true;
		}
		truyTheo = truyTheo->tiepTheo;
	}

	return false;
}
template <typename T>

void BangBam<T>::thayThe(const T &phanTu, const std::string &maMoi, const std::string &maCu)
{
	xoaPhanTu(maCu);
	themPhanTu(phanTu, maMoi);
}

#endif