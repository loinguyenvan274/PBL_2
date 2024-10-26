#include "giaoDienPhong.h"

giaoDienPhong ::giaoDienPhong(QuanLy<Phong> *qLPhongDV)
{

    qLPhong = qLPhongDV;

    soPhong = qLPhong->lSoPhanTu();
    sohangBD = soPhong;

    // table

    int soDongToiDA = 1000;
    viTriLuu = new int[soDongToiDA]; // dùng để tìm kiếm
    flagTimKiem = false;
    chuoiTimSoSanh = "";

    table = new Bang({10, 200}, 6, soDongToiDA + 1, {250, 36});
    table->cTieuDe(true);
    table->cFlagCuon(true);
    table->cGianHangCot(3, 0);
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
    for (int i = 0; i < soDongToiDA; i++)
    {
        (*table)(i, 2).cChiNhapSo(true);
    }
    capNhatThuTu();
    // hộp xóa
    boxThem = new hopChu({1030, 134, 210, 40}, "      Thêm phòng", BLUE, YELLOW, BLACK);
    (*boxThem).cKieuChu(font28);
    (*boxThem).cCoChu(26);
    (*boxThem).cDoDayVien(3);

    boxXoa = new hopChu({1260, 134, 210, 40}, "         Xóa tất cả", RED, YELLOW, BLACK);
    (*boxXoa).cKieuChu(font28);
    (*boxXoa).cCoChu(26);
    (*boxXoa).cDoDayVien(3);

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
    table->vungHoatDong(1, 1, sohangBD, 2);
    table->vungHoatDong(1, 4, sohangBD, 5);
    Vector2 dCLay = table->oHoatDong();
    int c = dCLay.y, h = dCLay.x, vT = h - 1;
    if (h != -1)
    {
        string chuoiMoi = (*table)(h, c).layChu();

        cout
            << h << " ---- " << c;
        if (flagTimKiem)
            vT = viTriLuu[h - 1];
        switch (c)
        {
        case 1:
            (*qLPhong)[vT].cMaPhong(chuoiMoi);
            break;
        case 2:
            if (chuoiMoi == "")
                chuoiMoi += '0';
            (*qLPhong)[vT].cSoNguoiToiDa(stoi(chuoiMoi));
            break;
        case 3:
            (*qLPhong)[vT].cSoNguoiHienTai(stoi(chuoiMoi));
            break;
        case 4:
            (*qLPhong)[vT].cMoTa(chuoiMoi);
            break;
        case 5:
            soPhong--;
            soDoiTuongTim--;
            (*qLPhong).xoa(vT);
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
        qLPhong->chen(qLPhong->lDCDau(), Phong());
        soPhong++;
        soDoiTuongTim++;
        boxThem->cTrangThaiChon(false);
        capNhatThuTu();
    }
    if (boxXoa->laDuocChon())
    {
        qLPhong->xoa(qLPhong->lDCDau(), qLPhong->lDCCuoi());
        soPhong = 0;
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

        for (int i = 0; i < soPhong; i++)
        {
            if ((*qLPhong)[i].lMaPhong().find(boxTimKiem->layChu()) != string::npos || (*qLPhong)[i].lMoTa().find(boxTimKiem->layChu()) != string::npos || boxTimKiem->layChu() == "")
            {
                viTriLuu[soDoiTuongTim++] = i;
            }
        }
        capNhatThuTu();
    }
}
void giaoDienPhong::bieuDien()
{
    table->bieuDien(0, 0, sohangBD, 5);
    boxTimKiem->bieuDien();
    boxThem->bieuDien();
    boxXoa->bieuDien();
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
    delete[] viTriLuu;
    delete boxThem;
    delete boxXoa;
    delete boxTimKiem;
    delete table;
}
void giaoDienPhong::capNhatThuTu()
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
        (*table)(i, 2).cNoiDung(to_string((*qLPhong)[vT].lSoNguoiToiDa()));
        (*table)(i, 3).cNoiDung(to_string((*qLPhong)[vT].lSoNguoiHienTai()));
        (*table)(i, 4).cNoiDung((*qLPhong)[vT].lMoTa());
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