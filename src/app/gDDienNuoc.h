
#ifndef _GIAODIENCHINH
#define _GIEODIENCHINH

#include "raylib.h"
#include "giaoDien.h"

class gDDienNuoc : public giaoDien
{
private:
    void capNhatThuTu();
    // void luuDuLieu() const;
public:
    gDDienNuoc(QuanLy<Phong> *);
    void capNhatTT() override;
    void bieuDien() override;
    ~gDDienNuoc();
};
#endif