#ifndef _GIAODIENCHINH
#define _GIEODIENCHINH

#include "raylib.h"
#include "giaoDien.h"

class giaoDienChinh : public giaoDien
{
private:
    void capNhatBang(const Vector<SinhVien> &);
    void capNhatDong(const int &, const SinhVien &);
    SinhVien LaySinhVienOBang(const int &) const; // lấy sinh vien tai dòng thư i
    void capNhatDanhSachSV();
public:
    giaoDienChinh(QuanLyKTX &);
    void capNhatTT() override;
    void bieuDien() override;
    ~giaoDienChinh();
};
#endif