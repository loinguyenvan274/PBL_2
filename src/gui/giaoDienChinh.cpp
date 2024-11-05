#include "giaoDienChinh.h"

giaoDienChinh ::giaoDienChinh(QuanLyKTX &quanLyKTX) : giaoDien(quanLyKTX)
{
    sohangBD = soSinhVien;
    table = nullptr;

    flagTimKiem = false;
    chuoiTimSoSanh = "";
    // table ;
    // hộp xóa
    boxThem = hopChu({1030, 144, 210, 40}, "   Thêm sinh viên", BLUE, YELLOW, BLACK);
    boxThem.cKieuChu(font26);
    boxThem.cDoBoVien(0.3f);
    boxXoa = hopChu({1260, 144, 210, 40}, "         Xóa tất cả", RED, YELLOW, BLACK);
    boxXoa.cKieuChu(font26);
    boxXoa.cDoBoVien(0.3f);

    boxHTSoNguoiOBang = hopChu({10, 70, 540, 40}, "", WHITE, MAU_LA_CAY, BLACK);
    boxHTSoNguoiOBang.cKieuChu(font26);
    boxHTSoNguoiOBang.cDoBoVien(0.3f);
    boxHTSoNguoiOBang.cTrangThaiChon(true);

    boxTimKiem = hopChu({146, 144, 400, 40}, "          Tìm kiếm", BLUE, YELLOW, BLACK);
    boxTimKiem.cKieuChu(font26);
    boxTimKiem.cDoBoVien(0.3f);

    tuyChonTimKiem = hopChu({10, 144, 130, 40}, " Tên", MAU_XANH, YELLOW, BLACK);
    tuyChonTimKiem.cKieuChu(font26);
    tuyChonTimKiem.cDoBoVien(0.3f);

    boDemMucChon = 0; // khoi tao bang 0

    flagThongBaoKHL = false;

    capNhatBang(quanLyKTX.lDanhSachSinhVien());
}
void giaoDienChinh::taoBang(const unsigned int &soDongBieuDien)
{
    if (table != nullptr)
    {
        delete table;
    }
    table = new Bang({10, 200}, 8, soDongBieuDien, {250, 42});
    table->cTieuDe(true);
    table->cFlagCuon(true);
    table->cGianHangCot(3, 0);
    table->cKieuChu(font26, 26);
    table->cGioHanBD(table->lViTri().y, GetScreenHeight());
    table->cMauTheoHang(0, {46, 139, 87, 255});
    for (int i = 1; i < soDongBieuDien; i++)
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
    static unsigned soDongBang = 0;
    sohangBD = danhSachSinhVien.lSoPhanTu() + boxThem.laDuocChon();
    boxHTSoNguoiOBang.cNoiDung("  Số sinh viên trên bảng: " + to_string(sohangBD) + "/" + to_string(quanLyKTX.lDanhSachSinhVien().lSoPhanTu() + boxThem.laDuocChon()));
    if (soDongBang < sohangBD + 1 || table == nullptr) // cong 1 la them cai tieu de;
    {
        soDongBang = (sohangBD + 1) * 2; // gấp đôi lê hễ thêm 1 đối tượng thôi mà phải tạo lại thì không tốt cho lắm
        taoBang(soDongBang);
    }

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
        if (sinhVienCu.lMa() == "")
        {
            trangThaiSV = quanLyKTX.themSinhVien(sinhVien);
            if (trangThaiSV != HOP_LE)
            {
                cout << "sinh Vien khong hop le" << endl; // "edit"
                capNhatBang(quanLyKTX.lDanhSachSinhVien());
            }
        }
        else
        {
            trangThaiSV = quanLyKTX.doiSinhVien(sinhVienCu, sinhVien);
            if (trangThaiSV != HOP_LE)
            {
                cout << "sinh Vien khong hop le" << endl;
                capNhatDong(viTriCu.x, sinhVienCu);
            }
        }
        flagThongBaoKHL = true;
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
    tuyChonTimKiem.capNhatTT();
    if (tuyChonTimKiem.laDuocChon())
    {
        boDemMucChon++;
        tuyChonTimKiem.cTrangThaiChon(false);
        const char *const noiDungOTuyChon[3] = {" Tên", " MSV", " Mã phòng"};
        tuyChonTimKiem.cNoiDung(noiDungOTuyChon[boDemMucChon % 3]);
    }

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
        bool (*hamSoSanh[3])(const SinhVien &, const string &) = {QuanLyKTX::soSanhTenSV, QuanLyKTX::soSanhMaSV, QuanLyKTX::soSanhMaPhongSV};
        chuoiTimSoSanh = boxTimKiem.layChu();
        capNhatBang(quanLyKTX.timSinhVienGiong(chuoiTimSoSanh, hamSoSanh[boDemMucChon % 3]));
    }
}
void giaoDienChinh::bieuDien()
{

    table->bieuDien(0, 0, sohangBD, 7);
    boxTimKiem.bieuDien();
    tuyChonTimKiem.bieuDien();
    boxThem.bieuDien();
    boxXoa.bieuDien();
    boxHTSoNguoiOBang.bieuDien();

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
/*
57  ---  1031
127  ---  1470
*/
void giaoDienChinh::cuaSoThongBaoKHL()
{
    const string noiDungThongBao[5] = {"Hợp lệ", "Trùng mã", "Mã không hợp lệ", "Phòng Không tồn tại", "Phòng Đầy"};
    Color mauVien = RED;
    if (trangThaiSV == HOP_LE)
        mauVien = GREEN;
    hop nenSauCuaSo(Rectangle{1031, 57, 439, 70}, mauVien);
    nenSauCuaSo.cDoBoVien(0.3f);
    hopChu chuThongBao(Rectangle{1036, 62, 429, 60}, "            " + noiDungThongBao[trangThaiSV], WHITE);
    chuThongBao.cKieuChu(font26);
    chuThongBao.cDoBoVien(0.3f);

    nenSauCuaSo.bieuDien();
    chuThongBao.bieuDien();
}

giaoDienChinh::~giaoDienChinh()
{
    delete table;
}