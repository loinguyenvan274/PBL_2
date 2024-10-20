#ifndef _GIAODIEN
#define _GIAODIEN

class giaoDien
{
public:
    virtual void capNhatTT() = 0;
    virtual void bieuDien() = 0;
    virtual ~giaoDien() = default;
};
#endif