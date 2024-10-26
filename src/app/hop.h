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
    void cVitri(const float &, const float &);
    void cKichCo(const float &, const float &);
    void cMauNen(const Color &);
    void cMauVien(const Color &);
    void cDoDayVien(float);
    Vector2 layViTri();
    Vector2 layKichCo();
    const bool &laDuocChon();
    void cTrangThaiChon(const bool &);

    virtual void capNhatTT();
    virtual void bieuDien();

    ~hop();
};

#endif