
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
    int mucBacDien[6];
    double giaTienDien[6]; // theo các tính tiền điện của bậc điện (tiền điện được tính theo 6 bật)
    double giaTienNuoc;
    void capNhatTinhToan(const int &, const int &);
    void veKhoiTao();
    QuanLy<QuanLy<string>> *heThong;

public:
    gDDienNuoc(QuanLy<Phong> *, QuanLy<QuanLy<string>> &);
    void capNhatTT() override;
    void bieuDien() override;
    ~gDDienNuoc();
};

#endif