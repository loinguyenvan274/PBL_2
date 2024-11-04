#include "quanLyGiaoDien.h"
#include "giaoDienChinh.h"
#include "giaoDienPhong.h"
#include "gDDienNuoc.h"

#define oSinhVien (*thanhChuyen)(0, 0)
#define oPhong (*thanhChuyen)(0, 1)
#define oDienNuoc (*thanhChuyen)(0, 2)

quanLyGiaoDien::quanLyGiaoDien(QuanLyKTX &quanLyKTX) : quanLyKTX(quanLyKTX)
{

    docGhiFile docTep("data/heThong.csv");
    heThong = docTep.docData();

    thanhChuyen = new Bang({10, 5}, 5, 1, {250, 36});
    thanhChuyen->cKieuChu(giaoDien::font26, 26);

    oSinhVien.cDoBoVien(0.2);
    oPhong.cDoBoVien(0.2);
    oDienNuoc.cDoBoVien(0.2);
    oSinhVien.cNoiDung("          Sinh viên");
    oPhong.cNoiDung("          Phòng");
    oDienNuoc.cNoiDung("          Điện nước");

    thanhChuyen->cMauTheoHang(0, BLUE);
    thanhChuyen->cGianHangCot(0, 10);
    //
    logoBachKhoa = LoadTexture("assets/bach_khoa.png");
    logoKhoaCntt = LoadTexture("assets/khoa_cntt.png");

    flagGD = FGD_PHONG;
    flagGDMoi = FGD_SINH_VIEN;
    gDHienThi = nullptr;
}
void quanLyGiaoDien::bieuDien()
{
    hop boxKhung({0, 0, float(GetScreenWidth()), 46}, {0, 128, 128, 255});
    boxKhung.bieuDien();
    thanhChuyen->bieuDien(0, 0, 0, 2);
    DrawTextureEx(logoBachKhoa, Vector2{1350, 3}, 0.0f, 0.18f, WHITE);
    DrawTextureEx(logoKhoaCntt, Vector2{1400, 3}, 0.0f, 0.18f, WHITE);

    gDHienThi->bieuDien(); // Truy cập con trỏ
}
void quanLyGiaoDien::capNhatTT()
{
    if (oPhong.laDuocChon())
    {
        flagGDMoi = FGD_PHONG;
        oPhong.cTrangThaiChon(false);
    }
    if (oSinhVien.laDuocChon())
    {
        flagGDMoi = FGD_SINH_VIEN;
        oSinhVien.cTrangThaiChon(false);
    }
    if (oDienNuoc.laDuocChon())
    {
        flagGDMoi = FGD_DIEN_NUOC;
        oDienNuoc.cTrangThaiChon(false);
    }

    if (flagGDMoi != flagGD)
    {
        switch (flagGDMoi)
        {
        case FGD_SINH_VIEN:
            doi(new giaoDienChinh(quanLyKTX));
            break;
        case FGD_PHONG:
            doi(new giaoDienPhong(quanLyKTX));
            break;
        case FGD_DIEN_NUOC:
            doi(new gDDienNuoc(quanLyKTX, heThong));
            break;
        default:
            break;
        }
        flagGD = flagGDMoi;
    }
    thanhChuyen->vungHoatDong(0, 0, 0, 2);
    gDHienThi->capNhatTT(); // Truy cập con trỏ
}
void quanLyGiaoDien::xoa()
{
    if (gDHienThi != nullptr)
    {
        delete gDHienThi;
        gDHienThi = nullptr;
    }
}
void quanLyGiaoDien::doi(giaoDien *gDHienThi) // Nhận con trỏ
{
    xoa();
    this->gDHienThi = gDHienThi;
}
quanLyGiaoDien::~quanLyGiaoDien()
{
    xoa();
    UnloadTexture(logoKhoaCntt);
    UnloadTexture(logoBachKhoa);

    docGhiFile ghiTep("data/heThong.csv");
    ghiTep.ghiData(heThong);
    delete thanhChuyen;
}