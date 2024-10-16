#pragma once

#include "raylib.h"
#include <string>
using namespace std;
class hopNhap
{
    Rectangle hinhThai; // vị trí ô, chiều dài, chiều rộng
    string chu;         // text trong ô
    Color mauChu;       // màu chữ trong ô
    Color mauNen;       // màu trong ô
    Color mauVien;      // màu đường viền
    bool tTchon;        // trang thai chon
    bool coChuotChi;    // chuột đang chỉ vào ô
    float doDayVien;

    int coChu;
    Font kieuChu;
    static double tGBatDauNhan;
    static double tGTamThoi;
public:

    hopNhap(Rectangle = {0, 0, 0, 0}, const string = "", Color = WHITE, Color = WHITE, Color = BLACK);
    void cViTri(const int, const int);
    void cKichCo(const int, const int);
    void cMauNen(Color);
    void cMauVien(Color);
    void cDoDayVien(float);
    void cNoiDung(const string chu);
    void cMauChu(Color);
    void cCoChu(int);

    void capNhatTT();

    void bieuDien();

    string layChu();
    Vector2 layViTri();
    Vector2 layKichCo();
    ~hopNhap();
};
