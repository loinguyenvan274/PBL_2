// số hàng, số cột, kích cở mỗi hàng, kích cơ mỗi cột
#ifndef _BANG
#define _BANG

#include "hop.h"
#include "hopChu.h"

class Bang
{
private:
    int soHang, soCot;
    int cachHang, cachCot;                      // khoảng các giữa các ô trong cột
    int chanTren, chanDuoi, chanTRai, chanPhai; // dùng để xác định giới hạn vẽ
    bool tieuDe;
    Vector2 viTri;     // ví trí của bảng
    hopChu **hop;      // này là  cấp pháp ra nhiều hộp
    bool flagCuonBang; // là flag cuộn bản
    void cuon();       // cập nhật ví trí cuộn khi lăng con
public:
    Bang(const Vector2 & = {0, 0}, const int & = 2, const int & = 2, const Vector2 & = {20, 10});
    void cKieuChu(const Font &, const int & = 26);
    void cCot(const int &, const double &);
    void cHang(const int &, const double &);
    void cMauTheoO(const OXY &, const Color &);
    void cMauTheoCot(const int &, const Color &);
    void cMauTheoHang(const int &, const Color &);
    const int &lSoHang() const;
    const int &lSoCot() const;
    void cFlagCuon(const bool &);

    void cGioHanBD(const int &, const int &); // chỉnh giới hạn trên và giới hạn dưới tức có nghĩa là xác định vùng vẽ, vùng cập nhật trạng thái
    void cTieuDe(const bool &);
    void cGianHangCot(const int &, const int &);  // giãn hàng côt  tăng khoảng cách giữa các ô (tức là độ hở của các ô nếu = 0 tức hai ô liền với nhau nhìn như 1)
    hopChu &operator()(const int &, const int &); // overload truy xuất ô
    void capNhatTT();
    void bieuDien(const int &, const int &, const int &, const int &) const;     // vẽ
    void vungHoatDong(const int &, const int &, const int &, const int &) const; // xác định vùng nào sẽ cập nhật thạng thái
    const Vector2 lViTri() const;

    Vector2 oHoatDong();

    ~Bang();
};

#endif