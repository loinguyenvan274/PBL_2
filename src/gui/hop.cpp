#include "hop.h"

hop::hop(Rectangle hinhThai, Color mauNen, Color mauVien) : hinhThai(hinhThai), mauNen(mauNen), mauVien(mauVien)
{
    tTChon = false;
    coChuotChi = false;
    rangBuoc = false;
    doDayVien = 2.0;
    doBoVien = 0;
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
Vector2 hop::layViTri() const { return Vector2{hinhThai.x, hinhThai.y}; }
Vector2 hop::layKichCo() { return Vector2{hinhThai.width, hinhThai.height}; }
void hop::cDoDayVien(float doDayDV) { doDayVien = doDayDV; }
void hop::cDoBoVien(const float &doBoVienDV) { doBoVien = doBoVienDV; };
void hop::cRangBuoc(const bool &rangBuocDV) { rangBuoc = rangBuocDV; };

const bool &hop::laDuocChon() { return tTChon; }
const bool &hop::laRangBuoc() { return rangBuoc; }

void hop::cTrangThaiChon(const bool &TTChon) { tTChon = TTChon; }

void hop::bieuDien()
{
    float doDayVien;
    if (rangBuoc)
        doDayVien = this->doDayVien;
    else
        doDayVien = 0;

    int phanDoan = 30; // Số lượng phân đoạn cho bo góc
    // Vẽ viền bên ngoài
    DrawRectangleRounded((Rectangle){hinhThai.x, hinhThai.y, hinhThai.width, hinhThai.height}, doBoVien, phanDoan, mauVien);
    // Vẽ hình chữ nhật bên trong với độ bo và trừ đi độ dày viền
    DrawRectangleRounded((Rectangle){hinhThai.x + doDayVien, hinhThai.y + doDayVien, hinhThai.width - doDayVien * 2, hinhThai.height - doDayVien * 2}, doBoVien, phanDoan, mauNen);
    if (coChuotChi || tTChon)
    {
        DrawRectangleRounded((Rectangle){hinhThai.x + doDayVien, hinhThai.y + doDayVien, hinhThai.width - doDayVien * 2, hinhThai.height - doDayVien * 2}, doBoVien, phanDoan, Color{34, 139, 34, 120});
    }
}
void hop::capNhatTT()
{
    if ((GetMouseX() > hinhThai.x && GetMouseX() < hinhThai.x + hinhThai.width && GetMouseY() > hinhThai.y && GetMouseY() < hinhThai.y + hinhThai.height))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            this->tTChon = true;
        this->coChuotChi = true;
    }
    else
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            tTChon = false;
        this->coChuotChi = false;
    }
}