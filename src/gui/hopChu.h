#pragma once

#include "hop.h"
#include <string>
#include "../app/Vector.h"

extern const int vietnameseCodepoints[2332];

using namespace std;

class hopChu : public hop
{
    wstring chu; // text trong ô
    wstring chuoiIME;
    wstring strChuoiIME;
    string chuCoDinh;
    Color mauChu; // màu chữ trong ô
    int coChu;
    Font kieuChu;
    static double tGBatDauNhan;
    static double tGTamThoi;
    bool chiNhapSo; // chỉ cho phép nhập số
    Vector2 viTriConTro;
    int soKiTuTruocConTro;
    bool flagChuThayThe;

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
    void cChuCoDinh(const string &);
    void cFlagChuCoDinh(const bool &);
    NTN lNTN();

    string layChu();

    ~hopChu();
};
