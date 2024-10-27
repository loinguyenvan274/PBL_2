#ifndef _GIAODIEN
#define _GIAODIEN
#include "hopChu.h"
#include "hop.h"
#include "bang.h"

#include "../utils/QuanLy.h"
#include "../utils/Nguoi.h"
#include "../utils/SinhVien.h"
#include "../utils/Phong.h"
#include "../utils/docGhiFile.h"

#define MAU_XANH {65, 105, 225, 255}
#define MAU_LA_CAY {0, 128, 128, 255}
#define MAU_DEN_MO {255,255,255,80}

class giaoDien
{
protected:
    QuanLy<SinhVien> *qLSV;
    QuanLy<Phong> *qLPhong;
    int soSinhVien, soPhong;

    Bang *table;
    hopChu boxThem, *boxXoa, *boxTimKiem;
    int sohangBD;
    bool flagTimKiem;
    int *viTriLuu, soDoiTuongTim;                              // dùng để tìm kiếm
    string chuoiTimSoSanh;                                     // dung để kiểm tra cập nhật tìm kiếm nếu chuổi vừa mới nhật khác chuổi vừa nảy thì sẽ tìm kiếm lại
    const string float_string(const float &, const int & = 4); // loai bỏ số 000 dư thừa phía sau;
public:
    static Font font28;
    virtual void capNhatTT() = 0;
    virtual void bieuDien() = 0;
    virtual ~giaoDien() = default;
};

#endif