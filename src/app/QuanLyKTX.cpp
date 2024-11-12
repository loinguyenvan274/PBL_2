#include "QuanLyKTX.h"

QuanLyKTX::QuanLyKTX() {}

QuanLyKTX::~QuanLyKTX() {}

TrangThaiSV QuanLyKTX::themSinhVien(const SinhVien &sinhVien)
{
    Phong *phongChuaSinhVien = dsPhong.timPhanTu(sinhVien.lMaPhong());
    if ("" == sinhVien.lMa())
        return MA_KHONG_HOP_LE;
    if (dsSinhVien.timPhanTu(sinhVien.lMa()) != KHONG_TIM_THAY)
        return TRUNG_MA;
    if (dsPhong.timPhanTu(sinhVien.lMaPhong()) == KHONG_TIM_THAY)
        return PHONG_KHONG_TON_TAI;
    if (phongChuaSinhVien->lSoNguoiHienTai() == phongChuaSinhVien->lSoNguoiToiDa())
        return PHONG_DAY;
    dsSinhVien.themPhanTu(sinhVien, sinhVien.lMa());
    phongChuaSinhVien->cSoNguoiHienTai(phongChuaSinhVien->lSoNguoiHienTai() + 1);
    return HOP_LE;
}
bool QuanLyKTX::themPhong(const Phong &phong)
{
    if ("" == phong.lMaPhong() || dsPhong.timPhanTu(phong.lMaPhong()) != KHONG_TIM_THAY)
        return false; // neu khoong hop le tra ve false
    dsPhong.themPhanTu(phong, phong.lMaPhong());
    return true;
}
void QuanLyKTX::xoaSinhVien(const string &maSinhVien)
{
    SinhVien *sinhVienXoa = dsSinhVien.timPhanTu(maSinhVien);
    Phong *phongChuaSinhVien = dsPhong.timPhanTu(sinhVienXoa->lMaPhong());
    dsSinhVien.xoaPhanTu(maSinhVien);
    if (phongChuaSinhVien != nullptr)
        phongChuaSinhVien->cSoNguoiHienTai(phongChuaSinhVien->lSoNguoiHienTai() - 1);
}

void QuanLyKTX::xoaPhong(const string &maPhong)
{
    dsPhong.xoaPhanTu(maPhong);
    xoaSinhVienOPhong(maPhong);
}

const Vector<SinhVien> QuanLyKTX::timSinhVienGiong(const string &chuoiCon, bool (*soSanh)(const SinhVien &, const string &))
{
    Vector<SinhVien> cacSinhVien = dsSinhVien.layCacGiaTri();
    Vector<SinhVien> sinhvienDuocTim;
    for (int i = 0; i < cacSinhVien.lSoPhanTu(); i++)
    {
        if (soSanh(cacSinhVien[i], chuoiCon))
            sinhvienDuocTim.them(cacSinhVien[i]);
    }
    return sinhvienDuocTim;
}
bool QuanLyKTX::soSanhMaSV(const SinhVien &sinhVien, const string &maSV) { return sinhVien.lMa().find(maSV) != string::npos; }
bool QuanLyKTX::soSanhTenSV(const SinhVien &sinhVien, const string &tenSinhVien) { return sinhVien.lHoVaTen().find(tenSinhVien) != string::npos; }
bool QuanLyKTX::soSanhMaPhongSV(const SinhVien &sinhVien, const string &phongSinhVien) { return sinhVien.lMaPhong().find(phongSinhVien) != string::npos; }
const Vector<Phong> QuanLyKTX::timPhongGiong(const string &chuoiCon)
{
    Vector<Phong> cacPhong = dsPhong.layCacGiaTri();
    Vector<Phong> phongDuocTim;
    for (int i = 0; i < cacPhong.lSoPhanTu(); i++)
    {
        if (cacPhong[i].lMaPhong().find(chuoiCon) != string::npos)
            phongDuocTim.them(cacPhong[i]);
    }
    return phongDuocTim;
}

