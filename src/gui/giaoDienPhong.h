#ifndef _GIAODIENCHINH
#define _GIEODIENCHINH

#include "raylib.h"
#include "giaoDien.h"

class giaoDienPhong : public giaoDien
{
private:
    // void capNhatThuTu();
    void capNhatDong(const int &, const Phong &);
    void capNhatBang(const Vector<Phong> &);
    Phong lPhongTuBang(const int &) const;
    void capNhatDanhSachPhong();

public:
    giaoDienPhong(QuanLyKTX &quanLyKTX);
    void capNhatTT() override;
    void bieuDien() override;
    ~giaoDienPhong();
};
#endif