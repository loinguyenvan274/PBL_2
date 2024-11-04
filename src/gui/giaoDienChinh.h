#ifndef _GIAODIENCHINH
#define _GIEODIENCHINH

#include "raylib.h"
#include "giaoDien.h"

class giaoDienChinh : public giaoDien
{
private:
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