TrangThaiSV QuanLyKTX::doiSinhVien(const SinhVien &sinhVienCu, const SinhVien &sinhVienMoi)
{
    // những cái return false này sau này có thê chỉnh sửa mới một thông báo khác chứ không phải tại sao gom lại các trường hợp cho khỏe
    if (!(sinhVienCu == sinhVienMoi))
    {
        if (dsSinhVien.timPhanTu(sinhVienMoi.lMa()) != KHONG_TIM_THAY)
        {
            cout << " sinh Vien Trung ma aaa;\n";
            return TRUNG_MA; // sinh Vien Trung ma;
        }
        if (sinhVienMoi.lMa() == "")
        {
            cout << " sinh vien khong hop le;\n";
            return MA_KHONG_HOP_LE; // sinh vien khong hop le
        }
    }
    Phong *phongsinhVienMoi = dsPhong.timPhanTu(sinhVienMoi.lMaPhong());
    if (sinhVienCu.lMaPhong() != sinhVienMoi.lMaPhong())
    {
        if (phongsinhVienMoi == KHONG_TIM_THAY)
        {
            cout << "Phong khong ton tai;\n";
            return PHONG_KHONG_TON_TAI; // phong khoong ton taij
        }
        if (phongsinhVienMoi->lSoNguoiHienTai() == phongsinhVienMoi->lSoNguoiToiDa())
        {
            cout << " phong day;\n";
            return PHONG_DAY; // phong da Day
        }
        else
        {
            Phong *phongSinhVienCu = dsPhong.timPhanTu(sinhVienCu.lMaPhong());
            phongSinhVienCu->cSoNguoiHienTai(phongSinhVienCu->lSoNguoiHienTai() - 1);
            phongsinhVienMoi->cSoNguoiHienTai(phongsinhVienMoi->lSoNguoiHienTai() + 1);
        }
    }
    SinhVien *viTriSV = dsSinhVien.timPhanTu(sinhVienCu.lMa());
    if (viTriSV != nullptr)
        *viTriSV = sinhVienMoi;
    return HOP_LE;
}
void QuanLyKTX::xoaSinhVienOPhong(const string &maPhong)
{
    const Vector<SinhVien> dSSinhVien = dsSinhVien.layCacGiaTri();
    for (int i = 0; i < dSSinhVien.lSoPhanTu(); i++)
    {
        if (dSSinhVien[i].lMaPhong() == maPhong)
        {
            dsSinhVien.xoaPhanTu(dSSinhVien[i].lMa());
        }
    }
}
bool QuanLyKTX::doiPhong(const Phong &phongCu, const Phong &phongMoi)
{

    if (((phongCu == phongMoi) || (dsPhong.timPhanTu(phongMoi.lMaPhong()) == KHONG_TIM_THAY) && phongMoi.lMaPhong() != ""))
    {
        Phong *viTriPhong = dsPhong.timPhanTu(phongCu.lMaPhong());
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
void QuanLyKTX::xoaTatCaSinhVien() { dsSinhVien.xoaTatCa(); }

void QuanLyKTX::xoaTatCaPhong()
{
    dsPhong.xoaTatCa();
    xoaTatCaSinhVien();
}
const Phong *QuanLyKTX::timPhong(const string &maPhong) const
{
    return dsPhong.timPhanTu(maPhong);
}

const Vector<SinhVien> QuanLyKTX::lDanhSachSinhVien() { return dsSinhVien.layCacGiaTri(); };

const Vector<Phong> QuanLyKTX::lDanhSachPhong() { return dsPhong.layCacGiaTri(); }

void QuanLyKTX::resetChiSoDienNuoc(ThietLapCSDN thietLap)
{
    Vector<Phong *> dSPhong = dsPhong.layCacPhanTu();
    for (int i = 0; i < dSPhong.lSoPhanTu(); i++)
    {
        if (thietLap == CHUYEN_CSCT_SANG_CSDT)
        {
            dSPhong[i]->cDienCSDT(dSPhong[i]->lDienCSCT());
            dSPhong[i]->cNuocCSDT(dSPhong[i]->lNuocCSCT());
        }
        else
        {
            dSPhong[i]->cDienCSDT(0.0f);
            dSPhong[i]->cNuocCSDT(0.0f);
        }
        dSPhong[i]->cDienCSCT(0.0f);
        dSPhong[i]->cNuocCSCT(0.0f);
        dSPhong[i]->cNopTienDN(false);
    }
}
