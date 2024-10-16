#ifndef _HOP
#define _HOP

#include "raylib.h"
class hop
{
protected:
    Rectangle hinhThai; // vị trí ô, chiều dài, chiều rộng

    float doDayVien;

    Color mauNen;  // màu trong ô
    Color mauVien; // màu đường viền

    bool tTchon;     // trang thai chon
    bool coChuotChi; // chuột đang chỉ vào ô

public:
    hop(Rectangle = {0, 0, 0, 0}, Color = BLACK, Color = RED);
    void cVitri(const int &, const int &);
    void cKichCo(const int &, const int &);
    void cMauNen(const Color &);
    void cMauVien(const Color &);
    void cDoDayVien(float);
    Vector2 layViTri();
    Vector2 layKichCo();

    virtual void capNhatTT();
    virtual void bieuDien();
    
    ~hop();
};

#endif