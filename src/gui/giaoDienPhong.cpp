#include "giaoDienPhong.h"

enum thuTuCot
{
    STT,
    MA_PHONG,
    LOAI_PHONG,
    HIEN_TAI,
    GIA_PHONG,
    MO_TA,
    XOA
};
enum cacNutTuyChon
{
    N_TAT_CA,
    N_PHONG_TRONG,
    N_DAY_PHONG
};
struct ngonNguHienThiGDP
{
    const char **roiRac;
    const char **noiDungNut;
};

namespace GDP
{
    const char *roiRacViet[30] = {"Thêm phòng", "Xóa tất cả", "Tìm kiếm", "STT", "Phòng", "Loại phòng", "Hiện tại", "Giá Phòng/Tháng", "Mô tả", "Xóa", "  Số danh sách trên bảng: ", "Xóa", "Tìm kiếm", "              Phòng không hợp lệ"};
    const char *noiDungNutViet[10] = {"Tất cả", "Phòng trống", "Phòng đầy"};

    const char *roiRacAnh[30] = {"Add room", "Delete all", "Search", "No.", "Room", "Room type", "Current", "Price per month", "Description", "Delete", "Number of items on the table:", "Delete", "Search", "Invalid room"};
    const char *noiDungNutAnh[10] = {"All", "Empty rooms", "Full rooms"};

    const char *roiRacNhat[30] = {"部屋を追加", "すべて削除", "検索", "番号", "部屋", "部屋タイプ", "現在", "月額料金", "説明", "削除", "表のリスト数:", "削除", "検索", "無効な部屋"};
    const char *noiDungNutNhat[10] = {"すべて", "空室", "満室"};
    const ngonNguHienThiGDP tiengViet{roiRacViet, noiDungNutViet};
    const ngonNguHienThiGDP tiengAnh{roiRacAnh, noiDungNutAnh};
    const ngonNguHienThiGDP tiengNhat{roiRacNhat, noiDungNutNhat};
}
const ngonNguHienThiGDP *chuGDP;
extern const Color *Mau;

