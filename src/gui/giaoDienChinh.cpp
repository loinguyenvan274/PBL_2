#include "giaoDienChinh.h"

enum cuaSoChinhSua
{
    HO_VA_TEN,
    CCCD,
    SDT,
    GIOI_TINH,
    NGAY_SINH,
    NGAY_VAO_O,
    MA_PHONG,
    LOAI_PHONG,
    SO_THANG_O,
    TIEN_PHONG,
    TIEN_THE_CHAP,
    XOA,
    THOAT,
    LUU,
    XUAT_HOP_DONG,
    THEM_HINH_ANH,
};
enum cacNutTuyChon
{
    N_TAT_CA,
    N_HET_HAN,
    N_CON_HAN
};

struct hienThiChuGDC
{
    const char **chuCacOCuaSoCon;
    const char **cacNutCongCu;
    const char **noiDungNut;
    const char **tieuDe;
    const char **noiDungRoiRac;
    const char **noiDungOTuyChon;
    const string *noiDungThongBao;
};
namespace GDC
{
    const char *chuCacOCuaSoConNhat[20] = {"氏名:", "CCCD:", "電話番号:", "性別:", "生年月日:", "入居日:", "部屋番号:", "部屋タイプ:", "入居月数:", "家賃:", "保証金:", "削除", "退出", "保存", "契約書の出力", "画像を追加"};
    const char *cacNutCongCuNhat[20] = {"学生を追加", "すべて削除", "検索", "名前"};
    const char *noiDungNutNhat[20] = {"すべて", "期限切れ", "有効"};
    const char *tieuDeNhat[] = {"番号", "氏名", "生年月日", "CCCD", "電話番号", "性別", "部屋番号", "編集"};
    const char *noiDungRoiRacNhat[20] = {"部屋", "人", "編集", "表の行数:", "検索"};
    const char *noiDungOTuyChonNhat[3] = {"名前", "CCCD", "部屋番号"};
    const string noiDungThongBaoNhat[5] = {"有効", "重複コード", "無効なコード", "存在しない部屋", "部屋が満員"};

    const char *chuCacOCuaSoConAnh[20] = {"Full name:", "ID number:", "Phone number:", "Gender:", "Date of birth:", "Move-in date:", "Room number:", "Room type:", "Months of stay:", "Room fee:", "Deposit:", "Delete", "Exit", "Save", "Export contract", "Add image"};
    const char *cacNutCongCuAnh[20] = {"Add student", "Delete all", "Search", "Name"};
    const char *noiDungNutAnh[20] = {"All", "Expired", "Valid"};
    const char *tieuDeAnh[] = {"No.", "Full name", "Date of birth", "ID number", "Phone number", "Gender", "Room number", "Edit"};
    const char *noiDungRoiRacAnh[20] = {"Room", "People", "Edit", "Number of rows on the table:", "Search"};
    const char *noiDungOTuyChonAnh[3] = {"Name", "ID number", "Room number"};
    const string noiDungThongBaoAnh[5] = {"Valid", "Duplicate code", "Invalid code", "Room does not exist", "Room is full"};

    const char *chuCacOCuaSoConViet[20] = {"Họ và tên:", "CCCD:", "SĐT:", "Giới tính:", "Ngày sinh:", "Ngày vào ở:", "Mã Phòng:", "Loại phòng:", "Số tháng ở:", "Tiền phòng:", "Tiền cọc:", "Xóa", "Thoát", "Lưu", "Xuất hợp đồng", "Thêm hình ảnh"};
    const char *cacNutCongCuViet[20] = {"Thêm sinh viên", "Xóa tất cả", "Tìm kiếm", " Tên"};
    const char *noiDungNutViet[20] = {"Tất cả", "Hết hạn", "Còn hạn"};
    const char *tieuDeViet[] = {"STT", "Họ và tên", "Ngày sinh", "CCCD", "Số điện thoại", "Giới tính", "Mã phòng", "Chỉnh Sửa"};
    const char *noiDungRoiRacViet[20] = {"phòng ", "nguời", "  Chỉnh", " Số dòng trên bản: ", "          Tìm kiếm"};
    const char *noiDungOTuyChonViet[3] = {" Tên", " CCCD", " Mã phòng"};
    const string noiDungThongBaoViet[5] = {"Hợp lệ", "Trùng mã", "Mã không hợp lệ", "Phòng Không tồn tại", "Phòng Đầy"};

