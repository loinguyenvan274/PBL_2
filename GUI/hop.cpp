#include "hop.h"

hop::hop(Rectangle hinhThai, Color mauNen, Color mauVien) : hinhThai(hinhThai), mauNen(mauNen), mauVien(mauVien)
{
    tTchon = false;
    coChuotChi = false;
    doDayVien = 0;
}

hop::~hop() {}
void hop::cVitri(const float &x, const float &y)
{
    hinhThai.x = x;
    hinhThai.y = y;
}
void hop::cKichCo(const float &with, const float &height)
{
    hinhThai.width = with;
    hinhThai.height = height;
}
void hop::cMauNen(const Color &mauNenDV) { mauNen = mauNenDV; }
void hop::cMauVien(const Color &mauVienDV) { mauNen = mauVienDV; }
Vector2 hop::layViTri() { return Vector2{hinhThai.x, hinhThai.y}; }
Vector2 hop::layKichCo() { return Vector2{hinhThai.width, hinhThai.height}; }
void hop::cDoDayVien(float doDayDV) { doDayVien = doDayDV; }

void hop::bieuDien()
{
    float doDayVien;
    if (tTchon || coChuotChi)
        doDayVien = this->doDayVien;
    else
        doDayVien = 0;
    DrawRectangle(hinhThai.x, hinhThai.y, hinhThai.width, hinhThai.height, mauVien);
    DrawRectangle(hinhThai.x + doDayVien, hinhThai.y + doDayVien, hinhThai.width - doDayVien * 2, hinhThai.height - doDayVien * 2, mauNen);
}
void hop::capNhatTT()
{
    if ((GetMouseX() > hinhThai.x && GetMouseX() < hinhThai.x + hinhThai.width && GetMouseY() > hinhThai.y && GetMouseY() < hinhThai.y + hinhThai.height))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            this->tTchon = true;
        this->coChuotChi = true;
    }
    else
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            tTchon = false;
        this->coChuotChi = false;
    }
}