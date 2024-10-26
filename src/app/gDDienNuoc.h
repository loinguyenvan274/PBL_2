
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
    hopChu *boxReset;

    hopChu boxResetHet;
    hopChu boxResetCoLay; // sao  chỉ số cột chỉ số điện nước tháng này làm tháng sau ;

    int mucBacDien[6];
    double giaTienDien[6]; // theo các tính tiền điện của bậc điện (tiền điện được tính theo 6 bật)
    double giaTienNuoc;
    string chuoiMoi; // dùng để so sánh và cập nhật nếu có thay đổi khi nhập để gọi void capNhatTinhToan(const int &, const int &) lúc cần thiết

    void capNhatTinhToan(const int &, const int &);
    void veKhoiTao();
    void capNhatBang();
    void resetCapNhat();
    QuanLy<QuanLy<string>> *heThong;
    void cuaSoReset();

public:
    gDDienNuoc(QuanLy<Phong> *, QuanLy<QuanLy<string>> &);
    void capNhatTT() override;
    void bieuDien() override;
    ~gDDienNuoc();
};

#endif