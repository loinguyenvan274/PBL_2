#ifndef _GIAODIENCHINH
#define _GIEODIENCHINH

#include "giaoDien.h"

class giaoDienPhong : public giaoDien
{
private:
    bool flagThongBaoKHL;

    void capNhatDong(const int &, const Phong &);
    void capNhatBang(const Vector<Phong> &);
    Phong lPhongTuBang(const int &) const;
    void capNhatDanhSachPhong();
    void cuaSoThongBaoKHL();
    void taoBang(const unsigned int &);
    hopChu boxHTSoPhongOBang;
    NutTuyChon cacNutChon;
    void taoNutTuyChon();

public:
    giaoDienPhong(QuanLyKTX &quanLyKTX, HeThong &HeThong);
    void capNhatTT() override;
    void bieuDien() override;
    ~giaoDienPhong();
};
#endif