#include "giaoDienPhong.h"

giaoDienPhong ::giaoDienPhong(quanLyGiaoDien &qLGiaoDienDV)
{
    
    
    qLGiaoDien = &qLGiaoDienDV;
    // soSinhVien = danhSachQLSV->lSoPhanTu();
    // sohangBD = soSinhVien;

    // table ;

    int soDongToiDA = 1000;
    sohangBD = soDongToiDA;

    // viTriLuu = new int[soDongToiDA]; // dùng để tìm kiếm
    // flagTimKiem = false;
    // chuoiTimSoSanh = "";

    table = new Bang({10, 200}, 6, soDongToiDA + 1, {250, 36});
    table->cTieuDe(true);
    table->cFlagCuon(true);
    table->cDangHangCot(3, 0);
    table->cKieuChu(font28, 26);
    table->cGioHanBD(table->lViTri().y, GetScreenHeight());

    (*table)(0, 0).cNoiDung("STT");
    (*table)(0, 1).cNoiDung("Phòng");
    (*table)(0, 2).cNoiDung("Tối đa");
    (*table)(0, 3).cNoiDung("Hiện tại");
    (*table)(0, 4).cNoiDung("Mô tả");
    (*table)(0, 5).cNoiDung("Xóa");

    table->cCot(0, 60);
    table->cCot(1, 240);
    table->cCot(2, 200);
    table->cCot(3, 200);
    table->cCot(4, 700);
    table->cCot(5, 60);
    capNhatThuTu();
    // hộp xóa
    boxThemSinhVien = new hopChu({1030, 134, 210, 40}, "      Thêm phòng", BLUE, YELLOW, BLACK);
    (*boxThemSinhVien).cKieuChu(font28);
    (*boxThemSinhVien).cCoChu(26);
    (*boxThemSinhVien).cDoDayVien(3);

    boxXoaHet = new hopChu({1260, 134, 210, 40}, "         Xóa tất cả", RED, YELLOW, BLACK);
    (*boxXoaHet).cKieuChu(font28);
    (*boxXoaHet).cCoChu(26);
    (*boxXoaHet).cDoDayVien(3);

    boxTimKiem = new hopChu({70, 134, 400, 40}, "          Tìm kiếm", {173, 216, 230, 255}, YELLOW, BLACK);
    (*boxTimKiem).cKieuChu(font28);
    (*boxTimKiem).cCoChu(26);
    (*boxTimKiem).cDoDayVien(3);
}
void giaoDienPhong::capNhatTT()
{

    // // check
    // if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    //     cout << GetMouseY() << "  ---  " << GetMouseX() << endl;

    table->capNhatTT();
    table->vungHoatDong(1, 1, sohangBD + 1, 6);
    // Vector2 dCLay = table->oHoatDong();
    // int c = dCLay.y, h = dCLay.x, vT = h - 1;
    // if (h != -1)
    // {
    //     if (flagTimKiem)
    //         vT = viTriLuu[h - 1];
    //     switch (c)
    //     {
    //     case 1:
    //         (*danhSachQLSV)[vT].cHoVaTen((*table)(h, c).layChu());
    //         break;
    //     case 2:
    //         (*danhSachQLSV)[vT].cNgaySinh((*table)(h, c).layChu());
    //         break;
    //     case 3:
    //         (*danhSachQLSV)[vT].cMa((*table)(h, c).layChu());
    //         break;
    //     case 4:
    //         (*danhSachQLSV)[vT].cNgayBatDauO((*table)(h, c).layChu());
    //         break;
    //     case 5:
    //         (*danhSachQLSV)[vT].cThoiGianO((*table)(h, c).layChu());
    //         break;
    //     case 6:
    //         (*danhSachQLSV)[vT].cMaPhong((*table)(h, c).layChu());
    //         break;
    //     case 7:
    //         soSinhVien--;
    //         soDoiTuongTim--;
    //         (*danhSachQLSV).xoa(vT);
    //         (*table)(h, c).cTranThaiChon(false);
    //         capNhatThuTu();
    //         break;
    //     default:
    //         break;
    //     }
    // }
    // boxThemSinhVien->capNhatTT();
    // boxXoaHet->capNhatTT();
    // boxTimKiem->capNhatTT();

    // if (boxThemSinhVien->laDuocChon())
    // {
    //     danhSachQLSV->chen(danhSachQLSV->lDCDau(), SinhVien());
    //     soSinhVien++;
    //     soDoiTuongTim++;
    //     boxThemSinhVien->cTranThaiChon(false);
    //     capNhatThuTu();
    // }
    // if (boxXoaHet->laDuocChon())
    // {
    //     danhSachQLSV->xoa(danhSachQLSV->lDCDau(), danhSachQLSV->lDCCuoi());
    //     soSinhVien = 0;
    //     soDoiTuongTim = 0;
    //     boxXoaHet->cTranThaiChon(false);
    //     capNhatThuTu();
    // }
    // if (boxTimKiem->laDuocChon() && !flagTimKiem)
    // {
    //     boxTimKiem->cNoiDung("");
    //     flagTimKiem = true;
    // }
    // if (!boxTimKiem->laDuocChon() && boxTimKiem->layChu() == "")
    // {
    //     boxTimKiem->cNoiDung("          Tìm kiếm");
    //     flagTimKiem = false;
    // }
    // // tìm kiếm
    // if (boxTimKiem->laDuocChon() && chuoiTimSoSanh != boxTimKiem->layChu())
    // {
    //     soDoiTuongTim = 0;
    //     chuoiTimSoSanh = boxTimKiem->layChu();
    
    //     for (int i = 0; i < soSinhVien; i++)
    //     {
    //         if ((*danhSachQLSV)[i].lHoVaTen().find(boxTimKiem->layChu()) != string::npos || (*danhSachQLSV)[i].lMaPhong().find(boxTimKiem->layChu()) != string::npos || (*danhSachQLSV)[i].lMa().find(boxTimKiem->layChu()) != string::npos || boxTimKiem->layChu() == "")
    //         {
    //             viTriLuu[soDoiTuongTim++] = i;
    //         }
    //     }
    //     capNhatThuTu();
    // }
}
void giaoDienPhong::bieuDien()
{
    table->bieuDien(0, 0, sohangBD + 1, 6);
    boxTimKiem->bieuDien();
    boxThemSinhVien->bieuDien();
    boxXoaHet->bieuDien();
}
// void giaoDienPhong::luuDuLieu() const
// {
//     docGhiFile docGhi("data/sinhVien.csv");
//     QuanLy<QuanLy<string>> dSSVBK((*danhSachQLSV).lSoPhanTu());
//     for (int i = 0; i < (*danhSachQLSV).lSoPhanTu(); i++)
//     {
//         dSSVBK[i] = (*danhSachQLSV)[i].lThongTin();
//     }

