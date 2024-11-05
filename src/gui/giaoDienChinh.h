#ifndef _GIAODIENCHINH
#define _GIEODIENCHINH

#include "raylib.h"
#include "giaoDien.h"

class giaoDienChinh : public giaoDien
{
private:
    hopChu tuyChonTimKiem;
    hopChu boxHTSoNguoiOBang;
    unsigned int boDemMucChon; // cứ mỗi lần ấn vvaof tùy chọn tìm kiếm thì bộ đếm tăng lên 1 và ta chỉ cần % 3 là đuọc
    TrangThaiSV trangThaiSV;

    bool flagThongBaoKHL;
    void capNhatBang(const Vector<SinhVien> &);
    void capNhatDong(const int &, const SinhVien &);
    SinhVien LaySinhVienOBang(const int &) const; // lấy sinh vien tai dòng thư i
    void capNhatDanhSachSV();
    void cuaSoThongBaoKHL();
    void taoBang(const unsigned int &);

public:
    giaoDienChinh(QuanLyKTX &);
    void capNhatTT() override;
    void bieuDien() override;
    ~giaoDienChinh();
};

#endif