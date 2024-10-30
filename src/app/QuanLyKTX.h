
#ifndef _QUANLY
#define _QUANLY
#include "Vector.h"
#include "sinhVien.h"
#include "Phong.h"

class QuanLyKTX
{
private:
    Vector<SinhVien> dSSinhVien;
    Vector<Phong> dSPhong;

public:
    QuanLyKTX();
    bool themSinhVien(const SinhVien &);
    bool themPhong(const Phong &);
    void xoaSinhVien(const string &);
    void xoaPhong(const string &);
    void xoaTatCaPhong();
    void xoaTatCaSinhVien();
    void cThonTinSinhVien(const SinhVien &);
    bool doiSinhVien(const SinhVien &, const SinhVien &);
    bool doiPhong(const Phong &, const Phong &);
    const SinhVien &timSinhVien(const string &);
    const Vector<SinhVien> timSinhVienGiong(const string &);
    const Vector<Phong> timPhongGiong(const string &);
    const Phong &timPhong(const string &);
    const Vector<Phong> &lDanhSachPhong();
    const Vector<SinhVien> &lDanhSachSinhVien();
    const Vector<SinhVien> lSinhVien();
    ~QuanLyKTX();
};

#endif
