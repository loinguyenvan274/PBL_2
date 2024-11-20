#ifndef _QUANLYGIAODIEN
#define _QUANLYGIAODIEN

#include "raylib.h"
#include "giaoDien.h"

enum flagGiaoDien
{
    FGD_SINH_VIEN,
    FGD_PHONG,
    FGD_DIEN_NUOC,
    FGD_THIET_LAP
};
/*
tên đơn vị,
địa chỉ,
giá Phòng mặt định
giá tiền thế chấp mặt định
ngôn ngữ,
giao diện (sang,tối)
*/

class quanLyGiaoDien
{
private:
    flagGiaoDien flagGD;
    flagGiaoDien flagGDMoi;

    Texture2D logoBachKhoa;
    Texture2D logoKhoaCntt;

    QuanLyKTX &quanLyKTX;

    giaoDien *gDHienThi;
    HeThong heThong;
    Bang *thanhChuyen;
    void initHeThong();
    void luuHeThong();
    void capNhatGDVoiHeThong();

public:
    quanLyGiaoDien(QuanLyKTX &);
    void bieuDien();
    void capNhatTT();
    void xoa();
    void doi(giaoDien *gDHienThi); // Nhận con trỏ
    ~quanLyGiaoDien();
};

#endif
