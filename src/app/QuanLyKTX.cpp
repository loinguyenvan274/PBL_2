#include "QuanLyKTX.h"

QuanLyKTX::QuanLyKTX() {}

QuanLyKTX::~QuanLyKTX() {}

bool QuanLyKTX::themSinhVien(const SinhVien &sinhVien)
{
    SinhVien sinhVienThem = sinhVien;
    if ("" == sinhVien.lMa() || dSSinhVien.tim(sinhVien) != KHONG_TIM_THAY)
        return false;
    dSSinhVien.chen(dSSinhVien.lDCDau(), sinhVienThem);
    return true;
}
bool QuanLyKTX::themPhong(const Phong &phong)
{
    if ("" == phong.lMaPhong() || dSPhong.tim(phong) != KHONG_TIM_THAY)
        return false; // neu khoong hop le tra ve false
    dSPhong.chen(dSPhong.lDCDau(), phong);
    return true;
}
void QuanLyKTX::xoaSinhVien(const string &maSinhVien)
{
    dSSinhVien.xoa(dSSinhVien.tim(SinhVien("", maSinhVien)));
}
void QuanLyKTX::cThonTinSinhVien(const SinhVien &sinhVien)
{
    *(dSSinhVien.tim(sinhVien)) = sinhVien;
}
void QuanLyKTX::xoaPhong(const string &maPhong)
{
    dSPhong.xoa(dSPhong.tim(Phong(maPhong)));
}
const Vector<SinhVien> QuanLyKTX::timSinhVienGiong(const string &chuoiCon)
{
    Vector<SinhVien> sinhvienDuocTim;
    for (int i = 0; i < dSSinhVien.lSoPhanTu(); i++)
    {
        if (dSSinhVien[i].lHoVaTen().find(chuoiCon) != string::npos)
            sinhvienDuocTim.them(dSSinhVien[i]);
    }
    return sinhvienDuocTim;
}
const Vector<Phong> QuanLyKTX::timPhongGiong(const string &chuoiCon)
{
    Vector<Phong> phongDuocTim;
    for (int i = 0; i < dSPhong.lSoPhanTu(); i++)
    {
        if (dSPhong[i].lMaPhong().find(chuoiCon) != string::npos)
            phongDuocTim.them(dSPhong[i]);
    }
    return phongDuocTim;
}

bool QuanLyKTX::doiSinhVien(const SinhVien &sinhVienCu, const SinhVien &sinhVienMoi)
{
    if (((sinhVienCu == sinhVienMoi) || (dSSinhVien.soPhanTuTrung(sinhVienMoi) == 0) && sinhVienMoi.lMa() != ""))
    {
        SinhVien *viTriSV = dSSinhVien.tim(sinhVienCu);
        if (viTriSV != nullptr)
            *viTriSV = sinhVienMoi;
        return true;
    }
    return false;
}
bool QuanLyKTX::doiPhong(const Phong &phongCu, const Phong &phongMoi)
{
    if (((phongCu == phongMoi) || (dSPhong.soPhanTuTrung(phongMoi) == 0) && phongMoi.lMaPhong() != ""))
    {
        Phong *viTriPhong = dSPhong.tim(phongCu);
        if (viTriPhong != nullptr)
            *viTriPhong = phongMoi;
        return true;
    }
    return false;
}
void QuanLyKTX::xoaTatCaSinhVien() { dSSinhVien.xoa(dSSinhVien.lDCDau(), dSSinhVien.lDCCuoi()); }

void QuanLyKTX::xoaTatCaPhong()
{
    dSPhong.xoa(dSPhong.lDCDau(), dSPhong.lDCCuoi());
    xoaTatCaSinhVien();
}

const Vector<SinhVien> &QuanLyKTX::lDanhSachSinhVien() { return dSSinhVien; };

const Vector<Phong> &QuanLyKTX::lDanhSachPhong() { return dSPhong; }
