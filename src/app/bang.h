// số hàng, số cột, kích cở mỗi hàng, kích cơ mỗi cột
#ifndef _BANG
#define _BANG

#include "hop.h"
#include "hopChu.h"

class Bang
{
private:
    int soHang, soCot; 
    int cachHang, cachCot;// khoảng các giữa các ô trong cột
    int chanTren, chanDuoi, chanTRai, chanPhai;// dùng để xác định giới hạn vẽ
    bool tieuDe;
    Vector2 viTri;//ví trí của bảng
    hopChu **hop; // này là  cấp pháp ra nhiều hộp
    void cViTri();

public:
    Bang(const Vector2 & = {0, 0}, const int & = 2, const int & = 2, const Vector2 & = {20, 10});
    void cKieuChu(const Font &, const int & = 28);
    void cCot(const int &, const double &);
    void cHang(const int &, const double &);
    void cMauTheoO(const OXY &, const Color &);
    void cMauTheoCot(const int &, const Color &);
    void cMauTheoHang(const int &, const Color &);

    void cGioHanBD(const int &, const int &);
    void cTieuDe(const bool &);
    void cDangHangCot(const int &, const int &);
    hopChu &operator()(const int &, const int &); // overload truy xuất ô
    void capNhatTT() const;
    void bieuDien(const int &, const int &, const int &, const int &) const;
    void vungHoatDong(const int&, const int&, const int &, const int&) const;
    const Vector2 lViTri() const;

    Vector2 oHoatDong();

    ~Bang();
};

#endif