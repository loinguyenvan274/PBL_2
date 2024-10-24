#ifndef _GIAODIENCHINH
#define _GIEODIENCHINH

#include "raylib.h"
#include "giaoDien.h"

class giaoDienChinh : public giaoDien
{
private:
    void capNhatThuTu();
    // void luuDuLieu() const;
public:
    giaoDienChinh(quanLyGiaoDien &, QuanLy<SinhVien> &);
    void capNhatTT() override;
    void bieuDien() override;
    ~giaoDienChinh();
};
#endif