giaoDienPhong ::giaoDienPhong(QuanLyKTX &quanLyKTX, HeThong &heThong) : giaoDien(quanLyKTX, heThong)
{
    switch (this->heThong->ngonNgu)
    {
    case 0:
        chuGDP = &GDP::tiengViet;
        break;
    case 1:
        chuGDP = &GDP::tiengAnh;
        break;
    case 2:
        chuGDP = &GDP::tiengNhat;
        break;
    }
    taoNutTuyChon();
    sohangBD = quanLyKTX.lDanhSachPhong().lSoPhanTu();
    // table
    flagTimKiem = false;
    chuoiTimSoSanh = "";
    table = nullptr;
    boxHTSoPhongOBang = hopChu({10, 70, 460, 40}, "", Mau[0], MAU_LA_CAY, Mau[2], font26);
    boxHTSoPhongOBang.cDoBoVien(0.3f);

    capNhatBang(quanLyKTX.lDanhSachPhong());
    // hộp xóa
    boxThem = hopChu({1030, 134, 210, 40}, chuGDP->roiRac[0], Mau[0], YELLOW, Mau[2]);
    boxThem.cKieuChu(font26);
    boxThem.cDoBoVien(0.3f);

    boxXoa = hopChu({1260, 134, 210, 40}, chuGDP->roiRac[1], RED, YELLOW, Mau[2]);
    boxXoa.cKieuChu(font26);
    boxXoa.cDoBoVien(0.3f);

    boxTimKiem = hopChu({70, 134, 400, 40}, "", Mau[0], YELLOW, Mau[8]);
    boxTimKiem.cKieuChu(font26);
    boxTimKiem.cFlagChuCoDinh(true);
    boxTimKiem.cChuCoDinh(chuGDP->roiRac[12]);
    boxTimKiem.cDoBoVien(0.3f);

    flagThongBaoKHL = false;
}
void giaoDienPhong::taoBang(const unsigned int &soDongToiDa)
{
    if (table != nullptr)
        delete table;

    table = new Bang({10, 200}, 7, soDongToiDa + 1, {250, 42});
    table->cTieuDe(true);
    table->cFlagCuon(true);
    table->cGianHangCot(3, 0);
    table->cKieuChu(font26, 26);
    table->cGioHanBD(table->lViTri().y, GetScreenHeight());
    table->cMauTheoHang(0, {46, 139, 87, 255});
    for (int i = 1; i < soDongToiDa; i++)
    {
        table->cMauTheoHang(i, {32, 178, 170, 255});
    }

    (*table)(0, STT).cNoiDung(chuGDP->roiRac[3]);
    (*table)(0, MA_PHONG).cNoiDung(chuGDP->roiRac[4]);
    (*table)(0, LOAI_PHONG).cNoiDung(chuGDP->roiRac[5]);
    (*table)(0, HIEN_TAI).cNoiDung(chuGDP->roiRac[6]);
    (*table)(0, GIA_PHONG).cNoiDung(chuGDP->roiRac[7]);
    (*table)(0, MO_TA).cNoiDung(chuGDP->roiRac[8]);
    (*table)(0, XOA).cNoiDung(chuGDP->roiRac[9]);

    table->cCot(STT, 60);
    table->cCot(MA_PHONG, 220);
    table->cCot(LOAI_PHONG, 170);
    table->cCot(HIEN_TAI, 170);
    table->cCot(GIA_PHONG, 230);
    table->cCot(MO_TA, 530);
    table->cCot(XOA, 80);
    for (int i = 0; i < soDongToiDa; i++)
    {
        (*table)(i, LOAI_PHONG).cChiNhapSo(true);
        (*table)(i, GIA_PHONG).cChiNhapSo(true);
    }
}
void giaoDienPhong::capNhatBang(const Vector<Phong> &dSPhong)
{

    sohangBD = dSPhong.lSoPhanTu() + boxThem.laDuocChon();

    static unsigned soDongBang = 0;
    if (soDongBang < sohangBD + 1 || table == nullptr) // cong 1 la them cai tieu de;
    {
        soDongBang = (sohangBD + 1) * 2; // gấp đôi lê hễ thêm 1 đối tượng thôi mà phải tạo lại thì không tốt cho lắm
        taoBang(soDongBang);
    }

    if (boxThem.laDuocChon())
    {
        Phong phongMatDinh;
        phongMatDinh.cGiaPhong(heThong->giaPhongMatDinh);
        capNhatDong(1, phongMatDinh);
    }
    unsigned demHangThoaMang = 0;
    int viTRiPhong;
    for (int i = 1 + boxThem.laDuocChon(); i <= sohangBD; i++)
    {
        viTRiPhong = i - 1 - boxThem.laDuocChon();

        if (cacNutChon.dSNut[N_DAY_PHONG].laRangBuoc())
        {
            if (!(dSPhong[viTRiPhong].lSoNguoiToiDa() == dSPhong[viTRiPhong].lSoNguoiHienTai()))
            {
                continue;
            }
        }
        else if (cacNutChon.dSNut[N_PHONG_TRONG].laRangBuoc())
        {
            if (!(dSPhong[viTRiPhong].lSoNguoiToiDa() > dSPhong[viTRiPhong].lSoNguoiHienTai()))
            {
                continue;
            }
        }
        capNhatDong(demHangThoaMang++ + 1 + boxThem.laDuocChon(), dSPhong[viTRiPhong]);
    }

    sohangBD = demHangThoaMang + boxThem.laDuocChon();
    boxHTSoPhongOBang.cNoiDung(chuGDP->roiRac[10] + to_string(sohangBD) + "/" + to_string(quanLyKTX.lDanhSachPhong().lSoPhanTu()));
}
void giaoDienPhong::taoNutTuyChon()
{
    const int soNut = 3;
    cacNutChon.dSNut = Vector<hopChu>(soNut);
    float chieuDaiO = 150;
    float khoangCachO = 20;

    for (int i = 0; i < cacNutChon.dSNut.lSoPhanTu(); i++)
    {
        cacNutChon.dSNut[i] = hopChu({515 + (chieuDaiO + khoangCachO) * i, 134, chieuDaiO, 40}, chuGDP->noiDungNut[i], Mau[0], YELLOW, Mau[2], font26);
        cacNutChon.dSNut[i].cDoBoVien(0.3f);
    }
}
void giaoDienPhong::capNhatDong(const int &viTri, const Phong &phong)
{
    (*table)(viTri, STT).cNoiDung(to_string(viTri));
    (*table)(viTri, MA_PHONG).cNoiDung(phong.lMaPhong());
    (*table)(viTri, LOAI_PHONG).cNoiDung(to_string(phong.lSoNguoiToiDa()));
    (*table)(viTri, HIEN_TAI).cNoiDung(to_string(phong.lSoNguoiHienTai()));
    (*table)(viTri, GIA_PHONG).cNoiDung(to_string(phong.lGiaPhong()));
    (*table)(viTri, MO_TA).cNoiDung(phong.lMoTa());
    (*table)(viTri, XOA).cNoiDung(chuGDP->roiRac[11]);
}
Phong giaoDienPhong::lPhongTuBang(const int &viTri) const
{
    string oSo = (*table)(viTri, 2).layChu();
    if (oSo == "")
        oSo += '0';
    Phong phong((*table)(viTri, 1).layChu(), stoi(oSo), (*table)(viTri, 5).layChu());
    phong.cSoNguoiHienTai(stoi((*table)(viTri, 3).layChu()));
    try
    {
        phong.cGiaPhong(stoul((*table)(viTri, GIA_PHONG).layChu()));
    }
    catch (const std::invalid_argument &e)
    {
        phong.cGiaPhong(0);
    }

    return phong;
}
void giaoDienPhong::capNhatDanhSachPhong()
{
    Vector2 dCLay = table->oHoatDong();
    int cot = dCLay.y, hang = dCLay.x;
    static Phong phongCu;
    static Phong phong;

    static bool flagDoiPhong = false;

    static Vector2 viTriCu = {-2, -2}; // cho số âm , và tại sao không -1 -1 đi thì -1 -1 là giá trị ô không hoạt đông bên kia trả về
    if ((viTriCu.x != dCLay.x || viTriCu.y != dCLay.y) && flagDoiPhong == true)
    {
        cout << "here" << endl;
        if (phongCu.lMaPhong() == "")
        {
            if (!quanLyKTX.themPhong(phong))
            {
                cout << "Phong khong hop le" << endl;
                flagThongBaoKHL = true;
            }
        }
        else if (!quanLyKTX.doiPhong(phongCu, phong))
        {
            cout << "sinh Vien khong hop le" << endl;
            capNhatDong(viTriCu.x, phongCu);
            flagThongBaoKHL = true;
        }
        flagDoiPhong = false;
    }
    if (hang != -1)
    {
        phong = lPhongTuBang(hang);
        if (MA_PHONG <= cot && cot <= MO_TA && flagDoiPhong == false)
        {
            phongCu = lPhongTuBang(hang);
            flagDoiPhong = true;
            viTriCu = dCLay;
        }
        else if (cot == XOA)
        {
            quanLyKTX.xoaPhong(phong.lMaPhong());
            capNhatBang(quanLyKTX.timPhongGiong(chuoiTimSoSanh));
            (*table)(hang, cot).cTrangThaiChon(false);
        }
    }
}
void giaoDienPhong::capNhatTT()
{

    table->capNhatTT();
    table->vungHoatDong(1, 1, sohangBD, 2);
    table->vungHoatDong(1, 4, sohangBD, 6);
    capNhatDanhSachPhong();

    boxThem.capNhatTT();
    boxXoa.capNhatTT();
    boxTimKiem.capNhatTT();
    cacNutChon.capNhatTT();
    static int nutChonHienTai;

    if (nutChonHienTai != cacNutChon.nutBiRangBuot)
    {
        nutChonHienTai = cacNutChon.nutBiRangBuot;
        capNhatBang(quanLyKTX.timPhongGiong(chuoiTimSoSanh));
    }

    if (boxThem.laDuocChon())
    {
        capNhatBang(quanLyKTX.timPhongGiong(chuoiTimSoSanh));
        boxThem.cTrangThaiChon(false);
    }
    if (boxXoa.laDuocChon())
    {
        quanLyKTX.xoaTatCaPhong();
        capNhatBang(quanLyKTX.timPhongGiong(chuoiTimSoSanh));
        boxXoa.cTrangThaiChon(false);
    }
    if (boxTimKiem.laDuocChon() && !flagTimKiem)
    {
        flagTimKiem = true;
    }
    if (!boxTimKiem.laDuocChon() && boxTimKiem.layChu() == "")
    {
        flagTimKiem = false;
    }

    if (boxTimKiem.laDuocChon() && chuoiTimSoSanh != boxTimKiem.layChu())
    {
        chuoiTimSoSanh = boxTimKiem.layChu();
        capNhatBang(quanLyKTX.timPhongGiong(chuoiTimSoSanh));
    }
}
void giaoDienPhong::bieuDien()
{
    table->bieuDien(STT, 0, sohangBD, XOA);
    boxTimKiem.bieuDien();
    boxThem.bieuDien();
    boxXoa.bieuDien();
    cacNutChon.bieuDien();
    boxHTSoPhongOBang.bieuDien();

    static double thoiGianHenThongBao = 0;
    if (flagThongBaoKHL)
    {
        cuaSoThongBaoKHL();
        if (GetTime() - thoiGianHenThongBao > 5.0)
        {
            thoiGianHenThongBao = GetTime();
        }
    }
    if (flagThongBaoKHL && (GetTime() - thoiGianHenThongBao > 4.0))
        flagThongBaoKHL = false;
}
void giaoDienPhong::cuaSoThongBaoKHL()
{
    hop nenSauCuaSo(Rectangle{1031, 57, 439, 70}, RED);
    hopChu chuThongBao(Rectangle{1036, 62, 429, 60}, chuGDP->roiRac[13], WHITE);
    chuThongBao.cKieuChu(font26);
    nenSauCuaSo.cDoBoVien(0.3f);
    chuThongBao.cDoBoVien(0.3f);

    nenSauCuaSo.bieuDien();
    chuThongBao.bieuDien();
}

giaoDienPhong::~giaoDienPhong()
{
    delete table;
}