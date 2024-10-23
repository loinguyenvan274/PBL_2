#include "giaoDienChinh.h"

giaoDienChinh ::giaoDienChinh(quanLyGiaoDien &qLGiaoDienDV)
{

    docGhiFile docGhi("data/sinhVien.csv");
    QuanLy<QuanLy<string>> dSDoc = docGhi.docData();
    danhSachQLSV = new QuanLy<SinhVien>(dSDoc.lSoPhanTu());
    for (int i = 0; i < dSDoc.lSoPhanTu(); i++)
    {
        (*danhSachQLSV)[i].cThongTin(dSDoc[i]);
    }

    qLGiaoDien = &qLGiaoDienDV;
    soSinhVien = danhSachQLSV->lSoPhanTu();
    sohangBD = soSinhVien;

    font28 = LoadFontEx("assets/roboto.ttf", 26, const_cast<int *>(vietnameseCodepoints), sizeof(vietnameseCodepoints) / sizeof(int));

    // table ;

    int soDongToiDA = 1000;
    viTriLuu = new int[soDongToiDA]; // dùng để tìm kiếm
    flagTimKiem = false;

    table = new Bang({10, 200}, 8, soDongToiDA, {250, 36});
    table->cTieuDe(true);
    table->cDangHangCot(3, 0);
    table->cKieuChu(font28, 26);
    table->cGioHanBD(table->lViTri().y, GetScreenHeight());

    (*table)(0, 0).cNoiDung("STT");
    (*table)(0, 1).cNoiDung("Họ và tên");
    (*table)(0, 2).cNoiDung("Ngày sinh");
    (*table)(0, 3).cNoiDung("MSV");
    (*table)(0, 4).cNoiDung("Ngày ở");
    (*table)(0, 5).cNoiDung("Số Tháng");
    (*table)(0, 6).cNoiDung("Mã phòng");
    (*table)(0, 7).cNoiDung("Xóa");

    table->cCot(0, 60);
    table->cCot(1, 280);
    table->cCot(2, 250);
    table->cCot(3, 200);
    table->cCot(4, 210);
    table->cCot(5, 160);
    table->cCot(6, 240);
    table->cCot(7, 60);
    capNhatThuTu();
    // hộp xóa
    boxThemSinhVien = new hopChu({1030, 134, 210, 40}, "   Thêm Sinh Viên", BLUE, YELLOW, BLACK);
    (*boxThemSinhVien).cKieuChu(font28);
    (*boxThemSinhVien).cCoChu(26);
    (*boxThemSinhVien).cDoDayVien(3);
    boxXoaHet = new hopChu({1260, 134, 210, 40}, "         Xóa tất cả", RED, YELLOW, BLACK);
    (*boxXoaHet).cKieuChu(font28);
    (*boxXoaHet).cCoChu(26);
    (*boxXoaHet).cDoDayVien(3);
    boxTimKiem = new hopChu({70, 134, 400, 40}, "          Tìm Kiếm", WHITE, YELLOW, BLACK);
    (*boxTimKiem).cKieuChu(font28);
    (*boxTimKiem).cCoChu(26);
    (*boxTimKiem).cDoDayVien(3);
}
void giaoDienChinh::capNhatTT()
{

    // check
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        cout << GetMouseY() << "  ---  " << GetMouseX() << endl;

    table->vungHoatDong(1, 1, sohangBD + 1, 8);
    table->capNhatTT();
    Vector2 dCLay = table->oHoatDong();
    int c = dCLay.y, h = dCLay.x, vT = h - 1;
    if (h != -1)
    {
        if (flagTimKiem)
            vT = viTriLuu[h - 1];
        switch (c)
        {
        case 1:
            cout << h << "---" << c << endl;
            (*danhSachQLSV)[vT].cHoVaTen((*table)(h, c).layChu());
            break;
        case 2:
            cout << h << "---" << c << endl;
            (*danhSachQLSV)[vT].cNgaySinh((*table)(h, c).layChu());
            break;
        case 3:
            cout << h << "---" << c << endl;
            (*danhSachQLSV)[vT].cMa((*table)(h, c).layChu());
            break;
        case 4:
            cout << h << "---" << c << endl;
            (*danhSachQLSV)[vT].cNgayBatDauO((*table)(h, c).layChu());
            break;
        case 5:
            cout << h << "---" << c << endl;
            (*danhSachQLSV)[vT].cThoiGianO((*table)(h, c).layChu());
            break;
        case 6:
            cout << h << "---" << c << endl;
            (*danhSachQLSV)[vT].cMaPhong((*table)(h, c).layChu());
            break;
        case 7:
            cout << h << "---" << c << endl;
            soSinhVien--;
            soDoiTuongTim--;
            cout << "here";
            (*danhSachQLSV).xoa(vT);
            (*table)(h, c).laDuocChon() = false;
            capNhatThuTu();
            cout << "here";
            break;
        default:
            break;
        }
    }
    boxThemSinhVien->capNhatTT();
    boxXoaHet->capNhatTT();
    boxTimKiem->capNhatTT();

    if (boxThemSinhVien->laDuocChon())
    {
        danhSachQLSV->chen(danhSachQLSV->lDCDau(), SinhVien());
        soSinhVien++;
        soDoiTuongTim++;
        boxThemSinhVien->laDuocChon() = false;
        capNhatThuTu();
    }
    if (boxXoaHet->laDuocChon())
    {
        danhSachQLSV->xoa(danhSachQLSV->lDCDau(), danhSachQLSV->lDCCuoi());
        soSinhVien = 0;
        soDoiTuongTim = 0;
        boxXoaHet->laDuocChon() = false;
        capNhatThuTu();
    }
    if (boxTimKiem->laDuocChon() && !flagTimKiem)
    {
        boxTimKiem->cNoiDung("");
        flagTimKiem = true;
    }
    if (!boxTimKiem->laDuocChon() && boxTimKiem->layChu() == "")
    {
        boxTimKiem->cNoiDung("          Tìm Kiếm");
        flagTimKiem = false;
    }
    if (boxTimKiem->laDuocChon())
    {
        soDoiTuongTim = 0;
        for (int i = 0; i < soSinhVien; i++)
        {
            if ((*danhSachQLSV)[i].lHoVaTen().find(boxTimKiem->layChu()) != string::npos || (*danhSachQLSV)[i].lMa().find(boxTimKiem->layChu()) != string::npos || boxTimKiem->layChu() == "")
            {
                viTriLuu[soDoiTuongTim++] = i;
            }
        }
        capNhatThuTu();
    }
}
void giaoDienChinh::bieuDien()
{

    table->bieuDien(0, 0, sohangBD + 1, 8);
    boxTimKiem->bieuDien();
    boxThemSinhVien->bieuDien();
    boxXoaHet->bieuDien();
}
giaoDienChinh::~giaoDienChinh()
{

    docGhiFile docGhi("data/sinhVien.csv");
    QuanLy<QuanLy<string>> dSSVBK((*danhSachQLSV).lSoPhanTu());
    for (int i = 0; i < (*danhSachQLSV).lSoPhanTu(); i++)
    {
        dSSVBK[i] = (*danhSachQLSV)[i].lThongTin();
    }

    docGhi.ghiData(dSSVBK);

    delete[] viTriLuu;
    delete boxThemSinhVien;
    delete boxXoaHet;
    delete boxTimKiem;
    delete danhSachQLSV;
    UnloadFont(font28);

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
        (*table)(i, 1).cNoiDung((*danhSachQLSV)[vT].lHoVaTen());
        (*table)(i, 2).cNoiDung((*danhSachQLSV)[vT].lngaySinh());
        (*table)(i, 3).cNoiDung((*danhSachQLSV)[vT].lMa());
        (*table)(i, 4).cNoiDung((*danhSachQLSV)[vT].lNgayBatDauO());
        (*table)(i, 5).cNoiDung((*danhSachQLSV)[vT].lThoiGianO());
        (*table)(i, 6).cNoiDung((*danhSachQLSV)[vT].lMaPhong());
        (*table)(i, 7).cNoiDung("Xóa");
    }
    for (int i = 0; i <= sohangBD; i++)
    {
        if (i % 2 == 0)
            table->cMauTheoHang(i, {184, 184, 255, 255});
        else
            table->cMauTheoHang(i, {255, 238, 221, 255});
    }
}