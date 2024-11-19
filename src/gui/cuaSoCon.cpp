#include "cuaSoCon.h"

cuaSoCon::cuaSoCon(const Vector2 &viTri, const Vector2 &kichThuoc) : viTri(viTri), kichThuoc(kichThuoc)
{
    khungCuaSo = hop(Rectangle{viTri.x, viTri.y, kichThuoc.y, kichThuoc.x}, WHITE, BLACK);
}

cuaSoCon::~cuaSoCon() {}

void cuaSoCon::capNhatTT()
{

    int i;
    for (i = 0; i < dShopChu.lSoPhanTu(); i++)
    {
        dShopChu[i].capNhatTT();
    }
}
void cuaSoCon::bieuDien()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{255, 255, 255, 80});
    khungCuaSo.bieuDien();
    int i;
    for (i = 0; i < dShopChu.lSoPhanTu(); i++)
    {
        dShopChu[i].bieuDien();
    }
    for (i = 0; i < dSHopHienThi.lSoPhanTu(); i++)
    {
        dSHopHienThi[i].bieuDien();
    }
}
