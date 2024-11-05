
#ifndef _QUANLY
#define _QUANLY
#include "Vector.h"
#include "sinhVien.h"
#include "Phong.h"
enum ThietLapCSDN
{
    THIET_LAP_TAT_CA,
    CHUYEN_CSCT_SANG_CSDT
};
enum TrangThaiSV
{
    HOP_LE,
    TRUNG_MA,
    MA_KHONG_HOP_LE,
    PHONG_KHONG_TON_TAI,
    PHONG_DAY,
};
class QuanLyKTX
{
private:
    Vector<SinhVien> dSSinhVien;
    Vector<Phong> dSPhong;

public:
    QuanLyKTX();
    TrangThaiSV themSinhVien(const SinhVien &);
    bool themPhong(const Phong &);
    void xoaSinhVien(const string &);
    void xoaPhong(const string &);
    void xoaTatCaPhong();
    void xoaTatCaSinhVien();
    void xoaSinhVienOPhong(const string &);
    void cThonTinSinhVien(const SinhVien &);
    TrangThaiSV doiSinhVien(const SinhVien &, const SinhVien &);
    bool doiPhong(const Phong &, const Phong &);
    const SinhVien &timSinhVien(const string &);
    const Vector<SinhVien> timSinhVienGiong(const string &, bool (*soSanh)(const SinhVien &, const string &));
    static bool soSanhMaSV(const SinhVien &, const string &);
    static bool soSanhTenSV(const SinhVien &, const string &);
    static bool soSanhMaPhongSV(const SinhVien &, const string &);
    const Vector<Phong> timPhongGiong(const string &);
    const Phong *timPhong(const string &) const;
    const Vector<Phong> &lDanhSachPhong();
    const Vector<SinhVien> &lDanhSachSinhVien();

    void resetChiSoDienNuoc(ThietLapCSDN);
    ~QuanLyKTX();
};

#endif
