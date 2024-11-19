#pragma once

#include "hop.h"
#include "raylib.h"
#include <string>
#include "../app/Vector.h"

using namespace std;

class hopChu : public hop
{
    string chu;   // text trong ô
    Color mauChu; // màu chữ trong ô
    int coChu;
    Font kieuChu;
    static double tGBatDauNhan;
    static double tGTamThoi;
    bool chiNhapSo; // chỉ cho phép nhập số

public:
    // (vị trí, chuôi , màu nên, màu viền, màu chữ )
    hopChu(Rectangle = {0, 0, 0, 0}, const string = "", Color = WHITE, Color = RED, Color = BLACK, Font = GetFontDefault());

    void cNoiDung(const string chu);
    void cMauChu(const Color &);
    void cCoChu(int);
    void capNhatTT();
    void cKieuChu(const Font &);
    void bieuDien();
    void cChiNhapSo(const bool &);
    NTN lNTN();

    string layChu();

    ~hopChu();
};
