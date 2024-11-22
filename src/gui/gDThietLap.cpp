#include "gDThietLap.h"

const char *noiDungOTiengViet[20] = {"Tên đơn vị: ", "Địa chỉ:", "Giá phòng (mặc định):", "Tiền thế chấp (mặc định):", "Ngôn ngữ:", "Giao diện:"};
const char *noiDungNut1TiengViet[20] = {"Sáng", "Tối"};

const char *noiDungOTiengAnh[20] = {"Unit name: ", "Address:", "Room price (default):", "Deposit (default):", "Language:", "Interface:"};
const char *noiDungNut1TiengAnh[20] = {"Light", "Dark"};

const char *noiDungOTiengNhat[20] = {"ユニット名: ", "住所:", "部屋の料金 (デフォルト):", "保証金 (デフォルト):", "言語:", "インターフェース:"};
const char *noiDungNut1TiengNhat[20] = {"ライト", "ダーク"};

const char *noiDungNutMoiNgonNgu[20] = {"Tiếng việt", "English", "日本語"};
struct NgonNguHienThi
{
    const char **noiDungO;
    const char **noiDungNut;
    const char **noiDungNut1;
};

extern const Color *Mau;
const NgonNguHienThi tiengViet{noiDungOTiengViet, noiDungNutMoiNgonNgu, noiDungNut1TiengViet};
const NgonNguHienThi tiengAnh{noiDungOTiengAnh, noiDungNutMoiNgonNgu, noiDungNut1TiengAnh};
const NgonNguHienThi tiengNhat{noiDungOTiengNhat, noiDungNutMoiNgonNgu, noiDungNut1TiengNhat};

const NgonNguHienThi *ngonNguHienTai;
enum TenCacO
{
    TEN_DON_VI,
    DIA_CHI,
    GIA_PHONG_MD,
    TIEN_THE_CHAP_MD,
    NGON_NGU,
    GIAO_DIEN
};
gDThietLap::gDThietLap(QuanLyKTX &quanLyKTX, HeThong &heThong) : giaoDien(quanLyKTX, heThong)
{
    ngonNguHienTai = &tiengViet;
    nutNgonNguHienTai = -1;
    table = new Bang({100, 100}, 2, 6, {250, 36});
    table->cGianHangCot(70, 23);
    table->cCot(0, 300);
    table->cCot(1, 1000);
    for (int i = 0; i < table->lSoHang(); i++)
    {
        (*table)(i, 0).cNoiDung(ngonNguHienTai->noiDungO[i]);
        for (int j = 0; j < table->lSoCot(); j++)
        {
            (*table)(i, j).cDoBoVien(0.25f);
            (*table)(i, j).cKieuChu(font26);
        }
    }
    tuyChonNgonNgu.nutBiRangBuot = this->heThong->ngonNgu;
    tuyChonChuDe.nutBiRangBuot = this->heThong->chuDeGD;

    (*table)(NGON_NGU, 1).cKichCo(0, 0);
    (*table)(GIAO_DIEN, 1).cKichCo(0, 0);
    (*table)(TEN_DON_VI, 1).cNoiDung(this->heThong->tenDonVi);
    (*table)(DIA_CHI, 1).cNoiDung(this->heThong->diaChi);
    (*table)(TIEN_THE_CHAP_MD, 1).cNoiDung(to_string(this->heThong->giaCocMatDinh));
    (*table)(GIA_PHONG_MD, 1).cNoiDung(to_string(this->heThong->giaPhongMatDinh));
    (*table)(TIEN_THE_CHAP_MD, 1).cChiNhapSo(true);
    (*table)(GIA_PHONG_MD, 1).cChiNhapSo(true);

    vekhoiTao();
}
void gDThietLap::capNhatVaoHeThong()
{
    heThong->tenDonVi = (*table)(TEN_DON_VI, 1).layChu();
    heThong->diaChi = (*table)(DIA_CHI, 1).layChu();

    try
    {
        heThong->giaCocMatDinh = stoul((*table)(TIEN_THE_CHAP_MD, 1).layChu());
    }
    catch (std::invalid_argument &)
    {
        heThong->giaCocMatDinh = 0;
    }
    try
    {

        heThong->giaPhongMatDinh = stoul((*table)(GIA_PHONG_MD, 1).layChu());
    }
    catch (std::invalid_argument &)
    {
        heThong->giaPhongMatDinh = 0;
    }

    switch (tuyChonNgonNgu.nutBiRangBuot)
    {
    case 0:
        heThong->ngonNgu = TIENG_VIET;
        break;
    case 1:
        heThong->ngonNgu = TIENG_ANH;
        break;
    case 2:
        heThong->ngonNgu = TIENG_NHAT;
        break;
    }
    switch (tuyChonChuDe.nutBiRangBuot)
    {
    case 0:
        heThong->chuDeGD = GD_SANG;
        break;
    case 1:
        heThong->chuDeGD = GD_TOI;
        break;
    }
}

