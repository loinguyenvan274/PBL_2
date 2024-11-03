#include "giaoDienChinh.h"

giaoDienChinh ::giaoDienChinh(QuanLyKTX &quanLyKTX) : giaoDien(quanLyKTX)
{
    sohangBD = soSinhVien;

    // table ;
    int soDongToiDa = 10000;
    flagTimKiem = false;
    chuoiTimSoSanh = "";

    table = new Bang({10, 200}, 8, soDongToiDa, {250, 42});
    table->cTieuDe(true);
    table->cFlagCuon(true);
    table->cGianHangCot(3, 0);
    table->cKieuChu(font28, 26);
    table->cGioHanBD(table->lViTri().y, GetScreenHeight());
    table->cMauTheoHang(0, {46, 139, 87, 255});
    for (int i = 1; i < soDongToiDa; i++)
    {
        table->cMauTheoHang(i, {32, 178, 170, 255});
    }

    const string tieuDe[] = {"STT", "Họ và tên", "Ngày sinh", "Mã sinh viên", "Số điện thoại", "Giới tính", "Mã phòng", "Xóa"};
    const int doDai[] = {60, 280, 250, 200, 210, 160, 240, 60};
    // Đặt nội dung  và chiều dài cho các cột
    for (int i = 0; i < 8; ++i)
    {
        (*table)(0, i).cNoiDung(tieuDe[i]);
        table->cCot(i, doDai[i]);
    }
    capNhatBang(quanLyKTX.lDanhSachSinhVien());
    // hộp xóa
    boxThem = hopChu({1030, 134, 210, 40}, "   Thêm sinh viên", BLUE, YELLOW, BLACK);
    boxThem.cKieuChu(font28);
    boxThem.cDoBoVien(0.3f);
    boxXoa = hopChu({1260, 134, 210, 40}, "         Xóa tất cả", RED, YELLOW, BLACK);
    boxXoa.cKieuChu(font28);
    boxXoa.cDoBoVien(0.3f);
    boxTimKiem = hopChu({70, 134, 400, 40}, "          Tìm kiếm", BLUE, YELLOW, BLACK);
    boxTimKiem.cKieuChu(font28);
    boxTimKiem.cDoBoVien(0.3f);
}
void giaoDienChinh::capNhatDong(const int &viTri, const SinhVien &sinhVien)
{
    (*table)(viTri, 0).cNoiDung(to_string(viTri));
    (*table)(viTri, 1).cNoiDung(sinhVien.lHoVaTen());
    (*table)(viTri, 2).cNoiDung(sinhVien.lngaySinh());
    (*table)(viTri, 3).cNoiDung(sinhVien.lMa());
    (*table)(viTri, 4).cNoiDung(sinhVien.lSDT());
    (*table)(viTri, 5).cNoiDung(sinhVien.lGioiTinh());
    (*table)(viTri, 6).cNoiDung(sinhVien.lMaPhong());
    (*table)(viTri, 7).cNoiDung("Xóa");
}
void giaoDienChinh::capNhatBang(const Vector<SinhVien> &danhSachSinhVien)
{
    sohangBD = danhSachSinhVien.lSoPhanTu() + boxThem.laDuocChon();
    if (boxThem.laDuocChon())
        capNhatDong(1, SinhVien());
    for (int i = 1 + boxThem.laDuocChon(); i <= sohangBD; i++)
    {
        capNhatDong(i, danhSachSinhVien[i - 1 - boxThem.laDuocChon()]);
    }
}
SinhVien giaoDienChinh::LaySinhVienOBang(const int &viTri) const
{
    SinhVien sinhvien((*table)(viTri, 1).layChu(), (*table)(viTri, 3).layChu(), (*table)(viTri, 2).layChu());
    sinhvien.cNgayBatDauO((*table)(viTri, 4).layChu());
    sinhvien.cThoiGianO((*table)(viTri, 5).layChu());
    sinhvien.cMaPhong((*table)(viTri, 6).layChu());
    return sinhvien;
}
void giaoDienChinh::capNhatDanhSachSV()
{
    Vector2 dCLay = table->oHoatDong();
    int cot = dCLay.y, hang = dCLay.x;
    static SinhVien sinhVienCu;
    static SinhVien sinhVien;

    static bool flagDoiSinhVien = false;

    static Vector2 viTriCu = {-2, -2}; // cho số âm , và tại sao không -1 -1 đi thì -1 -1 là giá trị ô không hoạt đông bên kia trả về
    if ((viTriCu.x != dCLay.x) && flagDoiSinhVien == true)
    {
        cout << "here" << endl;
        if (sinhVienCu.lMa() == "")
        {
            if (!quanLyKTX.themSinhVien(sinhVien))
                cout << "sinh Vien khong hop le" << endl; // "edit"
        }
        else if (!quanLyKTX.doiSinhVien(sinhVienCu, sinhVien))
        {
            cout << "sinh Vien khong hop le" << endl;
            capNhatDong(viTriCu.x, sinhVienCu);
        }
        flagDoiSinhVien = false;
    }
    if (hang != -1)
    {
        sinhVien = LaySinhVienOBang(hang);
        if ((1 <= cot && cot <= 6) && flagDoiSinhVien == false)
        {
            sinhVienCu = LaySinhVienOBang(hang);
            flagDoiSinhVien = true;
            viTriCu = dCLay;
        }
        if (cot == 7)
        {
            cout << sinhVien.lMa() << endl;

            quanLyKTX.xoaSinhVien(sinhVien.lMa());
            capNhatBang(quanLyKTX.lDanhSachSinhVien());
            (*table)(hang, cot).cTrangThaiChon(false);
        }
    }
}

void giaoDienChinh::capNhatTT()
{
    // check
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        cout << GetMouseY() << "  ---  " << GetMouseX() << endl;

    table->capNhatTT();
    table->vungHoatDong(1, 1, sohangBD, 7);
    capNhatDanhSachSV(); // cap nhat qua sanh sach;
    boxThem.capNhatTT();
    boxXoa.capNhatTT();
    boxTimKiem.capNhatTT();

    if (boxThem.laDuocChon())
    {
        capNhatBang(quanLyKTX.lDanhSachSinhVien());
        boxThem.cTrangThaiChon(false);
    }
    if (boxXoa.laDuocChon())
    {
        quanLyKTX.xoaTatCaSinhVien();
        capNhatBang(quanLyKTX.lDanhSachSinhVien());
        boxXoa.cTrangThaiChon(false);
    }
    if (boxTimKiem.laDuocChon() && !flagTimKiem)
    {
        boxTimKiem.cNoiDung("");
        flagTimKiem = true;
    }
    if (!boxTimKiem.laDuocChon() && boxTimKiem.layChu() == "")
    {
        boxTimKiem.cNoiDung("          Tìm kiếm");
        flagTimKiem = false;
    }
    // tìm kiếm
    if (boxTimKiem.laDuocChon() && chuoiTimSoSanh != boxTimKiem.layChu())
    {
        chuoiTimSoSanh = boxTimKiem.layChu();
        capNhatBang(quanLyKTX.timSinhVienGiong(chuoiTimSoSanh));
    }
}
void giaoDienChinh::bieuDien()
{

    table->bieuDien(0, 0, sohangBD, 7);
    boxTimKiem.bieuDien();
    boxThem.bieuDien();
    boxXoa.bieuDien();
}
giaoDienChinh::~giaoDienChinh()
{
    delete table;
}