    const hienThiChuGDC tiengViet{chuCacOCuaSoConViet, cacNutCongCuViet, noiDungNutViet, tieuDeViet, noiDungRoiRacViet, noiDungOTuyChonViet, noiDungThongBaoViet};
    const hienThiChuGDC tiengAnh{chuCacOCuaSoConAnh, cacNutCongCuAnh, noiDungNutAnh, tieuDeAnh, noiDungRoiRacAnh, noiDungOTuyChonAnh, noiDungThongBaoAnh};
    const hienThiChuGDC tiengNhat{chuCacOCuaSoConNhat, cacNutCongCuNhat, noiDungNutNhat, tieuDeNhat, noiDungRoiRacNhat, noiDungOTuyChonNhat, noiDungThongBaoNhat};
}

const hienThiChuGDC *chuGDC;
giaoDienChinh ::giaoDienChinh(QuanLyKTX &quanLyKTX, HeThong &heThong) : giaoDien(quanLyKTX, heThong), flagChinhSinhVien(false)
{
    switch (this->heThong->ngonNgu)
    {
    case 0:
        chuGDC = &GDC::tiengViet;
        break;
    case 1:
        chuGDC = &GDC::tiengAnh;
        break;
    case 2:
        chuGDC = &GDC::tiengNhat;
        break;
    }

    taoNutTuyChon();
    sohangBD = soSinhVien;
    table = nullptr;

    flagTimKiem = false;
    chuoiTimSoSanh = "";

    boxThem = hopChu({1030, 144, 210, 40}, chuGDC->cacNutCongCu[0], BLUE, YELLOW, BLACK, font26);
    boxThem.cDoBoVien(0.3f);

    boxXoa = hopChu({1260, 144, 210, 40}, chuGDC->cacNutCongCu[1], RED, YELLOW, BLACK, font26);
    boxXoa.cDoBoVien(0.3f);

    boxHTSoNguoiOBang = hopChu({10, 70, 540, 40}, "", WHITE, MAU_LA_CAY, BLACK, font26);
    boxHTSoNguoiOBang.cDoBoVien(0.3f);
    boxHTSoNguoiOBang.cRangBuoc(true);

    boxTimKiem = hopChu({146, 144, 400, 40}, chuGDC->cacNutCongCu[2], BLUE, YELLOW, BLACK, font26);
    boxTimKiem.cDoBoVien(0.3f);

    tuyChonTimKiem = hopChu({10, 144, 130, 40}, chuGDC->cacNutCongCu[3], MAU_XANH, YELLOW, BLACK, font26);
    tuyChonTimKiem.cDoBoVien(0.3f);

    boDemMucChon = 0; // khoi tao bang 0

    flagThongBaoKHL = false;

    capNhatBang(quanLyKTX.lDanhSachSinhVien());

    taoCuaSoCon();
}
void giaoDienChinh::taoNutTuyChon()
{
    const int soNut = 3;
    cacNutChon.dSNut = Vector<hopChu>(soNut);
    float chieuDaiO = 130;
    float khoangCachO = 20;
    for (int i = 0; i < cacNutChon.dSNut.lSoPhanTu(); i++)
    {
        cacNutChon.dSNut[i] = hopChu({570 + (chieuDaiO + khoangCachO) * i, 144, chieuDaiO, 40}, chuGDC->noiDungNut[i], BLUE, YELLOW, BLACK, font26);
        cacNutChon.dSNut[i].cDoBoVien(0.3f);
    }
}
void giaoDienChinh::taoCuaSoCon()
{
    const Vector2 kichCoCuaSoCon = Vector2{700.0f, 1300.0f};
    cuaSoChinhSua = cuaSoCon({(GetScreenWidth() - kichCoCuaSoCon.y) / 2.0f,
                              (GetScreenHeight() - kichCoCuaSoCon.x) / 2.0f},
                             kichCoCuaSoCon);
    cuaSoChinhSua.khungCuaSo.cDoBoVien(0.1f);
    cuaSoChinhSua.khungCuaSo.cDoDayVien(3);
    cuaSoChinhSua.khungCuaSo.cMauNen(Color{224, 255, 255, 255});
    cuaSoChinhSua.khungCuaSo.cTrangThaiChon(true);
    cuaSoChinhSua.dSHopHienThi = Vector<hopChu>(13);
    cuaSoChinhSua.dShopChu = Vector<hopChu>(17);
    for (int i = 0; i < cuaSoChinhSua.dShopChu.lSoPhanTu(); i++)
    {
        cuaSoChinhSua.dShopChu[i].cDoBoVien(0.3f);
        cuaSoChinhSua.dShopChu[i].cMauNen(MAU_LA_CAY);
    }

    const float viTriXCuaSo = cuaSoChinhSua.viTri.x;
    const float viTriYCuaSo = cuaSoChinhSua.viTri.y;
    const float khoangCachO = 40;
    Color mauNenChuHienThi = Color{224, 255, 255, 255};
    const int doRongOHIenThi = 150;
    cuaSoChinhSua.dSHopHienThi[HO_VA_TEN] = hopChu({400, viTriYCuaSo + khoangCachO, doRongOHIenThi, 40}, chuGDC->chuCacOCuaSoCon[HO_VA_TEN], mauNenChuHienThi, YELLOW, BLACK, font26);
    cuaSoChinhSua.dShopChu[HO_VA_TEN] = hopChu({400 + doRongOHIenThi, viTriYCuaSo + khoangCachO, 300, 40}, "", MAU_XANH, YELLOW, BLACK, font26);
    cuaSoChinhSua.dSHopHienThi[CCCD] = hopChu({400, viTriYCuaSo + khoangCachO * 3, doRongOHIenThi, 40}, chuGDC->chuCacOCuaSoCon[CCCD], mauNenChuHienThi, YELLOW, BLACK, font26);
    cuaSoChinhSua.dShopChu[CCCD] = hopChu({400 + doRongOHIenThi, viTriYCuaSo + khoangCachO * 3, 300, 40}, "", MAU_XANH, YELLOW, BLACK, font26);
    cuaSoChinhSua.dSHopHienThi[SDT] = hopChu({400, viTriYCuaSo + khoangCachO * 5, doRongOHIenThi, 40}, chuGDC->chuCacOCuaSoCon[SDT], mauNenChuHienThi, YELLOW, BLACK, font26);
    cuaSoChinhSua.dShopChu[SDT] = hopChu({400 + doRongOHIenThi, viTriYCuaSo + khoangCachO * 5, 300, 40}, "", MAU_XANH, YELLOW, BLACK, font26);
    cuaSoChinhSua.dSHopHienThi[GIOI_TINH] = hopChu({900, viTriYCuaSo + khoangCachO * 3, doRongOHIenThi, 40}, chuGDC->chuCacOCuaSoCon[GIOI_TINH], mauNenChuHienThi, YELLOW, BLACK, font26);
    cuaSoChinhSua.dShopChu[GIOI_TINH] = hopChu({900 + doRongOHIenThi, viTriYCuaSo + khoangCachO * 3, 300, 40}, "", MAU_XANH, YELLOW, BLACK, font26);
    cuaSoChinhSua.dSHopHienThi[NGAY_SINH] = hopChu({900, viTriYCuaSo + khoangCachO, doRongOHIenThi, 40}, chuGDC->chuCacOCuaSoCon[NGAY_SINH], mauNenChuHienThi, YELLOW, BLACK, font26);
    cuaSoChinhSua.dShopChu[NGAY_SINH] = hopChu({900 + doRongOHIenThi, viTriYCuaSo + khoangCachO, 300, 40}, "", MAU_XANH, YELLOW, BLACK, font26);
    cuaSoChinhSua.dSHopHienThi[MA_PHONG] = hopChu({viTriXCuaSo + 100, viTriYCuaSo + khoangCachO * 10, doRongOHIenThi, 40}, chuGDC->chuCacOCuaSoCon[MA_PHONG], mauNenChuHienThi, YELLOW, BLACK, font26);
    cuaSoChinhSua.dShopChu[MA_PHONG] = hopChu({viTriXCuaSo + 100 + doRongOHIenThi, viTriYCuaSo + khoangCachO * 10, 300, 40}, "", MAU_XANH, YELLOW, BLACK, font26);
    cuaSoChinhSua.dSHopHienThi[LOAI_PHONG] = hopChu({viTriXCuaSo + 100, viTriYCuaSo + khoangCachO * 8, doRongOHIenThi, 40}, chuGDC->chuCacOCuaSoCon[LOAI_PHONG], mauNenChuHienThi, YELLOW, BLACK, font26);
    cuaSoChinhSua.dShopChu[LOAI_PHONG] = hopChu({viTriXCuaSo + 100 + doRongOHIenThi, viTriYCuaSo + khoangCachO * 8, 300, 40}, "", MAU_XANH, YELLOW, BLACK, font26);
    cuaSoChinhSua.dSHopHienThi[SO_THANG_O] = hopChu({viTriXCuaSo + 100, viTriYCuaSo + khoangCachO * 12, doRongOHIenThi, 40}, chuGDC->chuCacOCuaSoCon[SO_THANG_O], mauNenChuHienThi, YELLOW, BLACK, font26);
    cuaSoChinhSua.dShopChu[SO_THANG_O] = hopChu({viTriXCuaSo + 100 + doRongOHIenThi, viTriYCuaSo + khoangCachO * 12, 300, 40}, "", MAU_XANH, YELLOW, BLACK, font26);
    cuaSoChinhSua.dSHopHienThi[TIEN_PHONG] = hopChu({800, viTriYCuaSo + khoangCachO * 8, doRongOHIenThi, 40}, chuGDC->chuCacOCuaSoCon[TIEN_PHONG], mauNenChuHienThi, YELLOW, BLACK, font26);
    cuaSoChinhSua.dShopChu[TIEN_PHONG] = hopChu({800 + doRongOHIenThi, viTriYCuaSo + khoangCachO * 8, 300, 40}, "", MAU_XANH, YELLOW, BLACK, font26);
    cuaSoChinhSua.dSHopHienThi[NGAY_VAO_O] = hopChu({800, viTriYCuaSo + khoangCachO * 10, doRongOHIenThi, 40}, chuGDC->chuCacOCuaSoCon[NGAY_VAO_O], mauNenChuHienThi, YELLOW, BLACK, font26);
    cuaSoChinhSua.dShopChu[NGAY_VAO_O] = hopChu({800 + doRongOHIenThi, viTriYCuaSo + khoangCachO * 10, 300, 40}, "", MAU_XANH, YELLOW, BLACK, font26);
    cuaSoChinhSua.dSHopHienThi[TIEN_THE_CHAP] = hopChu({800, viTriYCuaSo + khoangCachO * 12, doRongOHIenThi, 40}, chuGDC->chuCacOCuaSoCon[TIEN_THE_CHAP], mauNenChuHienThi, YELLOW, BLACK, font26);
    cuaSoChinhSua.dShopChu[TIEN_THE_CHAP] = hopChu({800 + doRongOHIenThi, viTriYCuaSo + khoangCachO * 12, 300, 40}, "", MAU_XANH, YELLOW, BLACK, font26);
    // Các nút chức năng đặt ở cuối
    cuaSoChinhSua.dShopChu[XOA] = hopChu({900, 700, 130, 40}, chuGDC->chuCacOCuaSoCon[XOA], MAU_XANH, BLACK, BLACK, font26);
    cuaSoChinhSua.dShopChu[LUU] = hopChu({1050, 700, 130, 40}, chuGDC->chuCacOCuaSoCon[LUU], MAU_XANH, BLACK, BLACK, font26);
    cuaSoChinhSua.dShopChu[THOAT] = hopChu({1200, 700, 130, 40}, chuGDC->chuCacOCuaSoCon[THOAT], MAU_XANH, BLACK, BLACK, font26);
    cuaSoChinhSua.dShopChu[XUAT_HOP_DONG] = hopChu({viTriXCuaSo + 70, 700, 190, 40}, chuGDC->chuCacOCuaSoCon[XUAT_HOP_DONG], MAU_XANH, YELLOW, BLACK, font26);

    cuaSoChinhSua.dShopChu[THEM_HINH_ANH] = hopChu(Rectangle{viTriXCuaSo + 70, viTriYCuaSo + 40, 142, 182}, chuGDC->chuCacOCuaSoCon[THEM_HINH_ANH], MAU_XANH, YELLOW, BLACK, font26);
    for (int i = 0; i < cuaSoChinhSua.dShopChu.lSoPhanTu(); i++)
    {
        cuaSoChinhSua.dShopChu[i].cDoBoVien(0.2f);
        cuaSoChinhSua.dShopChu[i].cMauNen(MAU_LA_CAY);
    }
    cuaSoChinhSua.dShopChu[XOA].cMauNen(RED);
    cuaSoChinhSua.dShopChu[LUU].cMauNen(BLUE);
    cuaSoChinhSua.dShopChu[THOAT].cMauNen(YELLOW);
}
void giaoDienChinh::cNLoaiPhongVaGiaPhong()
{
    string loaiPhong = "", giaPhong = "";
    int soThang = 0;
    try
    {
        soThang = stoi(cuaSoChinhSua.dShopChu[SO_THANG_O].layChu());
    }
    catch (std::invalid_argument &e)
    {
        cout << "loi chuyen => int\n";
    }
    catch (std::out_of_range &e)
    {
        cout << "so qua lon => trang so \n";
    }
    const Phong *phongTim = quanLyKTX.timPhong(cuaSoChinhSua.dShopChu[MA_PHONG].layChu());
    if (phongTim != nullptr)
    {
        loaiPhong = chuGDC->noiDungRoiRac[0] + to_string(phongTim->lSoNguoiToiDa()) + " " + chuGDC->noiDungRoiRac[1];
        if (phongTim->lSoNguoiToiDa() != 0)
            giaPhong = to_string(phongTim->lGiaPhong() * soThang / phongTim->lSoNguoiToiDa());
        else
            giaPhong = "";
    }
    cuaSoChinhSua.dShopChu[TIEN_PHONG].cNoiDung(giaPhong);
    cuaSoChinhSua.dShopChu[LOAI_PHONG].cNoiDung(loaiPhong);

    // cuaSoChinhSua.dShopChu[LOAI_PHONG].cNoiDung();
}
void giaoDienChinh::capNhatCuaSoCon(const SinhVien &sinhVien)
{
    cuaSoChinhSua.dShopChu[HO_VA_TEN].cNoiDung(sinhVien.lHoVaTen());
    cuaSoChinhSua.dShopChu[CCCD].cNoiDung(sinhVien.lMa());
    cuaSoChinhSua.dShopChu[SDT].cNoiDung(sinhVien.lSDT());
    cuaSoChinhSua.dShopChu[GIOI_TINH].cNoiDung(sinhVien.lGioiTinh());
    cuaSoChinhSua.dShopChu[NGAY_SINH].cNoiDung(sinhVien.lngaySinh());
    cuaSoChinhSua.dShopChu[MA_PHONG].cNoiDung(sinhVien.lHopDong().maPhong);
    cuaSoChinhSua.dShopChu[SO_THANG_O].cNoiDung(to_string(sinhVien.lHopDong().soThangO));
    cuaSoChinhSua.dShopChu[NGAY_VAO_O].cNoiDung(sinhVien.lHopDong().ngaySinhVienVao.chuyenSangString());
    cuaSoChinhSua.dShopChu[TIEN_THE_CHAP].cNoiDung(to_string(sinhVien.lHopDong().tienTheChap));
    cNLoaiPhongVaGiaPhong();
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
    for (int i = 1; i < soDongBieuDien; i++)
    {
        table->cMauTheoHang(i, {32, 178, 170, 255});
    }
    table->cMauTheoHang(0, {46, 139, 87, 255});
    const int doDai[] = {60, 280, 250, 200, 210, 160, 180, 120};
    // Đặt nội dung  và chiều dài cho các cột
    for (int i = 0; i < 8; ++i)
    {
        (*table)(0, i).cNoiDung(chuGDC->tieuDe[i]);
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
    (*table)(viTri, 7).cNoiDung(chuGDC->noiDungRoiRac[2]);
}
void giaoDienChinh::capNhatBang(const Vector<SinhVien> &danhSachSinhVien)
{
    static unsigned soDongBang = 0;
    unsigned demHangThoaMang = 0;
    sohangBD = danhSachSinhVien.lSoPhanTu() + boxThem.laDuocChon();

    NTN ngayHienTai;
    NTN ngayHetHan;
    if (soDongBang < sohangBD + 1 || table == nullptr) // cong 1 la them cai tieu de;
    {
        soDongBang = (sohangBD + 1) * 2; // gấp đôi lê hễ thêm 1 đối tượng thôi mà phải tạo lại thì không tốt cho lắm
        taoBang(soDongBang);
    }
    if (boxThem.laDuocChon())
        capNhatDong(1, SinhVien());

    int viTriDanhSach;
    for (int i = 1 + boxThem.laDuocChon(); i <= sohangBD; i++)
    {
        viTriDanhSach = i - 1 - boxThem.laDuocChon();
        ngayHetHan = danhSachSinhVien[viTriDanhSach].lHopDong().ngaySinhVienVao;
        ngayHetHan += danhSachSinhVien[viTriDanhSach].lHopDong().soThangO;

        if (cacNutChon.dSNut[N_HET_HAN].laRangBuoc())
        {
            if (!(ngayHetHan < ngayHienTai))
                continue;
        }
        else if (cacNutChon.dSNut[N_CON_HAN].laRangBuoc())
        {
            if (ngayHetHan < ngayHienTai)
            {
                continue;
            }
        }
        capNhatDong(demHangThoaMang++ + 1 + boxThem.laDuocChon(), danhSachSinhVien[viTriDanhSach]);
    }
    sohangBD = demHangThoaMang;
    boxHTSoNguoiOBang.cNoiDung(chuGDC->noiDungRoiRac[3] + to_string(sohangBD) + "/" + to_string(quanLyKTX.lDanhSachSinhVien().lSoPhanTu()));
}
SinhVien giaoDienChinh::LaySinhVienOBang() const
{
    SinhVien sinhvien(cuaSoChinhSua.dShopChu[HO_VA_TEN].layChu(), cuaSoChinhSua.dShopChu[CCCD].layChu(), cuaSoChinhSua.dShopChu[NGAY_SINH].layChu());
    sinhvien.cSDT(cuaSoChinhSua.dShopChu[SDT].layChu());
    sinhvien.cGioiTinh(cuaSoChinhSua.dShopChu[GIOI_TINH].layChu());
    HopDongSinhVien hopDong;
    hopDong.maPhong = cuaSoChinhSua.dShopChu[MA_PHONG].layChu();
    hopDong.ngaySinhVienVao = cuaSoChinhSua.dShopChu[NGAY_VAO_O].lNTN();
    try
    {
        hopDong.soThangO = stoi(cuaSoChinhSua.dShopChu[SO_THANG_O].layChu());
    }
    catch (const invalid_argument &)
    {
        hopDong.soThangO = 0;
    }
    catch (const out_of_range &)
    {
        hopDong.soThangO = 0;
    }
    try
    {
        hopDong.tienTheChap = stoul(cuaSoChinhSua.dShopChu[TIEN_THE_CHAP].layChu());
    }
    catch (const invalid_argument &)
    {
        hopDong.tienTheChap = 0;
    }
    catch (const out_of_range &)
    {
        hopDong.tienTheChap = 0;
    }

    sinhvien.cHopDong(hopDong);
    return sinhvien;
}
void giaoDienChinh::capNhatDanhSachSV()
{
    Vector2 dCLay = table->oHoatDong();
    int cot = dCLay.y, hang = dCLay.x;

    static bool flagDoiSinhVien = false;

    static Vector2 viTriCu = {-2, -2}; // cho số âm , và tại sao không -1 -1 đi thì -1 -1 là giá trị ô không hoạt đông bên kia trả về
    if (hang != -1)
    {
        const SinhVien *sinhVienCS = quanLyKTX.timSinhVien((*table)(hang, 3).layChu());
        if (sinhVienCS != nullptr)
        {
            capNhatCuaSoCon(*sinhVienCS);
            flagChinhSinhVien = true;
            sinhVienCu = LaySinhVienOBang();
        }
        else
        {
            cout << (*table)(hang, 3).layChu() << endl;
            cout
                << "ERROR ------------------->\n";
        }
        (*table)(hang, cot).cTrangThaiChon(false);
    }
}
void giaoDienChinh::capNhatTTChinh()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        cout << GetMouseY() << "  ---  " << GetMouseX() << endl;

    table->capNhatTT();
    table->vungHoatDong(1, 7, sohangBD, 7);
    capNhatDanhSachSV(); // cap nhat qua sanh sach;
    boxThem.capNhatTT();
    boxXoa.capNhatTT();
    tuyChonTimKiem.capNhatTT();
    cacNutChon.capNhatTT();
    static int nutChonHienTai;

    if (nutChonHienTai != cacNutChon.nutBiRangBuot)
    {
        cout << "here";
        nutChonHienTai = cacNutChon.nutBiRangBuot;
        capNhatBang(dsSinhVienTimKiem());
    }
    if (tuyChonTimKiem.laDuocChon())
    {
        boDemMucChon++;
        tuyChonTimKiem.cTrangThaiChon(false);
        tuyChonTimKiem.cNoiDung(chuGDC->noiDungOTuyChon[boDemMucChon % 3]);
    }

    boxTimKiem.capNhatTT();

    if (boxThem.laDuocChon())
    {
        sinhVienCu = SinhVien();
        capNhatCuaSoCon(sinhVienCu);
        flagChinhSinhVien = true;
        boxThem.cTrangThaiChon(false);
    }
    if (boxXoa.laDuocChon())
    {
        for (int i = 1; i <= sohangBD; i++)
        {
            quanLyKTX.xoaSinhVien((*table)(i, 3).layChu());
        }
        capNhatBang(dsSinhVienTimKiem());
        boxXoa.cTrangThaiChon(false);
    }
    if (boxTimKiem.laDuocChon() && !flagTimKiem)
    {
        boxTimKiem.cNoiDung("");
        flagTimKiem = true;
    }
    if (!boxTimKiem.laDuocChon() && boxTimKiem.layChu() == "")
    {
        boxTimKiem.cNoiDung(chuGDC->noiDungRoiRac[4]);
        flagTimKiem = false;
    }
    // tìm kiếm
    if (boxTimKiem.laDuocChon() && chuoiTimSoSanh != boxTimKiem.layChu())
    {
        capNhatBang(dsSinhVienTimKiem());
    }
}
Vector<SinhVien> giaoDienChinh::dsSinhVienTimKiem()
{
    bool (*hamSoSanh[3])(const SinhVien &, const string &) = {QuanLyKTX::soSanhTenSV, QuanLyKTX::soSanhMaSV, QuanLyKTX::soSanhMaPhongSV};
    if (flagTimKiem)
        chuoiTimSoSanh = boxTimKiem.layChu();
    return quanLyKTX.timSinhVienGiong(chuoiTimSoSanh, hamSoSanh[boDemMucChon % 3]);
}
void giaoDienChinh::capNhatTT()
{
    // check
    if (flagChinhSinhVien)
    {
        // cap nhat trang thai cua so
        cuaSoChinhSua.capNhatTT();
        if (cuaSoChinhSua.dShopChu[SO_THANG_O].laDuocChon() || cuaSoChinhSua.dShopChu[MA_PHONG].laDuocChon())
        {
            cNLoaiPhongVaGiaPhong();
        }
        else if (cuaSoChinhSua.dShopChu[THOAT].laDuocChon())
        {
            flagChinhSinhVien = false;
            cuaSoChinhSua.dShopChu[THOAT].cTrangThaiChon(false);
        }
        else if (cuaSoChinhSua.dShopChu[LUU].laDuocChon())
        {
            SinhVien sinhVien = LaySinhVienOBang();
            trangThaiSV = quanLyKTX.doiSinhVien(sinhVienCu, sinhVien);
            if (trangThaiSV == HOP_LE)
                flagChinhSinhVien = false;
            flagThongBaoKHL = true;
            cuaSoChinhSua.dShopChu[LUU].cTrangThaiChon(false);
            capNhatBang(dsSinhVienTimKiem());
        }
        else if (cuaSoChinhSua.dShopChu[XOA].laDuocChon() && sinhVienCu.lMa() != "")
        {
            quanLyKTX.xoaSinhVien(sinhVienCu.lMa());
            cuaSoChinhSua.dShopChu[XOA].cTrangThaiChon(false);
            flagChinhSinhVien = false;
            capNhatBang(dsSinhVienTimKiem());
        }
    }
    else
    {
        capNhatTTChinh();
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
    cacNutChon.bieuDien();

    if (flagChinhSinhVien)
        cuaSoChinhSua.bieuDien();

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
void giaoDienChinh::cuaSoThongBaoKHL()
{
    Color mauVien = RED;
    if (trangThaiSV == HOP_LE)
        mauVien = GREEN;
    hop nenSauCuaSo(Rectangle{1031, 57, 439, 70}, mauVien);
    nenSauCuaSo.cDoBoVien(0.3f);
    hopChu chuThongBao(Rectangle{1036, 62, 429, 60}, "            " + chuGDC->noiDungThongBao[trangThaiSV], WHITE);
    chuThongBao.cKieuChu(font26);
    chuThongBao.cDoBoVien(0.3f);

    nenSauCuaSo.bieuDien();
    chuThongBao.bieuDien();
}

giaoDienChinh::~giaoDienChinh()
{
    delete table;
}