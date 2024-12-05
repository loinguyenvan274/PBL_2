#ifndef _GIAODIENCHINH
#define _GIEODIENCHINH

#include "giaoDien.h"
#include "cuaSoCon.h"

class giaoDienChinh : public giaoDien
{
private:
    cuaSoCon cuaSoChinhSua;
    hopChu tuyChonTimKiem;
    hopChu boxHTSoNguoiOBang;
    NutTuyChon cacNutChon;
    unsigned int boDemMucChon; // cứ mỗi lần ấn vvaof tùy chọn tìm kiếm thì bộ đếm tăng lên 1 và ta chỉ cần % 3 là đuọc
    TrangThaiSV trangThaiSV;
    SinhVien sinhVienCu;
    bool flagThongBaoKHL;
    void capNhatBang(const Vector<SinhVien> &);
    void capNhatDong(const int &, const SinhVien &);
    SinhVien LaySinhVienOBang() const; // lấy sinh vien tai bang chinh sua
    void capNhatDanhSachSV();
    void cuaSoThongBaoKHL();
    void taoBang(const unsigned int &);
    void taoCuaSoCon();
    void capNhatCuaSoCon(const SinhVien &);
    bool flagChinhSinhVien;
    void capNhatTTChinh();
    void cNLoaiPhongVaGiaPhong();
    void taoNutTuyChon();
    void xuatPhieuThu();
    Vector<SinhVien> dsSinhVienTimKiem();

public:
    giaoDienChinh(QuanLyKTX &, HeThong &);
    void capNhatTT() override;
    void bieuDien() override;
    ~giaoDienChinh();
};

#endif