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
    enum flagGiaoDien flagGD;
    enum flagGiaoDien flagGDMoi;

    QuanLy<SinhVien> *qLSV;
    QuanLy<Phong> *qLPhong;
    giaoDien *gDHienThi;

    Bang *thanhChuyen;

public:
    quanLyGiaoDien(QuanLy<SinhVien> *, QuanLy<Phong> *);
    void bieuDien();
    void capNhatTT();
    void xoa();
    void doi(giaoDien *gDHienThi); // Nhận con trỏ
    ~quanLyGiaoDien();
};

#endif
