#include "quanLyGiaoDien.h"
#include "giaoDienChinh.h"
#include "giaoDienPhong.h"
#include "gDDienNuoc.h"
#include "gDThietLap.h"

#define oSinhVien (*thanhChuyen)(0, 0)
#define oPhong (*thanhChuyen)(0, 1)
#define oDienNuoc (*thanhChuyen)(0, 2)
#define oThietLap (*thanhChuyen)(0, 3)

#define MAU_XANH_CAY_NHE \
    Color { 224, 255, 255, 255 }
#define MAU_TRANG_NHE {44, 44, 44, 255}
#define MAU_XAM_NHE {31, 31, 31, 255}
#define MAU_XAM {25, 25, 25, 255}
#define MAU_XANH_0_128 {0, 128, 128, 255}

const char *dDHeThong = "data/heThong.csv";
const char *dDFileAnhBachKhoa = "assets/bach_khoa.png";
const char *dDFileAnhKhoaCNTT = "assets/khoa_cntt.png";

namespace QLGD
{
    const char *tiengViet[5] = {"Sinh viên", "Phòng", "Điện nước ", "Thiết lập", ""};
    const char *tiengNhat[5] = {"学生", "部屋", "電気水道", "設定", ""};
    const char *tiengAnh[5] = {"Student", "Room", "Electricity & Water", "Settings", ""};
    const char **ngonNguHienTai;
}
// 7
Color *Mau;
Color MauSang[] = {BLUE, YELLOW, BLACK, RED, MAU_LA_CAY, MAU_XANH, MAU_XANH_CAY_NHE, MAU_XANH_0_128, BLACK, RED, BLUE};
Color MauToi[] = {MAU_TRANG_NHE, ORANGE, WHITE, MAROON, DARKGREEN, DARKPURPLE, MAU_XAM, MAU_XAM_NHE, BLUE, RED, BLUE};

const int SO_HANG_HE_THONG = 9, H_SO_COT_MUC_DIEN = 6, H_MUC_BAC_DIEN = 0, H_GIA_DIEN = 1, H_GIA_NUOC = 2, H_TEN_DON_VI = 3, H_DIA_CHI = 4, H_GIA_PHONG_MD = 5, H_GIA_COC_MD = 6, H_NGON_NGU = 7, H_CHU_DE = 8;

