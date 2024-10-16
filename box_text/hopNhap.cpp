#include "hopNhap.h"
#include <iostream>

double hopNhap::tGTamThoi = 0;
double hopNhap::tGBatDauNhan = 0;

hopNhap::hopNhap(Rectangle hinhThaiDV, const string chuDV, Color mauNenDV, Color mauVienDV, Color mauChuDV) : hinhThai(hinhThaiDV), chu(chuDV), mauChu(mauChuDV), mauNen(mauNenDV), mauVien(mauVienDV)
{
    coChu = 28;
    kieuChu = LoadFontEx("arial.ttf", coChu, vietnameseCodepoints, sizeof(vietnameseCodepoints) / sizeof(int));
    tTchon = false;
    coChuotChi = false;
    doDayVien = 0;
}
hopNhap ::~hopNhap()
{
    UnloadFont(kieuChu);
}

void hopNhap::cViTri(const int x, const int y)
{
    hinhThai.x = x;
    hinhThai.y = y;
}
void hopNhap::cKichCo(const int w, const int h)
{
    hinhThai.width = w;
    hinhThai.height = h;
}
void hopNhap::cDoDayVien(float doDayDV) { doDayVien = doDayDV; }
void hopNhap::cMauNen(Color mauDV) { mauNen = mauDV; }
void hopNhap::cMauChu(Color mauDV) { mauChu = mauDV; }
void hopNhap::cMauVien(Color mauDV) { mauVien = mauDV; }
void hopNhap::cNoiDung(const string chuDV) { chu = chuDV; }
void hopNhap::cCoChu(int coChuDV)
{
    coChu = coChuDV;
    UnloadFont(kieuChu);
    kieuChu = LoadFontEx("arial.ttf", coChu, vietnameseCodepoints, sizeof(vietnameseCodepoints) / sizeof(int));
}

string hopNhap::layChu() { return chu; }
Vector2 hopNhap::layViTri() { return Vector2{hinhThai.x, hinhThai.y}; }
Vector2 hopNhap::layKichCo() { return Vector2{hinhThai.width, hinhThai.height}; }
void hopNhap::bieuDien()
{
    float doDayVien;
    if (tTchon || coChuotChi)
        doDayVien = this->doDayVien;
    else
        doDayVien = 0;
    DrawRectangle(hinhThai.x, hinhThai.y, hinhThai.width, hinhThai.height, mauVien);
    DrawRectangle(hinhThai.x + doDayVien, hinhThai.y + doDayVien, hinhThai.width - doDayVien * 2, hinhThai.height - doDayVien * 2, mauNen);
    DrawTextEx(kieuChu, chu.substr((chu.size() > hinhThai.width / coChu*3) ? chu.size() - hinhThai.width / coChu*3 : 0).c_str(), (Vector2){hinhThai.x + this->doDayVien, hinhThai.y + this->doDayVien + (hinhThai.height - coChu) / 2}, coChu, 1.0f, mauChu);
}

void hopNhap::capNhatTT()
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
    // chinh sua text khi chuot duoc chon
    if (tTchon)
    {
        char kyTuVuaNhan = GetCharPressed();

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            tGBatDauNhan = tGTamThoi = GetTime();
            if (!chu.empty())
            {
                chu.pop_back();
            }
        }
        if (IsKeyDown(KEY_BACKSPACE) && GetTime() - tGBatDauNhan > 1)
        {

            if (!chu.empty() && GetTime() - tGTamThoi > 0.08)
            {
                tGTamThoi = GetTime();
                chu.pop_back();
            }
        }
        else if (kyTuVuaNhan != 0)
        {
            chu += kyTuVuaNhan;
        }
    }
}