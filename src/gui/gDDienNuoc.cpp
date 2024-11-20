#include "gDDienNuoc.h"
#include "tinyfiledialogs.h"
enum cotBang
{
    C_STT,
    C_M_PHONG,
    C_CS_DIEN_DT,
    C_CS_DIEN_CT,
    C_L_DIEN_TT,
    C_TIEN_DIEN,
    C_CS_NUOC_DT,
    C_CS_NUOC_CT,
    C_L_NUOC_TT,
    C_TIEN_NUOC,
    C_TONG_NOP,
    C_DA_NOP

};
enum nutTTNopTien
{
    TAT_CA,
    DA_NOP,
    CHUA_NOP,
};
#define SO_COT_BANG 12

struct hienThiChuGDDN
{
    const char **roiRac;
    const char **tieuDe;
    const char **noiDungNut;
};

namespace GDDN
{

    const char *roiRacViet[30] = {"Tìm kiếm", "Rồi", "Chưa", "Chưa", "Rồi", "  Số danh sách trên bảng: ", "Thiết lập lại", "Thiết lập giá điện nước", "Bậc ", "Mức bật điện", "Giá điện", "Giá nước", "Thiết lập lại", "Giá điện nước", "Tìm kiếm", "         Thiết lập lại tất cả", "Giữ cột CSCT và chuyển sang CSDT", " Xuất file"};
    const char *tieuDeViet[20] = {"STT", "Phòng", "Điện", "Nước", "Tổng nộp", "Đã nộp", "", "", "CSDT", "CSCT", "Lượng.TT", "T.Tiền", "CSDT", "CSCT", "Lượng.TT", "T.Tiền", "", "", ""};
    const char *noiDungNutViet[10] = {"Tất cả", "ĐÃ nộp", "Chưa nộp"};

    const char *roiRacAnh[30] = {"Search", "Done", "Not yet", "Not yet", "Done", "Number of items on the table:", "Reset", "Set electricity and water rates", "Tier", "Electricity tier", "Electricity price", "Water price", "Reset", "Elec & water prices", "Search", "Reset all", "Keep CSCT column and switch to CSDT", "Export file"};
    const char *tieuDeAnh[20] = {"No.", "Room", "Electricity", "Water", "Total payment", "Paid", "", "", "CSDT", "CSCT", "Usage", "Amount", "CSDT", "CSCT", "Usage", "Amount", "", "", ""};
    const char *noiDungNutAnh[10] = {"All", "Paid", "Unpaid"};

    const char *roiRacNhat[30] = {"検索", "済み", "まだ", "まだ", "済み", "表のリスト数:", "リセット", "電気と水道料金の設定", "レベル", "電気レベル", "電気料金", "水道料金", "リセット", "電気と水道料金", "検索", "すべてリセット", "CSCT列を保持してCSDTに切り替える", "ファイルを出力"};
    const char *tieuDeNhat[20] = {"番号", "部屋", "電気", "水道", "総支払", "支払済み", "", "", "CSDT", "CSCT", "使用量(電気)", "金額(電気)", "CSDT", "CSCT", "使用量(水道)", "金額(水道)", "", "", ""};
    const char *noiDungNutNhat[10] = {"すべて", "支払済み", "未払い"};

    hienThiChuGDDN tiengViet{roiRacViet, tieuDeViet, noiDungNutViet};
    hienThiChuGDDN tiengAnh{roiRacAnh, tieuDeAnh, noiDungNutAnh};
    hienThiChuGDDN tiengNhat{roiRacNhat, tieuDeNhat, noiDungNutNhat};

}
hienThiChuGDDN *chuGDDN;

