#ifndef _QUANLYGIAODIEN
#define _QUANLYGIAODIEN
#include "nganXep.h"
#include "giaoDien.h"

class quanLyGiaoDien
{
private:
    NganXep<giaoDien *> trangThai; // Sử dụng con trỏ giaoDien

public:
    void bieuDien()
    {
        trangThai.layDinh()->bieuDien(); // Truy cập con trỏ
    }
    void capNhatTT()
    {
        trangThai.layDinh()->capNhatTT(); // Truy cập con trỏ
    }
    void xoa()
    {
        trangThai.xoaDinh();
    }
    void them(giaoDien *dD) // Nhận con trỏ
    {
        trangThai.dayLen(dD);
    }
};
#endif
