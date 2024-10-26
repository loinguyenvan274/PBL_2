#include "gDDienNuoc.h"

gDDienNuoc ::gDDienNuoc(QuanLy<Phong> *qLPhongDV)
{

    qLPhong = qLPhongDV;

    soPhong = qLPhong->lSoPhanTu();
    sohangBD = soPhong;

    // table

    int soDongToiDA = 1000;
    viTriLuu = new int[soDongToiDA]; // dùng để tìm kiếm
    flagTimKiem = false;
    chuoiTimSoSanh = "";

    table = new Bang({10, 200}, 12, soDongToiDA + 1, {250, 36});
    table->cTieuDe(true);
    table->cFlagCuon(true);
    table->cGianHangCot(3, 0);
    table->cKieuChu(font28, 26);
    table->cGioHanBD(table->lViTri().y, GetScreenHeight());

    // Thiết lập tiêu đề cho 13 cột
    (*table)(0, 0).cNoiDung("STT");
    (*table)(0, 1).cNoiDung("Phòng");
    (*table)(0, 2).cNoiDung("CSDT");
    (*table)(0, 3).cNoiDung("CSCT");
    (*table)(0, 4).cNoiDung("Lương TT");
    (*table)(0, 5).cNoiDung("T.Tiền");
    (*table)(0, 6).cNoiDung("CSDT");
    (*table)(0, 7).cNoiDung("CSCT");
    (*table)(0, 8).cNoiDung("Lượng TT");
    (*table)(0, 9).cNoiDung("T.Tiền");
    (*table)(0, 10).cNoiDung("Tổng Nộp");
    (*table)(0, 11).cNoiDung("Đã Nộp");

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
void gDDienNuoc::capNhatTT()
{

    //     // // check
    //     // if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    //     //     cout << GetMouseY() << "  ---  " << GetMouseX() << endl;

    table->capNhatTT();
    // table->vungHoatDong(1, 1, sohangBD, 2);
    // table->vungHoatDong(1, 4, sohangBD, 5);
    //     Vector2 dCLay = table->oHoatDong();
    //     int c = dCLay.y, h = dCLay.x, vT = h - 1;
    //     if (h != -1)
    //     {
    //         string chuoiMoi = (*table)(h, c).layChu();

    //         cout
    //             << h << " ---- " << c;
    //         if (flagTimKiem)
    //             vT = viTriLuu[h - 1];
    //         switch (c)
    //         {
    //         case 1:
    //             (*qLPhong)[vT].cMaPhong(chuoiMoi);
    //             break;
    //         case 2:
    //             if (chuoiMoi == "")
    //                 chuoiMoi += '0';
    //             (*qLPhong)[vT].cSoNguoiToiDa(stoi(chuoiMoi));
    //             break;
    //         case 3:
    //             (*qLPhong)[vT].cSoNguoiHienTai(stoi(chuoiMoi));
    //             break;
    //         case 4:
    //             (*qLPhong)[vT].cMoTa(chuoiMoi);
    //             break;
    //         case 5:
    //             soPhong--;
    //             soDoiTuongTim--;
    //             (*qLPhong).xoa(vT);
    //             (*table)(h, c).cTranThaiChon(false);
    //             capNhatThuTu();
    //             break;
    //         default:
    //             break;
    //         }
    //     }
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
    boxTimKiem->bieuDien();
    boxXoaHet->bieuDien();
}
// // void giaoDienPhong::luuDuLieu() const
// // {
// //     docGhiFile docGhi("data/sinhVien.csv");
// //     QuanLy<QuanLy<string>> dSSVBK((*danhSachQLSV).lSoPhanTu());
// //     for (int i = 0; i < (*danhSachQLSV).lSoPhanTu(); i++)
// //     {
// //         dSSVBK[i] = (*danhSachQLSV)[i].lThongTin();
// //     }

// //     docGhi.ghiData(dSSVBK);
// // }
gDDienNuoc::~gDDienNuoc()
{
    delete[] viTriLuu;
    delete boxXoaHet;
    delete boxTimKiem;
    delete table;
}
void gDDienNuoc::capNhatThuTu()
{
    int vT;
    if (flagTimKiem)
        sohangBD = soDoiTuongTim;
    else
        sohangBD = soPhong;
    for (int i = 1; i <= sohangBD; i++)
    {
        if (flagTimKiem)
            vT = viTriLuu[i - 1];
        else
            vT = i - 1;
        (*table)(i, 0).cNoiDung(to_string(i));
        (*table)(i, 1).cNoiDung((*qLPhong)[vT].lMaPhong());
        (*table)(i, 2).cNoiDung(float_string((*qLPhong)[vT].lDienCSDT()));
        (*table)(i, 3).cNoiDung(float_string((*qLPhong)[vT].lDienCSCT()));
        (*table)(i, 6).cNoiDung(float_string((*qLPhong)[vT].lNuocCSDT()));
        (*table)(i, 7).cNoiDung(float_string((*qLPhong)[vT].lNuocCSCT()));
    }
    table->cMauTheoHang(0, {65, 105, 225, 255});
    for (int i = 1; i <= sohangBD; i++)
    {
        if (i % 2 == 0)
            table->cMauTheoHang(i, {135, 206, 235, 255});
        else
            table->cMauTheoHang(i, {173, 216, 230, 255});
    }
}