gDDienNuoc ::gDDienNuoc(QuanLyKTX &quanLyKTX, HeThong &heThong) : giaoDien(quanLyKTX, heThong)
{

    switch (this->heThong->ngonNgu)
    {
    case 0:
        chuGDDN = &GDDN::tiengViet;
        break;
    case 1:
        chuGDDN = &GDDN::tiengAnh;
        break;
    case 2:
        chuGDDN = &GDDN::tiengNhat;
        break;
    }

    initDienNuoc(); // khởi tạo điện nước

    veKhoiTao();
}
void gDDienNuoc::initDienNuoc()
{
    const int soMucDien = 6, hMucBacDien = 0, hGiaDien = 1, hGiaNuoc = 2;
    for (int i = 0; i < soMucDien; i++)
    {
        mucBacDien[i] = heThong->bacGiaDien[i];
        giaTienDien[i] = heThong->giaDien[i];
    }
    giaTienNuoc = heThong->giaNuoc;
}
void gDDienNuoc::XuatFile()
{
    const char *filters[] = {"*.txt", "*.cpp", "*.h", 0};
    const char *tenMatDinh = "Tien_Dien_Nuoc.txt";
    const char *tieuDe = "Lưu file";
    char *duongDan = tinyfd_saveFileDialog(tieuDe, tenMatDinh, 1, filters, NULL);
    if (duongDan != NULL)
    {
        ghiFileVaoDiaChi(duongDan);
    }
}
void gDDienNuoc::ghiFileVaoDiaChi(const char *duongDan)
{
    ofstream ghiFile(duongDan, ios::out);

    cout << duongDan;
    ghiFile << "\t\t\tBan Kí túc xá xin Thông báo Tiền điện nước\n\n";

    for (int i = 0; i <= sohangBD; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            ghiFile << (*table)(i, j).layChu() << "\t";
        }
        ghiFile << "\n";
    }

    ghiFile.close();
}

void gDDienNuoc::capNhatTTChinh()
{
    table->capNhatTT();
    table->vungHoatDong(1, C_CS_DIEN_DT, sohangBD, C_CS_DIEN_CT);
    table->vungHoatDong(1, C_CS_NUOC_DT, sohangBD, C_CS_NUOC_CT);
    table->vungHoatDong(1, C_DA_NOP, sohangBD, C_DA_NOP);
    capNhatDanhSach(); // cap lai nhung gi nguoi dung nhap vao vao danh sach
    cacNutChon.capNhatTT();
    static int nutChonHienTai;

    boxXuatFile.capNhatTT();
    boxTimKiem.capNhatTT();
    if (nutChonHienTai != cacNutChon.nutBiRangBuot)
    {
        nutChonHienTai = cacNutChon.nutBiRangBuot;
        capNhatBang(quanLyKTX.timPhongGiong(chuoiTimSoSanh));
    }

    if (boxXuatFile.laDuocChon())
    {
        XuatFile();
        boxXuatFile.cTrangThaiChon(false);
    }
    else if (boxTimKiem.laDuocChon() && !flagTimKiem)
    {
        boxTimKiem.cNoiDung("");
        flagTimKiem = true;
    }

    if (!boxTimKiem.laDuocChon() && boxTimKiem.layChu() == "")
    {
        boxTimKiem.cNoiDung(chuGDDN->roiRac[0]);
        flagTimKiem = false;
    }
    // tìm kiếm
    if (boxTimKiem.laDuocChon() && chuoiTimSoSanh != boxTimKiem.layChu())
    {

        chuoiTimSoSanh = boxTimKiem.layChu();
        capNhatBang(quanLyKTX.timPhongGiong(boxTimKiem.layChu()));
    }
}
void gDDienNuoc::capNhatTT()
{

    // if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    //     cout << GetMouseY() << " ----- " << GetMouseX() << endl;

    boxReset.capNhatTT();
    boxSetGiaTien.capNhatTT();

    if (boxReset.laDuocChon())
    {
        boxReset.cRangBuoc(true);
        boxReset.cTrangThaiChon(false);
    }
    else if (boxSetGiaTien.laDuocChon())
    {
        kTBangNhapGia();
        boxSetGiaTien.cRangBuoc(true);
        boxSetGiaTien.cTrangThaiChon(false);
    }

    if (boxReset.laRangBuoc())
    {
        cSResetCapNhatTT();
    }
    else if (boxSetGiaTien.laRangBuoc())
    {
        cSTLGiaTienCapNhatTT();
    }
    else
    {
        capNhatTTChinh();
    }
}
void gDDienNuoc::capNhatDanhSach()
{
    Vector2 viTriMoi = table->oHoatDong();
    int cot = viTriMoi.y, hang = viTriMoi.x;
    if (hang != -1)
    {
        Phong phongChinhSua = *quanLyKTX.timPhong((*table)(hang, C_M_PHONG).layChu());
        phongChinhSua.cDienCSDT(stringSangFloat((*table)(hang, C_CS_DIEN_DT).layChu()));
        phongChinhSua.cDienCSCT(stringSangFloat((*table)(hang, C_CS_DIEN_CT).layChu()));
        phongChinhSua.cNuocCSDT(stringSangFloat((*table)(hang, C_CS_NUOC_DT).layChu()));
        phongChinhSua.cNuocCSCT(stringSangFloat((*table)(hang, C_CS_NUOC_CT).layChu()));
        if (cot == C_DA_NOP)
        {
            string daNopTien = chuGDDN->roiRac[1];
            bool boolDaNopTien = true;
            if (phongChinhSua.daNopTienDN())
            {
                daNopTien = chuGDDN->roiRac[2];
                boolDaNopTien = false;
            }
            phongChinhSua.cNopTienDN(boolDaNopTien);
            (*table)(hang, C_DA_NOP).cNoiDung(daNopTien);
            (*table)(hang, C_DA_NOP).cTrangThaiChon(false);
        }
        quanLyKTX.doiPhong(phongChinhSua, phongChinhSua); // tham số dầu chỉ cần lấy mã phòng từ đó ma phòng truy ra phòng và được gán lại  bởi tham số thứ hai
        capNhatTinhToan(hang, *quanLyKTX.timPhong((*table)(hang, 1).layChu()));
    }
}
void gDDienNuoc::bieuDien()
{
    cacNutChon.bieuDien();
    boxHTSoPhongOBang.bieuDien();
    table->bieuDien(0, 0, sohangBD, 11);
    thanhDienNuoc->bieuDien(0, 0, 0, 5);
    boxTimKiem.bieuDien();
    boxReset.bieuDien();
    boxXuatFile.bieuDien();
    boxSetGiaTien.bieuDien();

    if (boxReset.laRangBuoc())
        cSResetBieuDien();
    if (boxSetGiaTien.laRangBuoc())
        cSTLGiaTienBieuDien();
}

