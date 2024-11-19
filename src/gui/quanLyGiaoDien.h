#ifndef _QUANLYGIAODIEN
#define _QUANLYGIAODIEN

#include "raylib.h"
#include "giaoDien.h"

enum flagGiaoDien
{
    FGD_SINH_VIEN,
    FGD_PHONG,
    FGD_DIEN_NUOC
};

class quanLyGiaoDien
{
private:
    flagGiaoDien flagGD;
    flagGiaoDien flagGDMoi;

    Texture2D logoBachKhoa;
    Texture2D logoKhoaCntt;

    QuanLyKTX &quanLyKTX;

    giaoDien *gDHienThi;
    Vector<Vector<string>> heThong; // lưu giá tiền điện / tiền nước / bật tiền điện tiền, biến hệ thông...
    Bang *thanhChuyen;

public:
    quanLyGiaoDien(QuanLyKTX &);
    void bieuDien();
    void capNhatTT();
    void xoa();
    void doi(giaoDien *gDHienThi); // Nhận con trỏ
    ~quanLyGiaoDien();
};

#endif
