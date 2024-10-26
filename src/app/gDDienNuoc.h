
#ifndef _GIAODIENCHINH
#define _GIEODIENCHINH

#include "raylib.h"
#include "giaoDien.h"

class gDDienNuoc : public giaoDien
{
private:
    void capNhatThuTu();
    Bang *thanhDienNuoc;
    // void luuDuLieu() const;
    float giaDienTheoBac[5];
    float giaNuoc;
    void capNhatTinhToan(int i);

public:
    gDDienNuoc(QuanLy<Phong> *);
    void capNhatTT() override;
    void bieuDien() override;
    ~gDDienNuoc();
};
#endif