gDDienNuoc::~gDDienNuoc()
{
    delete thanhDienNuoc;
    delete table;
}
void gDDienNuoc::capNhatTinhToan(const int &vTriBang, const Phong &phong)
{
    float luongDienTT, luongNuocTT, tienDien = 0, tienNuoc = 0;
    luongDienTT = phong.lDienCSCT() - phong.lDienCSDT();
    luongNuocTT = phong.lNuocCSCT() - phong.lNuocCSDT();
    // chuổi có 6 chữa số tương ứng với 6 bậc điện
    if (mucBacDien[0] < luongDienTT)
    {
        int j;
        tienDien += mucBacDien[0] * giaTienDien[0];
        for (j = 1; j < 5 && mucBacDien[j] < luongDienTT; j++)
        {
            tienDien += (mucBacDien[j] - mucBacDien[j - 1]) * giaTienDien[j];
        }
        tienDien += (luongDienTT - mucBacDien[j - 1]) * giaTienDien[j];
    }
    else
    {
        tienDien = luongDienTT * giaTienDien[0];
    }
    tienNuoc = giaTienNuoc * luongNuocTT;
    (*table)(vTriBang, 4).cNoiDung(floatSangString(luongDienTT));
    (*table)(vTriBang, 5).cNoiDung(floatSangString(tienDien));
    (*table)(vTriBang, 8).cNoiDung(floatSangString(luongNuocTT));
    (*table)(vTriBang, 9).cNoiDung(floatSangString(tienNuoc));
    (*table)(vTriBang, 10).cNoiDung(floatSangString(tienNuoc + tienDien));
}
void gDDienNuoc::capNhatDong(const int &viTri, const Phong &phong)
{
    string nopTien = chuGDDN->roiRac[3];
    if (phong.daNopTienDN())
        nopTien = chuGDDN->roiRac[4];
    (*table)(viTri, C_STT).cNoiDung(to_string(viTri));
    (*table)(viTri, C_M_PHONG).cNoiDung(phong.lMaPhong());
    (*table)(viTri, C_CS_DIEN_DT).cNoiDung(floatSangString(phong.lDienCSDT()));
    (*table)(viTri, C_CS_DIEN_CT).cNoiDung(floatSangString(phong.lDienCSCT()));
    (*table)(viTri, C_CS_NUOC_DT).cNoiDung(floatSangString(phong.lNuocCSDT()));
    (*table)(viTri, C_CS_NUOC_CT).cNoiDung(floatSangString(phong.lNuocCSCT()));
    (*table)(viTri, C_DA_NOP).cNoiDung(nopTien);
    capNhatTinhToan(viTri, phong);
}
void gDDienNuoc::capNhatBang(const Vector<Phong> &dSPhong)
{
    sohangBD = dSPhong.lSoPhanTu();
    unsigned demHangThoaMang = 0;
    int viTRiPhong;
    for (int i = 1; i <= sohangBD; i++)
    {
        viTRiPhong = i - 1;
        if (cacNutChon.dSNut[DA_NOP].laRangBuoc())
        {
            if (!(dSPhong[viTRiPhong].daNopTienDN()))
            {
                continue;
            }
        }
        else if (cacNutChon.dSNut[CHUA_NOP].laRangBuoc())
        {
            if (dSPhong[viTRiPhong].daNopTienDN())
            {
                continue;
            }
        }
        capNhatDong(demHangThoaMang++ + 1, dSPhong[viTRiPhong]);
    }
    sohangBD = demHangThoaMang;
    boxHTSoPhongOBang.cNoiDung(chuGDDN->roiRac[5] + to_string(sohangBD) + "/" + to_string(quanLyKTX.lDanhSachPhong().lSoPhanTu()));
}