void gDThietLap::vekhoiTao()
{
    for (int i = 0; i < table->lSoHang(); i++)
    {
        (*table)(i, 0).cNoiDung(ngonNguHienTai->noiDungO[i]);
        (*table)(i, 0).cMauChu(Mau[2]);
        (*table)(i, 1).cMauChu(Mau[2]);
    }
    table->cMauTheoCot(1, Mau[0]);
    table->cMauTheoCot(0, Mau[6]);

    const int soNut = 3;
    tuyChonNgonNgu.dSNut = Vector<hopChu>(soNut);
    float chieuDaiO = 130;
    float khoangCachO = 20;
    for (int i = 0; i < tuyChonNgonNgu.dSNut.lSoPhanTu(); i++)
    {
        tuyChonNgonNgu.dSNut[i] = hopChu({(*table)(NGON_NGU, 1).layViTri().x + (chieuDaiO + khoangCachO) * i, (*table)(NGON_NGU, 1).layViTri().y, chieuDaiO, 40}, ngonNguHienTai->noiDungNut[i], BLUE, YELLOW, BLACK, font26);
        tuyChonNgonNgu.dSNut[i].cDoBoVien(0.3f);
        tuyChonNgonNgu.dSNut[i].cMauChu(Mau[2]);
        tuyChonNgonNgu.dSNut[i].cMauNen(Mau[0]);
    }

    tuyChonChuDe.dSNut = Vector<hopChu>(2);
    float chieuDaiO1 = 130;
    float khoangCachO1 = 20;
    for (int i = 0; i < tuyChonChuDe.dSNut.lSoPhanTu(); i++)
    {
        tuyChonChuDe.dSNut[i] = hopChu({(*table)(GIAO_DIEN, 1).layViTri().x + (chieuDaiO1 + khoangCachO1) * i, (*table)(GIAO_DIEN, 1).layViTri().y, chieuDaiO1, 40}, ngonNguHienTai->noiDungNut1[i], BLUE, YELLOW, BLACK, font26);
        tuyChonChuDe.dSNut[i].cDoBoVien(0.3f);
        tuyChonChuDe.dSNut[i].cMauChu(Mau[2]);
        tuyChonChuDe.dSNut[i].cMauNen(Mau[0]);
    }
}
void gDThietLap::bieuDien()
{
    table->bieuDien(0, 0, table->lSoHang() - 1, table->lSoCot() - 1);
    tuyChonNgonNgu.bieuDien();
    tuyChonChuDe.bieuDien();
}
void gDThietLap::capNhatTT()
{
    static int chuDeHienTai = -1;
    if (nutNgonNguHienTai != tuyChonNgonNgu.nutBiRangBuot || chuDeHienTai != heThong->chuDeGD)
    {
        chuDeHienTai = heThong->chuDeGD;
        nutNgonNguHienTai = tuyChonNgonNgu.nutBiRangBuot;
        vekhoiTao();
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        cout << GetMouseY() << "  ---  " << GetMouseX() << endl;
    table->vungHoatDong(0, 1, table->lSoHang() - 1, table->lSoCot() - 1);
    tuyChonNgonNgu.capNhatTT();
    tuyChonChuDe.capNhatTT();
    capNhatVaoHeThong();
    switch (tuyChonNgonNgu.nutBiRangBuot)
    {
    case 0:
        ngonNguHienTai = &tiengViet;
        break;
    case 1:
        ngonNguHienTai = &tiengAnh;
        break;
    case 2:
        ngonNguHienTai = &tiengNhat;
        break;
    }
   
}
gDThietLap::~gDThietLap()
{
    delete table;
}