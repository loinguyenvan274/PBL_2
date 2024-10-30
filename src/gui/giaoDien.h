#ifndef _GIAODIEN
#define _GIAODIEN
#include "hopChu.h"
#include "hop.h"
#include "bang.h"

#include "../app/Vector.h"
#include "../app/Nguoi.h"
#include "../app/SinhVien.h"
#include "../app/Phong.h"
#include "../app/docGhiFile.h"
#include "../app/QuanLyKTX.h"

#define MAU_XANH {65, 105, 225, 255}
#define MAU_LA_CAY {0, 128, 128, 255}
#define MAU_DEN_MO {255, 255, 255, 80}

class giaoDien
{
protected:
    Vector<SinhVien> qLSV;
    Vector<Phong> *qLPhong;

    // bool flagNhap;

    QuanLyKTX &quanLyKTX;

    int soSinhVien, soPhong;

    Bang *table;
    hopChu boxThem, boxXoa, boxTimKiem;
    int sohangBD;
    bool flagTimKiem;                                          // dùng để tìm kiếm
    string chuoiTimSoSanh;                                     // dung để kiểm tra cập nhật tìm kiếm nếu chuổi vừa mới nhật khác chuổi vừa nảy thì sẽ tìm kiếm lại
    const string float_string(const float &, const int & = 4); // loai bỏ số 000 dư thừa phía sau;
public:
    static Font font28;
    giaoDien(QuanLyKTX &);
    virtual void capNhatTT() = 0;
    virtual void bieuDien() = 0;
    virtual ~giaoDien() = default;
};

#endif