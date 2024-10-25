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

class giaoDien
{
protected:
    QuanLy<SinhVien> *qLSV;
    QuanLy<Phong> *qLPhong;
    int soSinhVien, soPhong;

    Bang *table;
    hopChu *boxThem, *boxXoaHet, *boxTimKiem;
    int sohangBD;
    bool flagTimKiem;
    int *viTriLuu, soDoiTuongTim; // dùng để tìm kiếm
    string chuoiTimSoSanh;        // dung để kiểm tra cập nhật tìm kiếm nếu chuổi vừa mới nhật khác chuổi vừa nảy thì sẽ tìm kiếm lại

public:
    static Font font28;
    virtual void capNhatTT() = 0;
    virtual void bieuDien() = 0;
    virtual ~giaoDien() = default;
};

#endif