#ifndef _GIAODIENPHONG
#define _GIAODIENPHONG

#include "giaoDienChinh.h"


class giaoDienPhong : public giaoDien
{
private:
public:
    giaoDienPhong(quanLyGiaoDien &);
    void capNhatTT() override;
    void bieuDien() override;
    ~giaoDienPhong();
};
#endif