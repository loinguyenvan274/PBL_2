#include "hopNhap.h"
#include <iostream>

double hopNhap::tGTamThoi = 0;
double hopNhap::tGBatDauNhan = 0;

hopNhap::hopNhap(Rectangle hinhThaiDV, const string chuDV, Color mauNenDV, Color mauVienDV, Color mauChuDV) : hop(hinhThaiDV, mauNenDV, mauVienDV), chu(chuDV), mauChu(mauChuDV)
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

void hopNhap::cMauChu(const Color &mauDV) { mauChu = mauDV; }
void hopNhap::cNoiDung(const string chuDV) { chu = chuDV; }
void hopNhap::cCoChu(int coChuDV)
{
    coChu = coChuDV;
    UnloadFont(kieuChu);
    kieuChu = LoadFontEx("arial.ttf", coChu, vietnameseCodepoints, sizeof(vietnameseCodepoints) / sizeof(int));
}

void hopNhap::bieuDien()
{
    hop::bieuDien();
    DrawTextEx(kieuChu, chu.substr((chu.size() > hinhThai.width / (coChu / 2.8)) ? chu.size() - hinhThai.width / (coChu / 2.8) : 0).c_str(), (Vector2){hinhThai.x + this->doDayVien, hinhThai.y + this->doDayVien + (hinhThai.height - coChu) / 2}, coChu, 1.0f, mauChu);
}
void hopNhap::capNhatTT()
{
    hop::capNhatTT();
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
        if (IsKeyDown(KEY_BACKSPACE) && GetTime() - tGBatDauNhan > 0.8)
        {

            if (!chu.empty() && GetTime() - tGTamThoi > 0.04)
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

string hopNhap::layChu() { return chu; }