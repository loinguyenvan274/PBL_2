#ifndef _GIAODIENCHINH
#define _GIEODIENCHINH

#include "raylib.h"
#include "giaoDien.h"

class giaoDienPhong : public giaoDien
{
private:
    void capNhatThuTu();

public:
    giaoDienPhong(QuanLy<Phong> *);
    void capNhatTT() override;
    void bieuDien() override;
    ~giaoDienPhong();
};
#endif