#include "hopChu.h"
#include <iostream>

double hopChu::tGTamThoi = 0;
double hopChu::tGBatDauNhan = 0;

hopChu::hopChu(Rectangle hinhThaiDV, const string chuDV, Color mauNenDV, Color mauVienDV, Color mauChuDV) : hop(hinhThaiDV, mauNenDV, mauVienDV), chu(chuDV), mauChu(mauChuDV)
{
    coChu = 28;
    kieuChu = GetFontDefault();
}
hopChu ::~hopChu() {}

void hopChu::cMauChu(const Color &mauDV) { mauChu = mauDV; }
void hopChu::cNoiDung(const string chuDV) { chu = chuDV; }
void hopChu::cCoChu(int coChuDV)
{
    coChu = coChuDV;
}
void hopChu::cKieuChu(const Font &kieuChuDV)
{
    kieuChu = kieuChuDV;
}

void hopChu::bieuDien()
{
    hop::bieuDien();
    DrawTextEx(kieuChu, chu.substr((chu.size() > hinhThai.width / (coChu / 2.8)) ? chu.size() - hinhThai.width / (coChu / 2.8) : 0).c_str(), (Vector2){hinhThai.x + this->doDayVien, hinhThai.y + this->doDayVien + (hinhThai.height - coChu) / 2}, coChu, 1.0f, mauChu);
}
void hopChu::capNhatTT()
{
    hop::capNhatTT();
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

string hopChu::layChu() { return chu; }