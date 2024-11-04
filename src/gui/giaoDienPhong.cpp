#include "giaoDienPhong.h"

giaoDienPhong ::giaoDienPhong(QuanLyKTX &quanLyKTX) : giaoDien(quanLyKTX)
{
    sohangBD = quanLyKTX.lDanhSachPhong().lSoPhanTu();
    // table
    flagTimKiem = false;
    chuoiTimSoSanh = "";
    table = nullptr;

    capNhatBang(quanLyKTX.lDanhSachPhong());
    // hộp xóa
    boxThem = hopChu({1030, 134, 210, 40}, "      Thêm phòng", BLUE, YELLOW, BLACK);
    boxThem.cKieuChu(font26);
    boxThem.cDoBoVien(0.3f);

    boxXoa = hopChu({1260, 134, 210, 40}, "         Xóa tất cả", RED, YELLOW, BLACK);
    boxXoa.cKieuChu(font26);
    boxXoa.cDoBoVien(0.3f);

    boxTimKiem = hopChu({70, 134, 400, 40}, "          Tìm kiếm", BLUE, YELLOW, BLACK);
    boxTimKiem.cKieuChu(font26);
    boxTimKiem.cDoBoVien(0.3f);

    flagThongBaoKHL = false;
}
void giaoDienPhong::taoBang(const unsigned int &soDongToiDa)
{
    if (table != nullptr)
        delete table;

    table = new Bang({10, 200}, 6, soDongToiDa + 1, {250, 42});
    table->cTieuDe(true);
    table->cFlagCuon(true);
    table->cGianHangCot(3, 0);
    table->cKieuChu(font26, 26);
    table->cGioHanBD(table->lViTri().y, GetScreenHeight());
    table->cMauTheoHang(0, {46, 139, 87, 255});
    for (int i = 1; i < soDongToiDa; i++)
    {
        table->cMauTheoHang(i, {32, 178, 170, 255});
    }

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
    for (int i = 0; i < soDongToiDa; i++)
    {
        (*table)(i, 2).cChiNhapSo(true);
    }
}
void giaoDienPhong::capNhatBang(const Vector<Phong> &dSPhong)
{
    sohangBD = dSPhong.lSoPhanTu() + boxThem.laDuocChon();

    static unsigned soDongBang = 0;
    if (soDongBang < sohangBD + 1 || table == nullptr) // cong 1 la them cai tieu de;
    {
        soDongBang = (sohangBD + 1) * 2; // gấp đôi lê hễ thêm 1 đối tượng thôi mà phải tạo lại thì không tốt cho lắm
        taoBang(soDongBang);
    }
    
    if (boxThem.laDuocChon())
        capNhatDong(1, Phong());
    for (int i = 1 + boxThem.laDuocChon(); i <= sohangBD; i++)
    {
        capNhatDong(i, dSPhong[i - 1 - boxThem.laDuocChon()]);
    }
}
void giaoDienPhong::capNhatDong(const int &viTri, const Phong &phong)
{
    (*table)(viTri, 0).cNoiDung(to_string(viTri));
    (*table)(viTri, 1).cNoiDung(phong.lMaPhong());
    (*table)(viTri, 2).cNoiDung(to_string(phong.lSoNguoiToiDa()));
    (*table)(viTri, 3).cNoiDung(to_string(phong.lSoNguoiHienTai()));
    (*table)(viTri, 4).cNoiDung(phong.lMoTa());
    (*table)(viTri, 5).cNoiDung("Xóa");
}
Phong giaoDienPhong::lPhongTuBang(const int &viTri) const
{
    string oSo = (*table)(viTri, 2).layChu();
    if (oSo == "")
        oSo += '0';
    Phong phong((*table)(viTri, 1).layChu(), stoi(oSo), (*table)(viTri, 4).layChu());
    return phong;
}
void giaoDienPhong::capNhatDanhSachPhong()
{
    Vector2 dCLay = table->oHoatDong();
    int cot = dCLay.y, hang = dCLay.x;
    static Phong phongCu;
    static Phong phong;

    static bool flagDoiPhong = false;

    static Vector2 viTriCu = {-2, -2}; // cho số âm , và tại sao không -1 -1 đi thì -1 -1 là giá trị ô không hoạt đông bên kia trả về
    if ((viTriCu.x != dCLay.x || viTriCu.y != dCLay.y) && flagDoiPhong == true)
    {
        cout << "here" << endl;
        if (phongCu.lMaPhong() == "")
        {
            if (!quanLyKTX.themPhong(phong))
            {
                cout << "Phong khong hop le" << endl;
                flagThongBaoKHL = true;
            }
        }
        else if (!quanLyKTX.doiPhong(phongCu, phong))
        {
            cout << "sinh Vien khong hop le" << endl;
            capNhatDong(viTriCu.x, phongCu);
            flagThongBaoKHL = true;
        }
        flagDoiPhong = false;
    }
    if (hang != -1)
    {
        phong = lPhongTuBang(hang);
        if (1 <= cot && cot <= 4 && flagDoiPhong == false)
        {
            phongCu = lPhongTuBang(hang);
            flagDoiPhong = true;
            viTriCu = dCLay;
        }
        else if (cot == 5)
        {
            cout << phong.lMaPhong() << endl;

            quanLyKTX.xoaPhong(phong.lMaPhong());
            capNhatBang(quanLyKTX.lDanhSachPhong());
            (*table)(hang, cot).cTrangThaiChon(false);
        }
    }
}
void giaoDienPhong::capNhatTT()
{

    // // check
    // if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    //     cout << GetMouseY() << "  ---  " << GetMouseX() << endl;

    table->capNhatTT();
    table->vungHoatDong(1, 1, sohangBD, 2);
    table->vungHoatDong(1, 4, sohangBD, 5);
    capNhatDanhSachPhong();

    boxThem.capNhatTT();
    boxXoa.capNhatTT();
    boxTimKiem.capNhatTT();

    if (boxThem.laDuocChon())
    {
        capNhatBang(quanLyKTX.lDanhSachPhong());
        boxThem.cTrangThaiChon(false);
    }
    if (boxXoa.laDuocChon())
    {
        quanLyKTX.xoaTatCaPhong();
        capNhatBang(quanLyKTX.lDanhSachPhong());
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

    if (boxTimKiem.laDuocChon() && chuoiTimSoSanh != boxTimKiem.layChu())
    {
        chuoiTimSoSanh = boxTimKiem.layChu();
        capNhatBang(quanLyKTX.timPhongGiong(boxTimKiem.layChu()));
    }
}
void giaoDienPhong::bieuDien()
{
    table->bieuDien(0, 0, sohangBD, 5);
    boxTimKiem.bieuDien();
    boxThem.bieuDien();
    boxXoa.bieuDien();

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
void giaoDienPhong::cuaSoThongBaoKHL()
{
    hop nenSauCuaSo(Rectangle{1031, 57, 439, 70}, RED);
    hopChu chuThongBao(Rectangle{1036, 62, 429, 60}, "              Phòng không hợp lệ", WHITE);
    chuThongBao.cKieuChu(font26);
    nenSauCuaSo.cDoBoVien(0.3f);
    chuThongBao.cDoBoVien(0.3f);

    nenSauCuaSo.bieuDien();
    chuThongBao.bieuDien();
}

giaoDienPhong::~giaoDienPhong()
{
    delete table;
}