#ifndef _CUASOCON
#define _CUASOCON
#include "Bang.h"
#include "../app/Vector.h"

class cuaSoCon
{
public:
    Vector2 viTri;
    Vector2 kichThuoc;
    Vector<hopChu> dShopChu, dSHopHienThi;
    hop khungCuaSo;

    cuaSoCon(const Vector2 & = {.0f, .0f}, const Vector2 & = {100.0f, 100.0f});
    void capNhatTT();
    void bieuDien();
    ~cuaSoCon();
};

#endif
