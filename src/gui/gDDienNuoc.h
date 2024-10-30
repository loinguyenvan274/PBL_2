
#ifndef _GIAODIENCHINH
#define _GIEODIENCHINH

#include "raylib.h"
#include "giaoDien.h"

class gDDienNuoc : public giaoDien
{
private:
    void capNhatThuTu();
    void capNhatDong(const int &, const Phong &);
    void capNhatBang(const Vector<Phong> &);

    Bang *thanhDienNuoc;
    hopChu boxReset;

    hopChu boxResetHet;
    hopChu boxResetCoLay; // sao  chỉ số cột chỉ số điện nước tháng này làm tháng sau ;
    hopChu boxSetGiaTien;
    hop nutTat; // tắt ô cửa sổ con
    Bang *BangSetGiaTienDien;
    hopChu boxXuatFile;

    int mucBacDien[6];
    double giaTienDien[6]; // theo các tính tiền điện của bậc điện (tiền điện được tính theo 6 bật)
    double giaTienNuoc;
    string chuoiMoi; // dùng để so sánh và cập nhật nếu có thay đổi khi nhập để gọi void capNhatTinhToan(const int &, const int &) lúc cần thiết

    void capNhatTinhToan(const int &, const Phong &);
    void veKhoiTao();
    void initDienNuoc();
    void resetCapNhatTT();
    Vector<Vector<string>> *heThong;
    void cuaSoCon(const float &, const float &, const string &);

    void cSResetBieuDien();
    void cSResetCapNhatTT();
    void cSTLGiaTienBieuDien();
    void cSTLGiaTienCapNhatTT();

    void kTBangNhapGia();

    void XuatFile();
    void ghiFileVaoDiaChi(const char *);

public:
    gDDienNuoc(QuanLyKTX &, Vector<Vector<string>> &);
    void capNhatTT() override;
    void bieuDien() override;
    ~gDDienNuoc();
};

#endif