//     docGhi.ghiData(dSSVBK);
// }
giaoDienPhong::~giaoDienPhong()
{
    // luuDuLieu();

    // delete[] viTriLuu;
    // delete boxThemSinhVien;
    // delete boxXoaHet;
    // delete boxTimKiem;
    // delete danhSachQLSV;
    // delete table;
}
void giaoDienPhong::capNhatThuTu()
{
    // if (flagTimKiem)
    //     sohangBD = soDoiTuongTim;
    // else
    //     sohangBD = soSinhVien;
    // int vT;
    for (int i = 1; i <= sohangBD; i++)
    {
        // if (flagTimKiem)
        //     vT = viTriLuu[i - 1];
        // else
        //     vT = i - 1;
        (*table)(i, 0).cNoiDung(to_string(i));
        // (*table)(i, 1).cNoiDung((*danhSachQLSV)[vT].lHoVaTen());
        // (*table)(i, 2).cNoiDung((*danhSachQLSV)[vT].lngaySinh());
        // (*table)(i, 3).cNoiDung((*danhSachQLSV)[vT].lMa());
        // (*table)(i, 4).cNoiDung((*danhSachQLSV)[vT].lNgayBatDauO());
        // (*table)(i, 5).cNoiDung((*danhSachQLSV)[vT].lThoiGianO());
        // (*table)(i, 6).cNoiDung((*danhSachQLSV)[vT].lMaPhong());
        (*table)(i, 5).cNoiDung("Xóa");
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