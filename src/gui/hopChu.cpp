#include "hopChu.h"
#include <iostream>

double hopChu::tGTamThoi = 0;
double hopChu::tGBatDauNhan = 0;

hopChu::hopChu(Rectangle hinhThaiDV, const string chuDV, Color mauNenDV, Color mauVienDV, Color mauChuDV, Font kieuChu) : hop(hinhThaiDV, mauNenDV, mauVienDV), chu(chuDV), mauChu(mauChuDV), kieuChu(kieuChu)
{
    coChu = 26; // cở chử mặt định 26
    chiNhapSo = false;
}
hopChu ::~hopChu() {}

void hopChu::cMauChu(const Color &mauDV) { mauChu = mauDV; }
void hopChu::cNoiDung(const string chuDV) { chu = chuDV; }
void hopChu::cChiNhapSo(const bool &cChiNhapSo) { this->chiNhapSo = cChiNhapSo; }
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
    DrawTextEx(kieuChu, chu.c_str(), (Vector2){hinhThai.x + this->doDayVien, hinhThai.y + this->doDayVien + (hinhThai.height - coChu) / 2}, coChu, 1.0f, mauChu);
    // DrawTextEx(kieuChu, chu.substr((chu.size() > hinhThai.width / (coChu / 2.8)) ? chu.size() - hinhThai.width / (coChu / 2.8) : 0).c_str(), (Vector2){hinhThai.x + this->doDayVien, hinhThai.y + this->doDayVien + (hinhThai.height - coChu) / 2}, coChu, 1.0f, mauChu);
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
        else if (kyTuVuaNhan != 0 && kyTuVuaNhan != '~' && !((((kyTuVuaNhan < '0' || kyTuVuaNhan > '9') && kyTuVuaNhan != '.' || (chu == "" && kyTuVuaNhan == '.')) || chu.size() > 8) && chiNhapSo))
        {
            chu += kyTuVuaNhan;
        }
    }
}

NTN hopChu::lNTN()
{
    NTN ntn;

    size_t pos1 = chu.find('/');
    size_t pos2 = chu.rfind('/');

    if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2)
    {
        ntn.ngay = stoi(chu.substr(0, pos1));
        ntn.thang = stoi(chu.substr(pos1 + 1, pos2 - pos1 - 1));
        ntn.nam = stoi(chu.substr(pos2 + 1));
    }
    else
    {
        ntn.ngay = ntn.thang = ntn.nam = 0;
    }

    return ntn;
}

string hopChu::layChu() { return chu; }