#ifndef _GIAODIENCHINH
#define _GIEODIENCHINH

#include "raylib.h"
#include "giaoDien.h"
#include "quanLyGiaoDien.h"
#include "hopChu.h"
#include "hop.h"
#include "bang.h"

#include "../utils/QuanLy.h"
#include "../utils/Nguoi.h"
#include "../utils/SinhVien.h"
// #include "utils/Phong.h"
#include "../utils/docGhiFile.h"

class giaoDienChinh : public giaoDien
{
private:
    quanLyGiaoDien *qLGiaoDien;
    Font font28;
    Bang *table;
    hopChu *boxThemSinhVien, *boxXoaHet, *boxTimKiem;
    QuanLy<SinhVien> *danhSachQLSV;
    int soSinhVien,sohangBD;
    bool flagTimKiem;
    int *viTriLuu,soDoiTuongTim; // dùng để tìm kiếm
    void capNhatThuTu();

public:
    giaoDienChinh(quanLyGiaoDien &);
    void capNhatTT() override;
    void bieuDien() override;
    ~giaoDienChinh();
};
#endif