#ifndef _DG_THIET_LAP
#define _DG_THIET_LAP
#include "giaoDien.h"

class gDThietLap : public giaoDien
{
private:
    Bang *table;
    void vekhoiTao();
    void capNhatVaoHeThong();
    NutTuyChon tuyChonNgonNgu;
    NutTuyChon tuyChonChuDe;
    int nutNgonNguHienTai;

public:
    gDThietLap(QuanLyKTX &, HeThong &);
    void bieuDien() override;
    void capNhatTT() override;
    ~gDThietLap();
};

#endif
