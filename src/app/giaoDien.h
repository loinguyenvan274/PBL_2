#ifndef _GIAODIEN
#define _GIAODIEN
#include "hopChu.h"
#include "hop.h"
#include "bang.h"

#include "../utils/QuanLy.h"
#include "../utils/Nguoi.h"
#include "../utils/SinhVien.h"
// #include "utils/Phong.h"
#include "../utils/docGhiFile.h"

class quanLyGiaoDien;

class giaoDien
{
protected:
    quanLyGiaoDien *qLGiaoDien;
    Font font28;
    Bang *table;
    hopChu *boxThemSinhVien, *boxXoaHet, *boxTimKiem;
    int soSinhVien, sohangBD;
    bool flagTimKiem;
    int *viTriLuu, soDoiTuongTim; // dùng để tìm kiếm
public:

    virtual void capNhatTT() = 0;
    virtual void bieuDien() = 0;
    virtual ~giaoDien() = default;
};
#endif