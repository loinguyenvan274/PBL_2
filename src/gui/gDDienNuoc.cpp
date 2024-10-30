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

#define SO_COT_BANG 12

gDDienNuoc ::gDDienNuoc(QuanLyKTX &quanLyKTX, Vector<Vector<string>> &heThong) : giaoDien(quanLyKTX)
{
    this->heThong = &heThong;

    initDienNuoc(); // khởi tạo điện nước

    veKhoiTao();
}
void gDDienNuoc::initDienNuoc()
{
    const int soMucDien = 6, hMucBacDien = 0, hGiaDien = 1, hGiaNuoc = 2;
    for (int i = 0; i < soMucDien; i++)
    {
        mucBacDien[i] = stoi((*heThong)[hMucBacDien][i]);
        giaTienDien[i] = stod((*heThong)[hGiaDien][i]);
    }
    giaTienNuoc = stod((*heThong)[hGiaNuoc][0]);
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

void gDDienNuoc::capNhatTT()
{

    // if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    //     cout << GetMouseY() << " ----- " << GetMouseX() << endl;

    capNhatBang();
    // boxReset.capNhatTT();
    // if (boxReset.laDuocChon())
    //     boxReset.cRangBuoc(true);
    // if (boxReset.laRangBuoc())
    //     cSResetCapNhatTT();

    // boxSetGiaTien.capNhatTT();
    // if (boxSetGiaTien.laDuocChon())
    // {
    //     kTBangNhapGia();
    //     boxSetGiaTien.cRangBuoc(true);
    // }
    // if (boxSetGiaTien.laRangBuoc())
    //     cSTLGiaTienCapNhatTT();

    // boxXuatFile.capNhatTT();
    // if (boxXuatFile.laDuocChon())
    // {
    //     XuatFile();
    //     boxXuatFile.cTrangThaiChon(false);
    // }

    // boxTimKiem.capNhatTT();
    // if (boxTimKiem.laDuocChon() && !flagTimKiem)
    // {
    //     boxTimKiem.cNoiDung("");
    //     flagTimKiem = true;
    // }
    // if (!boxTimKiem.laDuocChon() && boxTimKiem.layChu() == "")
    // {
    //     boxTimKiem.cNoiDung("          Tìm kiếm");
    //     flagTimKiem = false;
    // }
    // // tìm kiếm
    // if (boxTimKiem.laDuocChon() && chuoiTimSoSanh != boxTimKiem.layChu())
    // {
    //     soDoiTuongTim = 0;
    //     chuoiTimSoSanh = boxTimKiem.layChu();

    //     for (int i = 0; i < soPhong; i++)
    //     {
    //         if ((*qLPhong)[i].lMaPhong().find(boxTimKiem.layChu()) != string::npos || boxTimKiem.layChu() == "")
    //         {
    //             viTriLuu[soDoiTuongTim++] = i;
    //         }
    //     }
    //     capNhatThuTu();
    // }
}
void gDDienNuoc::bieuDien()
{
    table->bieuDien(0, 0, sohangBD, 11);
    thanhDienNuoc->bieuDien(0, 0, 0, 5);
    boxTimKiem.bieuDien();
    boxReset.bieuDien();
    boxXuatFile.bieuDien();
    boxSetGiaTien.bieuDien();

    //     if (boxReset.laRangBuoc())
    //         cSResetBieuDien();
    //     if (boxSetGiaTien.laRangBuoc())
    //         cSTLGiaTienBieuDien();
}

gDDienNuoc::~gDDienNuoc()
{
    delete thanhDienNuoc;
    delete table;
}
void gDDienNuoc::capNhatTinhToan(const int &vTriBang, const Phong &phong)
{
    float luongDienTT, luongNuocTT, tienDien = 0, tienNuoc = 0;
    luongDienTT = (*qLPhong)[vTriDanhSach].lDienCSCT() - (*qLPhong)[vTriDanhSach].lDienCSDT();
    luongNuocTT = (*qLPhong)[vTriDanhSach].lNuocCSCT() - (*qLPhong)[vTriDanhSach].lNuocCSDT();
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
    (*table)(vTriBang, 4).cNoiDung(float_string(luongDienTT));
    (*table)(vTriBang, 5).cNoiDung(float_string(tienDien));
    (*table)(vTriBang, 8).cNoiDung(float_string(luongNuocTT));
    (*table)(vTriBang, 9).cNoiDung(float_string(tienNuoc));
    (*table)(vTriBang, 10).cNoiDung(float_string(tienNuoc + tienDien));
}
// void gDDienNuoc::capNhatThuTu()
// {
//     int vTriDanhSach;
//     if (flagTimKiem)
//         sohangBD = soDoiTuongTim;
//     else
//         sohangBD = soPhong;

//     for (int vTriBang = 1; vTriBang <= sohangBD; vTriBang++)
//     {
//         if (flagTimKiem)
//             vTriDanhSach = viTriLuu[vTriBang - 1];
//         else
//             vTriDanhSach = vTriBang - 1;

//         (*table)(vTriBang, C_STT).cNoiDung(to_string(vTriBang));
//         (*table)(vTriBang, C_M_PHONG).cNoiDung((*qLPhong)[vTriDanhSach].lMaPhong());
//         (*table)(vTriBang, C_CS_DIEN_DT).cNoiDung(float_string((*qLPhong)[vTriDanhSach].lDienCSDT()));
//         (*table)(vTriBang, C_CS_DIEN_CT).cNoiDung(float_string((*qLPhong)[vTriDanhSach].lDienCSCT()));
//         (*table)(vTriBang, C_CS_NUOC_DT).cNoiDung(float_string((*qLPhong)[vTriDanhSach].lNuocCSDT()));
//         (*table)(vTriBang, C_CS_NUOC_CT).cNoiDung(float_string((*qLPhong)[vTriDanhSach].lNuocCSCT()));
//         capNhatTinhToan(vTriBang, vTriDanhSach);
//         if ((*qLPhong)[vTriDanhSach].daNopTienDN())
//             (*table)(vTriBang, C_DA_NOP).cNoiDung("Rồi");
//         else
//             (*table)(vTriBang, C_DA_NOP).cNoiDung("Chưa");
//     }
// }
void gDDienNuoc::capNhatDong(const int &viTri, const Phong &phong)
{
    string nopTien = "Chưa";
    if (phong.daNopTienDN())
        nopTien = "Rồi";
    (*table)(viTri, C_STT).cNoiDung(to_string(viTri));
    (*table)(viTri, C_M_PHONG).cNoiDung(phong.lMaPhong());
    (*table)(viTri, C_CS_DIEN_DT).cNoiDung(float_string(phong.lDienCSDT()));
    (*table)(viTri, C_CS_DIEN_CT).cNoiDung(float_string(phong.lDienCSCT()));
    (*table)(viTri, C_CS_NUOC_DT).cNoiDung(float_string(phong.lNuocCSDT()));
    (*table)(viTri, C_CS_NUOC_CT).cNoiDung(float_string(phong.lNuocCSCT()));
    (*table)(viTri, C_DA_NOP).cNoiDung(nopTien);
    capNhatTinhToan(viTri, phong);
}
void gDDienNuoc::capNhatBang(const Vector<Phong> &phong)
{

    //     Vector2 dCLay = table->oHoatDong();
    //     int c = dCLay.y, h = dCLay.x, vT = h - 1;
    //     if (flagTimKiem)
    //         vT = viTriLuu[h - 1];
    //     if (h != -1 && chuoiMoi != (*table)(h, c).layChu())
    //     {
    //         chuoiMoi = (*table)(h, c).layChu();
    //         if (chuoiMoi == "") // nếu chuổi rổng thì cộng thêm '0' vì nếu chuổi rổng stof() sẽ không chuyển qua được gây ra lỗi
    //             chuoiMoi += '0';
    //         switch (c)
    //         {
    //         case C_CS_DIEN_DT:
    //             (*qLPhong)[vT].cDienCSDT(stof(chuoiMoi));
    //             break;
    //         case C_CS_DIEN_CT:
    //             (*qLPhong)[vT].cDienCSCT(stof(chuoiMoi));
    //             break;
    //         case C_CS_NUOC_DT:
    //             (*qLPhong)[vT].cNuocCSDT(stof(chuoiMoi));
    //             break;
    //         case C_CS_NUOC_CT:
    //             (*qLPhong)[vT].cNuocCSCT(stof(chuoiMoi));
    //             break;
    //         }
    //         capNhatTinhToan(h, vT);
    //     }
    //     if (c == C_DA_NOP)
    //     {
    //         if ((*qLPhong)[vT].daNopTienDN())
    //         {
    //             (*qLPhong)[vT].cNopTienDN(false);
    //             (*table)(h, c).cNoiDung("Chưa");
    //         }
    //         else
    //         {
    //             (*qLPhong)[vT].cNopTienDN(true);
    //             (*table)(h, c).cNoiDung("Rồi");
    //         }
    //         (*table)(h, c).cTrangThaiChon(false);
    //     }
}

// void gDDienNuoc::resetCapNhatTT()
// {

//     boxResetHet.capNhatTT();
//     boxResetCoLay.capNhatTT();
//     if (boxResetHet.laDuocChon())
//     {
//         for (int i = 0; i < (*qLPhong).lSoPhanTu(); i++)
//         {
//             (*qLPhong)[i].cDienCSDT(0.0f);
//             (*qLPhong)[i].cNuocCSDT(0.0f);
//             (*qLPhong)[i].cDienCSCT(0.0f);
//             (*qLPhong)[i].cNuocCSCT(0.0f);
//             (*qLPhong)[i].cNopTienDN(false);
//         }
//         capNhatThuTu();
//         boxResetHet.cTrangThaiChon(false);
//     }
//     else if (boxResetCoLay.laDuocChon())
//     {
//         for (int i = 0; i < (*qLPhong).lSoPhanTu(); i++)
//         {
//             (*qLPhong)[i].cDienCSDT((*qLPhong)[i].lDienCSCT());
//             (*qLPhong)[i].cNuocCSDT((*qLPhong)[i].lNuocCSCT());
//             (*qLPhong)[i].cDienCSCT(0.0f);
//             (*qLPhong)[i].cNuocCSCT(0.0f);
//             (*qLPhong)[i].cNopTienDN(false);
//         }
//         capNhatThuTu();
//         boxResetCoLay.cTrangThaiChon(false);
//     }
// }
// tạo ra của sổ nhỏ phái sau tái sử dụng cho nhiều mục khác
// void gDDienNuoc::cuaSoCon(const float &chieuDai, const float &chieuRong, const string &tenTieuDe)
// {
//     hopChu tieuDe({(GetScreenWidth() - chieuDai) / 2.0f, (GetScreenHeight() - chieuRong) / 2.0f, chieuDai, nutTat.layKichCo().y}, tenTieuDe, MAU_XANH);
//     nutTat.cVitri((GetScreenWidth() - chieuDai) / 2.0f + chieuDai - nutTat.layKichCo().x, (GetScreenHeight() - chieuRong) / 2.0f);
//     tieuDe.cKieuChu(font28);

//     DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), MAU_DEN_MO);
//     DrawRectangle((GetScreenWidth() - chieuDai) / 2.0f, (GetScreenHeight() - chieuRong) / 2.0f, chieuDai, chieuRong, MAU_LA_CAY);
//     tieuDe.bieuDien();
//     nutTat.bieuDien();
// }

// void gDDienNuoc::cSResetBieuDien()
// {
//     cuaSoCon(900, 350, "                       Thiết lập lại"); // dùng để vẽ ra của sổ phía sau
//     boxResetHet.bieuDien();
//     boxResetCoLay.bieuDien();
// }
// void gDDienNuoc::cSResetCapNhatTT()
// {
//     resetCapNhatTT();
//     nutTat.capNhatTT();
//     if (nutTat.laDuocChon())
//     {
//         boxReset.cRangBuoc(false);
//     }
// }
// void gDDienNuoc::cSTLGiaTienBieuDien()
// {
//     cuaSoCon(1000, 600, "      Thiết lập giá điện nước");
//     BangSetGiaTienDien->bieuDien(0, 0, BangSetGiaTienDien->lSoHang() - 1, BangSetGiaTienDien->lSoCot() - 1);
// }
// void gDDienNuoc::cSTLGiaTienCapNhatTT()
// {
//     BangSetGiaTienDien->vungHoatDong(1, 1, BangSetGiaTienDien->lSoHang() - 1, BangSetGiaTienDien->lSoCot() - 3);
//     (*BangSetGiaTienDien)(1, 4).capNhatTT();

//     Vector2 dCLay = BangSetGiaTienDien->oHoatDong();
//     int hang = dCLay.x, cot = dCLay.y;
//     const int soMucDien = 6, hMucBacDien = 0, hGiaDien = 1, hGiaNuoc = 2;
//     if (dCLay.x != -1)
//     {
//         string chuoiVuaNhap = (*BangSetGiaTienDien)(hang, cot).layChu();
//         if (chuoiVuaNhap == "") // nếu chuổi rổng thì cộng thêm '0' vì nếu chuổi rổng stof() sẽ không chuyển qua được gây ra lỗi
//             chuoiVuaNhap += '0';
//         float soVuaNhap = stof(chuoiVuaNhap);
//         switch (int(dCLay.y))
//         {
//         case 1:
//             mucBacDien[hang - 1] = soVuaNhap;
//             (*heThong)[hMucBacDien][hang - 1] = chuoiVuaNhap;
//             break;
//         case 2:
//             giaTienDien[hang - 1] = soVuaNhap;
//             (*heThong)[hGiaDien][hang - 1] = chuoiVuaNhap;
//             break;
//         case 4:
//             giaTienNuoc = soVuaNhap;
//             (*heThong)[hGiaNuoc][0] = chuoiVuaNhap;
//             break;
//         }
//         capNhatThuTu();
//     }

//     nutTat.capNhatTT();
//     if (nutTat.laDuocChon())
//     {
//         delete BangSetGiaTienDien;
//         BangSetGiaTienDien = nullptr;
//         boxSetGiaTien.cRangBuoc(false);
//     }
// }
// void gDDienNuoc::kTBangNhapGia()
// {
//     if (BangSetGiaTienDien == nullptr)
//     {
//         BangSetGiaTienDien = new Bang({281, 221}, 5, 7, {180, 40});
//         BangSetGiaTienDien->cGianHangCot(30, 10);
//         BangSetGiaTienDien->cCot(0, 90);
//         BangSetGiaTienDien->cKieuChu(font28);
//         BangSetGiaTienDien->cMauTheoCot(0, MAU_LA_CAY);
//         BangSetGiaTienDien->cMauTheoCot(3, MAU_LA_CAY);
//         BangSetGiaTienDien->cMauTheoCot(4, MAU_LA_CAY);

//         BangSetGiaTienDien->cMauTheoHang(0, MAU_LA_CAY);
//         string vietVaoO = "Bậc ";
//         for (int i = 1; i <= 6; i++)
//         {
//             (*BangSetGiaTienDien)(i, 0).cNoiDung(vietVaoO + to_string(i));
//             (*BangSetGiaTienDien)(i, 1).cNoiDung(float_string(mucBacDien[i - 1]));
//             (*BangSetGiaTienDien)(i, 2).cNoiDung(float_string(giaTienDien[i - 1]));
//             (*BangSetGiaTienDien)(i, 1).cChiNhapSo(true);
//             (*BangSetGiaTienDien)(i, 2).cChiNhapSo(true);
//         }
//         (*BangSetGiaTienDien)(0, 1).cNoiDung("Mức bật điện");
//         (*BangSetGiaTienDien)(0, 2).cNoiDung("  Giá điện");
//         (*BangSetGiaTienDien)(0, 4).cNoiDung("  Giá nước");
//         (*BangSetGiaTienDien)(1, 4).cNoiDung(float_string(giaTienNuoc));
//         (*BangSetGiaTienDien)(1, 4).cMauNen(WHITE);
//         (*BangSetGiaTienDien)(1, 4).cChiNhapSo(true);
//     }
// }
void gDDienNuoc::veKhoiTao()
{
    // tạo thanh điện nước
    thanhDienNuoc = new Bang({10, 200}, 6, 1, {250, 36});
    thanhDienNuoc->cKieuChu(font28, 26);
    thanhDienNuoc->cMauTheoHang(0, MAU_XANH);

    int soDongToiDa = 10000;

    flagTimKiem = false;
    chuoiTimSoSanh = "";
    //{vị trí}, số cột, số dòng + tiêu đề, {kích cở mặt định của các ô} / 12 cot
    table = new Bang({10, 236}, 12, soDongToiDa, {250, 36});
    table->cTieuDe(true);
    table->cFlagCuon(true);
    // table->cGianHangCot(0, 2);
    table->cKieuChu(font28, 26);
    table->cGioHanBD(table->lViTri().y, GetScreenHeight()); // đặt giới hạn vì không thể vẽ hết tất các các ô, nếu vẽ hêt tức những ô ra ngoài vùng cửa sổ vũng vẽ => dư thừa và hiệu suất kém

    // Thiết lập tiêu đề cho bảng và thanh tiêu đề  cột
    const string tieuDe[18] = {"STT", "Phòng", "Điện", "Nước", "Tổng nộp", "Đã nộp", "", "", "CSDT", "CSCT", "Lượng.TT", "T.Tiền", "CSDT", "CSCT", "Lượng.TT", "T.Tiền"};
    const int chieuDaiO[18] = {60, 120, 490, 490, 200, 100, 60, 120, 110, 110, 120, 150, 110, 110, 120, 150, 200, 100};
    for (int i = 0; i < 6; i++)
    {
        thanhDienNuoc->cCot(i, chieuDaiO[i]);
        (*thanhDienNuoc)(0, i).cNoiDung(tieuDe[i]);
    }
    for (int i = 6; i < 18; i++)
    {
        table->cCot(i - 6, chieuDaiO[i]);
        (*table)(0, i - 6).cNoiDung(tieuDe[i]);
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
    // capNhatThuTu(); "this edit"
    // hộp xóa
    boxReset = hopChu({1260, 134, 210, 40}, "         Thiết lập lại", RED, YELLOW);
    boxReset.cKieuChu(font28);

    boxSetGiaTien = hopChu({1030, 134, 210, 40}, "Giá điện nước", BLUE, YELLOW);
    boxSetGiaTien.cKieuChu(font28);

    boxTimKiem = hopChu({70, 134, 400, 40}, "          Tìm kiếm", {173, 216, 230, 255}, YELLOW, BLACK);
    boxTimKiem.cKieuChu(font28);

    boxResetHet = hopChu({(GetScreenWidth() - 560) / 2.0f, (GetScreenHeight() - 60) / 2.0f - 40, 560, 60}, "         Thiết lập lại tất cả");
    boxResetHet.cKieuChu(font28);

    boxResetCoLay = hopChu({(GetScreenWidth() - 560) / 2.0f, (GetScreenHeight() - 60) / 2.0f + 70, 560, 60}, "        Giữ cột CSCT và chuyển sang CSDT");
    boxResetCoLay.cKieuChu(font28);

    nutTat = hop({0, 0, 60, 30}, RED);

    BangSetGiaTienDien = nullptr;

    boxXuatFile = hopChu({800, 134, 210, 40}, " Xuất file", BLUE, YELLOW);
    boxXuatFile.cKieuChu(font28);
}