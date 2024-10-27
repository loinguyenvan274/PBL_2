#include "giaoDienChinh.h"

giaoDienChinh ::giaoDienChinh(QuanLy<SinhVien> *qLSinhVienDV)
{

    qLSV = qLSinhVienDV;

    soSinhVien = qLSV->lSoPhanTu();
    sohangBD = soSinhVien;

    // table ;

    int soDongToiDA = 1000;
    viTriLuu = new int[soDongToiDA]; // dùng để tìm kiếm
    flagTimKiem = false;
    chuoiTimSoSanh = "";
    
    table = new Bang({10, 200}, 8, soDongToiDA, {250, 36});
    table->cTieuDe(true);
    table->cFlagCuon(true);
    table->cGianHangCot(3, 0);
    table->cKieuChu(font28, 26);
    table->cGioHanBD(table->lViTri().y, GetScreenHeight());

    const string tieuDe[] = {"STT", "Họ và tên", "Ngày sinh", "MSV", "Ngày ở", "Số Tháng", "Mã phòng", "Xóa"};
    const int doDai[] = {60, 280, 250, 200, 210, 160, 240, 60};
    // Đặt nội dung  và chiều dài cho các cột
    for (int i = 0; i < 8; ++i)
    {
        (*table)(0, i).cNoiDung(tieuDe[i]);
        table->cCot(i, doDai[i]);
    }
    capNhatThuTu();
    // hộp xóa
    boxThem = new hopChu({1030, 134, 210, 40}, "   Thêm sinh viên", BLUE, YELLOW, BLACK);
    (*boxThem).cKieuChu(font28);
    boxXoa = new hopChu({1260, 134, 210, 40}, "         Xóa tất cả", RED, YELLOW, BLACK);
    (*boxXoa).cKieuChu(font28);
    boxTimKiem = new hopChu({70, 134, 400, 40}, "          Tìm kiếm", {173, 216, 230, 255}, YELLOW, BLACK);
    (*boxTimKiem).cKieuChu(font28);
}
void giaoDienChinh::capNhatTT()
{
    // check
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        cout << GetMouseY() << "  ---  " << GetMouseX() << endl;

    table->capNhatTT();
    table->vungHoatDong(1, 1, sohangBD, 7);
    Vector2 dCLay = table->oHoatDong();
    int c = dCLay.y, h = dCLay.x, vT = h - 1;
    if (h != -1)
    {
        if (flagTimKiem)
            vT = viTriLuu[h - 1];
        switch (c)
        {
        case 1:
            (*qLSV)[vT].cHoVaTen((*table)(h, c).layChu());
            break;
        case 2:
            (*qLSV)[vT].cNgaySinh((*table)(h, c).layChu());
            break;
        case 3:
            (*qLSV)[vT].cMa((*table)(h, c).layChu());
            break;
        case 4:
            (*qLSV)[vT].cNgayBatDauO((*table)(h, c).layChu());
            break;
        case 5:
            (*qLSV)[vT].cThoiGianO((*table)(h, c).layChu());
            break;
        case 6:
            (*qLSV)[vT].cMaPhong((*table)(h, c).layChu());
            break;
        case 7:
            soSinhVien--;
            soDoiTuongTim--;
            (*qLSV).xoa(vT);
            (*table)(h, c).cTrangThaiChon(false);
            capNhatThuTu();
            break;
        default:
            break;
        }
    }
    boxThem->capNhatTT();
    boxXoa->capNhatTT();
    boxTimKiem->capNhatTT();

    if (boxThem->laDuocChon())
    {
        qLSV->chen(qLSV->lDCDau(), SinhVien());
        soSinhVien++;
        soDoiTuongTim++;
        boxThem->cTrangThaiChon(false);
        capNhatThuTu();
    }
    if (boxXoa->laDuocChon())
    {
        qLSV->xoa(qLSV->lDCDau(), qLSV->lDCCuoi());
        soSinhVien = 0;
        soDoiTuongTim = 0;
        boxXoa->cTrangThaiChon(false);
        capNhatThuTu();
    }
    if (boxTimKiem->laDuocChon() && !flagTimKiem)
    {
        boxTimKiem->cNoiDung("");
        flagTimKiem = true;
    }
    if (!boxTimKiem->laDuocChon() && boxTimKiem->layChu() == "")
    {
        boxTimKiem->cNoiDung("          Tìm kiếm");
        flagTimKiem = false;
    }
    // tìm kiếm
    if (boxTimKiem->laDuocChon() && chuoiTimSoSanh != boxTimKiem->layChu())
    {
        soDoiTuongTim = 0;
        chuoiTimSoSanh = boxTimKiem->layChu();

        for (int i = 0; i < soSinhVien; i++)
        {
            if ((*qLSV)[i].lHoVaTen().find(boxTimKiem->layChu()) != string::npos || (*qLSV)[i].lMaPhong().find(boxTimKiem->layChu()) != string::npos || (*qLSV)[i].lMa().find(boxTimKiem->layChu()) != string::npos || boxTimKiem->layChu() == "")
            {
                viTriLuu[soDoiTuongTim++] = i;
            }
        }
        capNhatThuTu();
    }
}
void giaoDienChinh::bieuDien()
{

    table->bieuDien(0, 0, sohangBD, 7);
    boxTimKiem->bieuDien();
    boxThem->bieuDien();
    boxXoa->bieuDien();
}
giaoDienChinh::~giaoDienChinh()
{
    delete[] viTriLuu;
    delete boxThem;
    delete boxXoa;
    delete boxTimKiem;
    delete table;
}
void giaoDienChinh::capNhatThuTu()
{
    if (flagTimKiem)
        sohangBD = soDoiTuongTim;
    else
        sohangBD = soSinhVien;
    int vT;
    for (int i = 1; i <= sohangBD; i++)
    {
        if (flagTimKiem)
            vT = viTriLuu[i - 1];
        else
            vT = i - 1;
        (*table)(i, 0).cNoiDung(to_string(i));
        (*table)(i, 1).cNoiDung((*qLSV)[vT].lHoVaTen());
        (*table)(i, 2).cNoiDung((*qLSV)[vT].lngaySinh());
        (*table)(i, 3).cNoiDung((*qLSV)[vT].lMa());
        (*table)(i, 4).cNoiDung((*qLSV)[vT].lNgayBatDauO());
        (*table)(i, 5).cNoiDung((*qLSV)[vT].lThoiGianO());
        (*table)(i, 6).cNoiDung((*qLSV)[vT].lMaPhong());
        (*table)(i, 7).cNoiDung("Xóa");
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