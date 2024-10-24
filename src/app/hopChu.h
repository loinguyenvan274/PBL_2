#pragma once

#include "hop.h"
#include "raylib.h"
#include <string>

using namespace std;

class hopChu : public hop
{
    string chu;   // text trong ô
    Color mauChu; // màu chữ trong ô
    int coChu;
    Font kieuChu;
    static double tGBatDauNhan;
    static double tGTamThoi;

public:
    hopChu(Rectangle = {0, 0, 0, 0}, const string = "", Color = WHITE, Color = RED, Color = BLACK);

    void cNoiDung(const string chu);
    void cMauChu(const Color &);
    void cCoChu(int);

    void capNhatTT();
    void cKieuChu(const Font &);
    void bieuDien();

    string layChu();

    ~hopChu();
};
