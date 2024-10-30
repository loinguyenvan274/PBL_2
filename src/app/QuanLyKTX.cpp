#include "QuanLyKTX.h"

QuanLyKTX::QuanLyKTX() {}

QuanLyKTX::~QuanLyKTX() {}

bool QuanLyKTX::themSinhVien(const SinhVien &sinhVien)
{
    Phong *phongChuaSinhVien = dSPhong.tim(Phong(sinhVien.lMaPhong()));
    SinhVien sinhVienThem = sinhVien;
    if ("" == sinhVien.lMa() || dSSinhVien.tim(sinhVien) != KHONG_TIM_THAY || dSPhong.tim(Phong(sinhVien.lMaPhong())) == KHONG_TIM_THAY || phongChuaSinhVien->lSoNguoiHienTai() >= phongChuaSinhVien->lSoNguoiToiDa())
        return false;
    dSSinhVien.chen(dSSinhVien.lDCDau(), sinhVienThem);
    phongChuaSinhVien->cSoNguoiHienTai(phongChuaSinhVien->lSoNguoiHienTai() + 1);
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
    SinhVien *sinhVienXoa = dSSinhVien.tim(SinhVien("", maSinhVien));
    Phong *phongChuaSinhVien = dSPhong.tim(Phong(sinhVienXoa->lMaPhong()));
    dSSinhVien.xoa(sinhVienXoa);
    if (phongChuaSinhVien != nullptr)
        phongChuaSinhVien->cSoNguoiHienTai(phongChuaSinhVien->lSoNguoiHienTai() - 1);
}
void QuanLyKTX::cThonTinSinhVien(const SinhVien &sinhVien)
{
    *(dSSinhVien.tim(sinhVien)) = sinhVien;
}
void QuanLyKTX::xoaPhong(const string &maPhong)
{
    dSPhong.xoa(dSPhong.tim(Phong(maPhong)));
    xoaSinhVienOPhong(maPhong);
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

    if ((sinhVienCu == sinhVienMoi) || (dSSinhVien.soPhanTuTrung(sinhVienMoi) == 0) && sinhVienMoi.lMa() != "" && dSPhong.tim(Phong(sinhVienMoi.lMaPhong())) != KHONG_TIM_THAY)
    {
        Phong *phongSinhVienCu = dSPhong.tim(Phong(sinhVienCu.lMaPhong()));
        Phong *phongsinhVienMoi = dSPhong.tim(Phong(sinhVienMoi.lMaPhong()));
        if (phongsinhVienMoi->lSoNguoiHienTai() >= phongsinhVienMoi->lSoNguoiToiDa())
            return false;
        if (phongSinhVienCu != nullptr)
            phongSinhVienCu->cSoNguoiHienTai(phongSinhVienCu->lSoNguoiHienTai() - 1);
        if (phongsinhVienMoi != nullptr)
            phongsinhVienMoi->cSoNguoiHienTai(phongsinhVienMoi->lSoNguoiHienTai() + 1);
        SinhVien *viTriSV = dSSinhVien.tim(sinhVienCu);
        if (viTriSV != nullptr)
            *viTriSV = sinhVienMoi;
        return true;
    }
    return false;
}
void QuanLyKTX::xoaSinhVienOPhong(const string &maPhong)
{
    // một lần xóa là kéo lui
    // i ++ chạy tơi
    // xoa vi trí 5
    // i++
    // kéo lui vị tri 5
    // i 66
    // bỏ xót
    for (int i = 0; i < dSSinhVien.lSoPhanTu(); i++)
    {
        if (dSSinhVien[i].lMaPhong() == maPhong)
        {
            dSSinhVien.xoa(dSSinhVien.tim(dSSinhVien[i]));
            i--;
        }
    }
}
bool QuanLyKTX::doiPhong(const Phong &phongCu, const Phong &phongMoi)
{

    if (((phongCu == phongMoi) || (dSPhong.soPhanTuTrung(phongMoi) == 0) && phongMoi.lMaPhong() != ""))
    {
        Phong *viTriPhong = dSPhong.tim(phongCu);
        if (viTriPhong != nullptr)
            *viTriPhong = phongMoi;
        if (!(phongCu == phongMoi))
        {
            xoaSinhVienOPhong(phongCu.lMaPhong());
        }
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
const Phong *QuanLyKTX::timPhong(const string &maPhong) const
{
    return dSPhong.tim(Phong(maPhong));
}

const Vector<SinhVien> &QuanLyKTX::lDanhSachSinhVien() { return dSSinhVien; };

const Vector<Phong> &QuanLyKTX::lDanhSachPhong() { return dSPhong; }

void QuanLyKTX::resetChiSoDienNuoc(ThietLapCSDN thietLap)
{
    for (int i = 0; i < dSPhong.lSoPhanTu(); i++)
    {
        if (thietLap == CHUYEN_CSCT_SANG_CSDT)
        {
            dSPhong[i].cDienCSDT(dSPhong[i].lDienCSCT());
            dSPhong[i].cNuocCSDT(dSPhong[i].lNuocCSCT());
        }
        else
        {
            dSPhong[i].cDienCSDT(0.0f);
            dSPhong[i].cNuocCSDT(0.0f);
        }
        dSPhong[i].cDienCSCT(0.0f);
        dSPhong[i].cNuocCSCT(0.0f);
        dSPhong[i].cNopTienDN(false);
    }
}