void gDDienNuoc::taoNutTuyChon()
{
    const int soNut = 3;
    cacNutChon.dSNut = Vector<hopChu>(soNut);
    float chieuDaiO = 110;
    float khoangCachO = 20;

    for (int i = 0; i < cacNutChon.dSNut.lSoPhanTu(); i++)
    {
        cacNutChon.dSNut[i] = hopChu({450 + (chieuDaiO + khoangCachO) * i, 134, chieuDaiO, 40}, chuGDDN->noiDungNut[i], BLUE, YELLOW, BLACK, font26);
        cacNutChon.dSNut[i].cDoBoVien(0.3f);
    }
}
void gDDienNuoc::resetCapNhatTT()
{

    boxResetHet.capNhatTT();
    boxResetCoLay.capNhatTT();
    if (boxResetHet.laDuocChon())
    {
        quanLyKTX.resetChiSoDienNuoc(THIET_LAP_TAT_CA);
        boxResetHet.cTrangThaiChon(false);
        capNhatBang(quanLyKTX.lDanhSachPhong());
    }
    else if (boxResetCoLay.laDuocChon())
    {
        quanLyKTX.resetChiSoDienNuoc(CHUYEN_CSCT_SANG_CSDT);
        boxResetCoLay.cTrangThaiChon(false);
        capNhatBang(quanLyKTX.lDanhSachPhong());
    }
}
// tạo ra của sổ nhỏ phái sau tái sử dụng cho nhiều mục khác
void gDDienNuoc::cuaSoCon(const float &chieuDai, const float &chieuRong, const string &tenTieuDe)
{
    hopChu tieuDe({(GetScreenWidth() - chieuDai) / 2.0f, (GetScreenHeight() - chieuRong) / 2.0f, chieuDai, nutTat.layKichCo().y}, tenTieuDe, MAU_XANH);
    nutTat.cVitri((GetScreenWidth() - chieuDai) / 2.0f + chieuDai - nutTat.layKichCo().x, (GetScreenHeight() - chieuRong) / 2.0f);
    tieuDe.cKieuChu(font26);

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), MAU_DEN_MO);
    DrawRectangle((GetScreenWidth() - chieuDai) / 2.0f, (GetScreenHeight() - chieuRong) / 2.0f, chieuDai, chieuRong, MAU_LA_CAY);
    tieuDe.bieuDien();
    nutTat.bieuDien();
}

