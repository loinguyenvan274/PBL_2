#ifndef _GIAODIENCHINH
#define _GIEODIENCHINH

#include "raylib.h"
#include "giaoDien.h"

class giaoDienChinh : public giaoDien
{
private:
    QuanLy<SinhVien> *danhSachQLSV;
    void capNhatThuTu();
    void luuDuLieu() const;
public:
    giaoDienChinh(quanLyGiaoDien &);
    void capNhatTT() override;
    void bieuDien() override;
    ~giaoDienChinh();
};
#endif