quanLyGiaoDien::quanLyGiaoDien(QuanLyKTX &quanLyKTX) : quanLyKTX(quanLyKTX)
{
    Mau = MauSang;
    QLGD::ngonNguHienTai = QLGD::tiengAnh;
    thanhChuyen = new Bang({10, 5}, 5, 1, {250, 36});
    thanhChuyen->cKieuChu(giaoDien::font26, 26);

    for (int i = 0; i < thanhChuyen->lSoCot(); i++)
    {
        (*thanhChuyen)(0, i).cDoBoVien(0.25f);
    }

    thanhChuyen->cMauTheoHang(0, Mau[0]);
    thanhChuyen->cGianHangCot(0, 10);
    //
    logoBachKhoa = LoadTexture(dDFileAnhBachKhoa);
    logoKhoaCntt = LoadTexture(dDFileAnhKhoaCNTT);

    flagGD = FGD_PHONG;
    flagGDMoi = FGD_SINH_VIEN;
    gDHienThi = nullptr;
    initHeThong();
}
void quanLyGiaoDien::initHeThong()
{
    docGhiFile docTep(dDHeThong);
    Vector<Vector<string>> heThongDoc = docTep.docData();
    for (int i = 0; i < H_SO_COT_MUC_DIEN; i++)
    {
        heThong.bacGiaDien[i] = stoi(heThongDoc[H_MUC_BAC_DIEN][i]);
        heThong.giaDien[i] = stoul(heThongDoc[H_GIA_DIEN][i]);
    }
    heThong.giaNuoc = stoul(heThongDoc[H_GIA_NUOC][0]);

    heThong.tenDonVi = heThongDoc[H_TEN_DON_VI][0];
    heThong.diaChi = heThongDoc[H_DIA_CHI][0];
    heThong.giaPhongMatDinh = stoul(heThongDoc[H_GIA_PHONG_MD][0]);
    heThong.giaCocMatDinh = stoul(heThongDoc[H_GIA_COC_MD][0]);
    switch (stoi(heThongDoc[H_NGON_NGU][0]))
    {
    case 0:
        heThong.ngonNgu = TIENG_VIET;
        break;
    case 1:
        heThong.ngonNgu = TIENG_ANH;
        break;
    case 2:
        heThong.ngonNgu = TIENG_NHAT;
        break;
    }
    switch (stoi(heThongDoc[H_CHU_DE][0]))
    {
    case 0:
        heThong.chuDeGD = GD_SANG;
        break;
    case 1:
        heThong.chuDeGD = GD_TOI;
        break;
    }
}
void quanLyGiaoDien::luuHeThong()
{
    docGhiFile ghiTep(dDHeThong);
    Vector<Vector<string>> heThongLuu(SO_HANG_HE_THONG);
    for (int i = 0; i < H_SO_COT_MUC_DIEN; i++)
    {
        heThongLuu[H_MUC_BAC_DIEN].them(to_string(heThong.bacGiaDien[i]));
        heThongLuu[H_GIA_DIEN].them(to_string(heThong.giaDien[i]));
    }
    heThongLuu[H_GIA_NUOC].them(to_string(heThong.giaNuoc));
    heThongLuu[H_TEN_DON_VI].them(heThong.tenDonVi);
    heThongLuu[H_DIA_CHI].them(heThong.diaChi);
    heThongLuu[H_GIA_PHONG_MD].them(to_string(heThong.giaPhongMatDinh));
    heThongLuu[H_GIA_COC_MD].them(to_string(heThong.giaCocMatDinh));
    heThongLuu[H_NGON_NGU].them(to_string(heThong.ngonNgu));
    heThongLuu[H_CHU_DE].them(to_string(heThong.chuDeGD));

    ghiTep.ghiData(heThongLuu);
}
void quanLyGiaoDien::bieuDien()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Mau[6]);
    hop boxKhung({0, 0, float(GetScreenWidth()), 46}, Mau[7]);
    boxKhung.bieuDien();
    thanhChuyen->bieuDien(0, 0, 0, 3);
    DrawTextureEx(logoBachKhoa, Vector2{1350, 3}, 0.0f, 0.18f, WHITE);
    DrawTextureEx(logoKhoaCntt, Vector2{1400, 3}, 0.0f, 0.18f, WHITE);

    gDHienThi->bieuDien();
}
void quanLyGiaoDien::capNhatTT()
{
    static int bienCapNhatNgonNgu = -1;
    static int bienCapNhatChuDe = -1;

    if (bienCapNhatNgonNgu != heThong.ngonNgu || bienCapNhatChuDe != heThong.chuDeGD)
    {
        capNhatGDVoiHeThong();
        bienCapNhatNgonNgu = heThong.ngonNgu;
        bienCapNhatChuDe = heThong.chuDeGD;
    }
    if (oPhong.laDuocChon())
    {
        flagGDMoi = FGD_PHONG;
        oPhong.cTrangThaiChon(false);
    }
    else if (oSinhVien.laDuocChon())
    {
        flagGDMoi = FGD_SINH_VIEN;
        oSinhVien.cTrangThaiChon(false);
    }
    else if (oDienNuoc.laDuocChon())
    {
        flagGDMoi = FGD_DIEN_NUOC;
        oDienNuoc.cTrangThaiChon(false);
    }
    else if (oThietLap.laDuocChon())
    {
        flagGDMoi = FGD_THIET_LAP;
        oThietLap.cTrangThaiChon(false);
    }

    if (flagGDMoi != flagGD)
    {
        switch (flagGDMoi) 
        {
        case FGD_SINH_VIEN:
            doi(new giaoDienChinh(quanLyKTX, heThong));
            break;
        case FGD_PHONG:
            doi(new giaoDienPhong(quanLyKTX, heThong));
            break;
        case FGD_DIEN_NUOC:
            doi(new gDDienNuoc(quanLyKTX, heThong));
            break;
        case FGD_THIET_LAP:
            doi(new gDThietLap(quanLyKTX, heThong));
            break;
        default:
            break;
        }
        flagGD = flagGDMoi;
    }
    thanhChuyen->vungHoatDong(0, 0, 0, 3);
    gDHienThi->capNhatTT();
}
void quanLyGiaoDien::capNhatGDVoiHeThong()
{

    switch (heThong.ngonNgu)
    {
    case 0:
        QLGD::ngonNguHienTai = QLGD::tiengViet;
        break;
    case 1:
        QLGD::ngonNguHienTai = QLGD::tiengAnh;
        break;
    case 2:
        QLGD::ngonNguHienTai = QLGD::tiengNhat;
        break;
    }
    switch (heThong.chuDeGD)
    {
    case GD_SANG:
        Mau = MauSang;
        break;
    case GD_TOI:
        Mau = MauToi;
        break;
    }
    for (int i = 0; i < thanhChuyen->lSoCot(); i++)
    {
        (*thanhChuyen)(0, i).cNoiDung(QLGD::ngonNguHienTai[i]);
        (*thanhChuyen)(0, i).cMauChu(Mau[2]);
        (*thanhChuyen)(0, i).cMauNen(Mau[0]);
    }
}
void quanLyGiaoDien::xoa()
{
    if (gDHienThi != nullptr)
    {
        delete gDHienThi;
        gDHienThi = nullptr;
    }
}
void quanLyGiaoDien::doi(giaoDien *gDHienThi)
{
    xoa();
    this->gDHienThi = gDHienThi;
}
quanLyGiaoDien::~quanLyGiaoDien()
{
    xoa();
    UnloadTexture(logoKhoaCntt);
    UnloadTexture(logoBachKhoa);
    luuHeThong();
    delete thanhChuyen;
}