void gDDienNuoc::cSResetBieuDien()
{
    cuaSoCon(900, 350, chuGDDN->roiRac[6]); // dùng để vẽ ra của sổ phía sau
    boxResetHet.bieuDien();
    boxResetCoLay.bieuDien();
}
void gDDienNuoc::cSResetCapNhatTT()
{
    resetCapNhatTT();
    nutTat.capNhatTT();
    if (nutTat.laDuocChon())
    {
        boxReset.cRangBuoc(false);
    }
}
void gDDienNuoc::cSTLGiaTienBieuDien()
{
    cuaSoCon(1200, 600, chuGDDN->roiRac[7]);
    BangSetGiaTienDien->bieuDien(0, 0, BangSetGiaTienDien->lSoHang() - 1, BangSetGiaTienDien->lSoCot() - 1);
}
void gDDienNuoc::cSTLGiaTienCapNhatTT()
{
    BangSetGiaTienDien->vungHoatDong(1, 1, BangSetGiaTienDien->lSoHang() - 1, BangSetGiaTienDien->lSoCot() - 3);
    (*BangSetGiaTienDien)(1, 4).capNhatTT();

    Vector2 dCLay = BangSetGiaTienDien->oHoatDong();
    int hang = dCLay.x, cot = dCLay.y;
    const int soMucDien = 6, hMucBacDien = 0, hGiaDien = 1, hGiaNuoc = 2;
    if (dCLay.x != -1)
    {
        string chuoiVuaNhap = (*BangSetGiaTienDien)(hang, cot).layChu();
        if (chuoiVuaNhap == "") // nếu chuổi rổng thì cộng thêm '0' vì nếu chuổi rổng stringSangFloat() sẽ không chuyển qua được gây ra lỗi
            chuoiVuaNhap += '0';
        float soVuaNhap = stringSangFloat(chuoiVuaNhap);
        switch (int(dCLay.y))
        {
        case 1:
            mucBacDien[hang - 1] = soVuaNhap;
            heThong->bacGiaDien[hang - 1] = stoi(chuoiVuaNhap);
            break;
        case 2:
            giaTienDien[hang - 1] = soVuaNhap;
            heThong->giaDien[hang - 1] = stoul(chuoiVuaNhap);
            break;
        case 4:
            giaTienNuoc = soVuaNhap;
            heThong->giaNuoc = stoul(chuoiVuaNhap);
            break;
        }
    }

    nutTat.capNhatTT();
    if (nutTat.laDuocChon())
    {
        delete BangSetGiaTienDien;
        capNhatBang(quanLyKTX.lDanhSachPhong());
        BangSetGiaTienDien = nullptr;
        boxSetGiaTien.cRangBuoc(false);
    }
}
void gDDienNuoc::kTBangNhapGia()
{
    if (BangSetGiaTienDien == nullptr)
    {
        BangSetGiaTienDien = new Bang({281, 221}, 5, 7, {180, 40});
        BangSetGiaTienDien->cGianHangCot(30, 10);
        BangSetGiaTienDien->cCot(0, 90);
        BangSetGiaTienDien->cKieuChu(font26);
        BangSetGiaTienDien->cMauTheoCot(0, MAU_LA_CAY);
        BangSetGiaTienDien->cMauTheoCot(3, MAU_LA_CAY);
        BangSetGiaTienDien->cMauTheoCot(4, MAU_LA_CAY);

        BangSetGiaTienDien->cMauTheoHang(0, MAU_LA_CAY);
        string vietVaoO = chuGDDN->roiRac[8];
        for (int i = 1; i <= 6; i++)
        {
            (*BangSetGiaTienDien)(i, 0).cNoiDung(vietVaoO + to_string(i));
            (*BangSetGiaTienDien)(i, 1).cNoiDung(floatSangString(mucBacDien[i - 1]));
            (*BangSetGiaTienDien)(i, 2).cNoiDung(floatSangString(giaTienDien[i - 1]));
            (*BangSetGiaTienDien)(i, 1).cChiNhapSo(true);
            (*BangSetGiaTienDien)(i, 2).cChiNhapSo(true);
        }
        (*BangSetGiaTienDien)(0, 1).cNoiDung(chuGDDN->roiRac[9]);
        (*BangSetGiaTienDien)(0, 2).cNoiDung(chuGDDN->roiRac[10]);
        (*BangSetGiaTienDien)(0, 4).cNoiDung(chuGDDN->roiRac[11]);
        (*BangSetGiaTienDien)(1, 4).cNoiDung(floatSangString(giaTienNuoc));
        (*BangSetGiaTienDien)(1, 4).cMauNen(WHITE);
        (*BangSetGiaTienDien)(1, 4).cChiNhapSo(true);
    }
}
void gDDienNuoc::veKhoiTao()
{
    taoNutTuyChon();
    boxHTSoPhongOBang = hopChu({10, 70, 540, 40}, "", WHITE, MAU_LA_CAY, BLACK, font26);
    boxHTSoPhongOBang.cDoBoVien(0.3f);
    boxHTSoPhongOBang.cRangBuoc(true);
    // tạo thanh điện nước
    thanhDienNuoc = new Bang({10, 200}, 6, 1, {250, 42});
    thanhDienNuoc->cKieuChu(font26, 26);
    thanhDienNuoc->cMauTheoHang(0, MAU_XANH);

    int soDongToiDa = quanLyKTX.lDanhSachPhong().lSoPhanTu() + 1;

    flagTimKiem = false;
    chuoiTimSoSanh = "";
    //{vị trí}, số cột, số dòng + tiêu đề, {kích cở mặt định của các ô} / 12 cot
    table = new Bang({10, 236}, 12, soDongToiDa, {250, 42});
    table->cTieuDe(true);
    table->cFlagCuon(true);
    // table->cGianHangCot(0, 2);
    table->cKieuChu(font26, 26);
    table->cGioHanBD(table->lViTri().y, GetScreenHeight()); // đặt giới hạn vì không thể vẽ hết tất các các ô, nếu vẽ hêt tức những ô ra ngoài vùng cửa sổ vũng vẽ => dư thừa và hiệu suất kém

    // Thiết lập tiêu đề cho bảng và thanh tiêu đề  cột
    const int chieuDaiO[18] = {60, 120, 490, 490, 200, 100, 60, 120, 110, 110, 120, 150, 110, 110, 120, 150, 200, 100};
    for (int i = 0; i < 6; i++)
    {
        thanhDienNuoc->cCot(i, chieuDaiO[i]);
        (*thanhDienNuoc)(0, i).cNoiDung(chuGDDN->tieuDe[i]);
    }
    for (int i = 6; i < 18; i++)
    {
        table->cCot(i - 6, chieuDaiO[i]);
        (*table)(0, i - 6).cNoiDung(chuGDDN->tieuDe[i]);
    }
    // thiết lập ô chỉ nhập số
    for (int i = 0; i < soDongToiDa; i++)
    {
        (*table)(i, C_CS_DIEN_DT).cChiNhapSo(true);
        (*table)(i, C_CS_DIEN_CT).cChiNhapSo(true);
        (*table)(i, C_CS_NUOC_DT).cChiNhapSo(true);
        (*table)(i, C_CS_NUOC_CT).cChiNhapSo(true);
    }
    // chỉnh màu theo cột
    for (int i = 0; i < SO_COT_BANG; i++)
    {
        if (i == C_CS_DIEN_CT || i == C_CS_DIEN_DT || i == C_CS_NUOC_DT || i == C_CS_NUOC_CT || i == C_DA_NOP)
            table->cMauTheoCot(i, ORANGE);
        else
            table->cMauTheoCot(i, YELLOW);
    }
    table->cMauTheoHang(0, MAU_LA_CAY);
    capNhatBang(quanLyKTX.lDanhSachPhong());

    boxReset = hopChu({1260, 134, 170, 40}, chuGDDN->roiRac[12], RED, YELLOW);
    boxReset.cKieuChu(font26);
    boxReset.cDoBoVien(0.3f);

    boxSetGiaTien = hopChu({1070, 134, 170, 40}, chuGDDN->roiRac[13], BLUE, YELLOW);
    boxSetGiaTien.cKieuChu(font26);
    boxSetGiaTien.cDoBoVien(0.3f);

    boxTimKiem = hopChu({30, 134, 370, 40}, chuGDDN->roiRac[14], BLUE, YELLOW, BLACK);
    boxTimKiem.cKieuChu(font26);
    boxTimKiem.cDoBoVien(0.3f);

    boxResetHet = hopChu({(GetScreenWidth() - 560) / 2.0f, (GetScreenHeight() - 60) / 2.0f - 40, 560, 60}, chuGDDN->roiRac[15]);
    boxResetHet.cKieuChu(font26);
    boxResetHet.cDoBoVien(0.3f);

    boxResetCoLay = hopChu({(GetScreenWidth() - 560) / 2.0f, (GetScreenHeight() - 60) / 2.0f + 70, 560, 60}, chuGDDN->roiRac[16]);
    boxResetCoLay.cKieuChu(font26);
    boxResetCoLay.cDoBoVien(0.3f);

    nutTat = hop({0, 0, 60, 30}, RED);

    BangSetGiaTienDien = nullptr;

    boxXuatFile = hopChu({880, 134, 170, 40}, chuGDDN->roiRac[17], BLUE, YELLOW);
    boxXuatFile.cKieuChu(font26);
    boxXuatFile.cDoBoVien(0.3f);
}