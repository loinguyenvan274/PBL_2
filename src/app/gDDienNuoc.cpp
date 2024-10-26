#include "gDDienNuoc.h"

gDDienNuoc ::gDDienNuoc(QuanLy<Phong> *qLPhongDV, QuanLy<QuanLy<string>> &heThong)
{
    qLPhong = qLPhongDV;
    this->heThong = &heThong;

    const int soMucDien = 6, hMucBacDien = 0, hGiaDien = 1, hGiaNuoc = 2;
    for (int i = 0; i < soMucDien; i++)
    {
        mucBacDien[i] = stoi(heThong[hMucBacDien][i]);
        giaTienDien[i] = stod(heThong[hGiaDien][i]);
    }
    giaTienNuoc = stod(heThong[hGiaNuoc][0]); // hang 2 : hàng giá nước tức là chỉ hàng đó chỉ có một cái giá trị lưu giá tien nước;

    soPhong = qLPhong->lSoPhanTu();
    sohangBD = soPhong;
    veKhoiTao();
}
void gDDienNuoc::capNhatTT()
{
    table->capNhatTT();
    table->vungHoatDong(1, 2, sohangBD, 3);
    table->vungHoatDong(1, 6, sohangBD, 7);
    table->vungHoatDong(1, 11, sohangBD, 11);
    Vector2 dCLay = table->oHoatDong();
    int c = dCLay.y, h = dCLay.x, vT = h - 1;
    if (h != -1)
    {
        string chuoiMoi = (*table)(h, c).layChu();
        if (chuoiMoi == "")
            chuoiMoi += '0';
        cout
            << h << " ---- " << c;
        if (flagTimKiem)
            vT = viTriLuu[h - 1];
        switch (c)
        {
        case 2:
            (*qLPhong)[vT].cDienCSDT(stof(chuoiMoi));
            break;
        case 3:
            (*qLPhong)[vT].cDienCSCT(stof(chuoiMoi));
            break;
        case 6:
            (*qLPhong)[vT].cNuocCSDT(stof(chuoiMoi));
            break;
        case 7:
            (*qLPhong)[vT].cNuocCSCT(stof(chuoiMoi));
            break;
        case 11:
            if ((*qLPhong)[vT].daNopTienDN())
            {
                (*qLPhong)[vT].cNopTienDN(false);
                (*table)(h, c).cNoiDung("Chưa");
            }
            else
            {
                (*qLPhong)[vT].cNopTienDN(true);
                (*table)(h, c).cNoiDung("Rồi");
            }
            (*table)(h, c).cTranThaiChon(false);
            break;
        default:
            break;
        }
    }
    //     boxThem->capNhatTT();
    //     boxXoaHet->capNhatTT();
    //     boxTimKiem->capNhatTT();

    //     if (boxThem->laDuocChon())
    //     {
    //         qLPhong->chen(qLPhong->lDCDau(), Phong());
    //         soPhong++;
    //         soDoiTuongTim++;
    //         boxThem->cTranThaiChon(false);
    //         capNhatThuTu();
    //     }
    //     if (boxXoaHet->laDuocChon())
    //     {
    //         qLPhong->xoa(qLPhong->lDCDau(), qLPhong->lDCCuoi());
    //         soPhong = 0;
    //         soDoiTuongTim = 0;
    //         boxXoaHet->cTranThaiChon(false);
    //         capNhatThuTu();
    //     }
    //     if (boxTimKiem->laDuocChon() && !flagTimKiem)
    //     {
    //         boxTimKiem->cNoiDung("");
    //         flagTimKiem = true;
    //     }
    //     if (!boxTimKiem->laDuocChon() && boxTimKiem->layChu() == "")
    //     {
    //         boxTimKiem->cNoiDung("          Tìm kiếm");
    //         flagTimKiem = false;
    //     }
    //     // tìm kiếm
    //     if (boxTimKiem->laDuocChon() && chuoiTimSoSanh != boxTimKiem->layChu())
    //     {
    //         soDoiTuongTim = 0;
    //         chuoiTimSoSanh = boxTimKiem->layChu();

    //         for (int i = 0; i < soPhong; i++)
    //         {
    //             if ((*qLPhong)[i].lMaPhong().find(boxTimKiem->layChu()) != string::npos || (*qLPhong)[i].lMoTa().find(boxTimKiem->layChu()) != string::npos || boxTimKiem->layChu() == "")
    //             {
    //                 viTriLuu[soDoiTuongTim++] = i;
    //             }
    //         }
    //         capNhatThuTu();
    //     }
}
void gDDienNuoc::bieuDien()
{
    table->bieuDien(0, 0, sohangBD, 11);
    thanhDienNuoc->bieuDien(0, 0, 0, 5);
    boxTimKiem->bieuDien();
    boxXoaHet->bieuDien();
}
gDDienNuoc::~gDDienNuoc()
{
    delete[] viTriLuu;
    delete thanhDienNuoc;
    delete boxXoaHet;
    delete boxTimKiem;
    delete table;
}
void gDDienNuoc::capNhatTinhToan(const int &vTriBang, const int &vTriDanhSach)
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
void gDDienNuoc::capNhatThuTu()
{
    int vTriDanhSach;
    if (flagTimKiem)
        sohangBD = soDoiTuongTim;
    else
        sohangBD = soPhong;

    for (int vTriBang = 1; vTriBang <= sohangBD; vTriBang++)
    {
        if (flagTimKiem)
            vTriDanhSach = viTriLuu[vTriBang - 1];
        else
            vTriDanhSach = vTriBang - 1;

        (*table)(vTriBang, 0).cNoiDung(to_string(vTriBang));
        (*table)(vTriBang, 1).cNoiDung((*qLPhong)[vTriDanhSach].lMaPhong());
        (*table)(vTriBang, 2).cNoiDung(float_string((*qLPhong)[vTriDanhSach].lDienCSDT()));
        (*table)(vTriBang, 3).cNoiDung(float_string((*qLPhong)[vTriDanhSach].lDienCSCT()));
        (*table)(vTriBang, 6).cNoiDung(float_string((*qLPhong)[vTriDanhSach].lNuocCSDT()));
        (*table)(vTriBang, 7).cNoiDung(float_string((*qLPhong)[vTriDanhSach].lNuocCSCT()));
        capNhatTinhToan(vTriBang, vTriDanhSach);
        if ((*qLPhong)[vTriDanhSach].daNopTienDN())
            (*table)(vTriBang, 11).cNoiDung("Rồi");
        else
            (*table)(vTriBang, 11).cNoiDung("Chưa");
    }
}
void gDDienNuoc::veKhoiTao()
{
    // tạo thanh điện nước
    thanhDienNuoc = new Bang({10, 200}, 6, 1, {250, 36});
    thanhDienNuoc->cKieuChu(font28, 26);
    thanhDienNuoc->cMauTheoHang(0, MAU_XANH);
    thanhDienNuoc->cCot(0, 60);  // stt
    thanhDienNuoc->cCot(1, 120); // phong
    thanhDienNuoc->cCot(2, 490);
    thanhDienNuoc->cCot(3, 490);
    thanhDienNuoc->cCot(4, 200);
    thanhDienNuoc->cCot(5, 100);

    (*thanhDienNuoc)(0, 0).cNoiDung("STT");
    (*thanhDienNuoc)(0, 1).cNoiDung("Phòng");
    (*thanhDienNuoc)(0, 2).cNoiDung("Điện");
    (*thanhDienNuoc)(0, 3).cNoiDung("Nước");
    (*thanhDienNuoc)(0, 4).cNoiDung("Tổng nộp");
    (*thanhDienNuoc)(0, 5).cNoiDung("Đã nộp");

    int soDongToiDA = 10000;
    viTriLuu = new int[soDongToiDA]; // dùng để tìm kiếm
    flagTimKiem = false;
    chuoiTimSoSanh = "";
    //{vị trí}, số cột, số dòng + tiêu đề, {kích cở mặt định của các ô} / 12 cot
    table = new Bang({10, 236}, 12, soDongToiDA + 1, {250, 36});
    table->cTieuDe(true);
    table->cFlagCuon(true);
    table->cGianHangCot(3, 0);
    table->cKieuChu(font28, 26);
    table->cGioHanBD(table->lViTri().y, GetScreenHeight()); // đặt giới hạn vì không thể vẽ hết tất các các ô, nếu vẽ hêt tức những ô ra ngoài vùng cửa sổ vũng vẽ => dư thừa và hiệu suất kém

    // Thiết lập tiêu đề cho 13 cột
    (*table)(0, 2).cNoiDung("CSDT");
    (*table)(0, 3).cNoiDung("CSCT");
    (*table)(0, 4).cNoiDung("Lương TT");
    (*table)(0, 5).cNoiDung("T.Tiền");
    (*table)(0, 6).cNoiDung("CSDT");
    (*table)(0, 7).cNoiDung("CSCT");
    (*table)(0, 8).cNoiDung("Lượng TT");
    (*table)(0, 9).cNoiDung("T.Tiền");

    // Thiết lập chiều rộng cho 13 cột
    table->cCot(0, 60);   // STT
    table->cCot(1, 120);  // Phòng
    table->cCot(2, 110);  // CSDT
    table->cCot(3, 110);  // CSCT
    table->cCot(4, 120);  // Lương TT
    table->cCot(5, 150);  // T.Tiền
    table->cCot(6, 110);  // CSDT
    table->cCot(7, 110);  // CSCT
    table->cCot(8, 120);  // Lượng TT
    table->cCot(9, 150);  // T.Tiền
    table->cCot(10, 200); // Tổng Nộp
    table->cCot(11, 100); // Đã Nộp

    // thiết lập ô chỉ nhập số
    for (int i = 0; i < soDongToiDA; i++)
    {
        (*table)(i, 2).cChiNhapSo(true);
        (*table)(i, 3).cChiNhapSo(true);
        (*table)(i, 6).cChiNhapSo(true);
        (*table)(i, 7).cChiNhapSo(true);
    }
    capNhatThuTu();
    // hộp xóa
    boxXoaHet = new hopChu({1260, 134, 210, 40}, "         Xóa tất cả", RED, YELLOW, BLACK);
    (*boxXoaHet).cKieuChu(font28);
    (*boxXoaHet).cCoChu(26);
    (*boxXoaHet).cDoDayVien(3);

    boxTimKiem = new hopChu({70, 134, 400, 40}, "          Tìm kiếm", {173, 216, 230, 255}, YELLOW, BLACK);
    (*boxTimKiem).cKieuChu(font28);
    (*boxTimKiem).cCoChu(26);
    (*boxTimKiem).cDoDayVien(3);
}