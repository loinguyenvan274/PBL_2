#ifndef _PHONG
#define _PHONG
#include <string>
#include "Vector.h"
using namespace std;
class Phong
{
private:
    string maPhong;
    string moTa;
    unsigned int soNguoiToiDa;
    unsigned int soNguoiHienTai;
    float dienCSDT, dienCSCT, nuocCSDT, nuocCSCT;
    unsigned long giaPhong;
    bool nopTienDN;

public:
    Phong(string maPhong = "", int soNguoiToiDa = 0, string moTa = "");
    const string &lMaPhong() const;
    const string &lMoTa() const;
    const unsigned int &lSoNguoiToiDa() const;
    const unsigned int &lSoNguoiHienTai() const;
    const float &lDienCSDT() const;
    const float &lDienCSCT() const;
    const float &lNuocCSDT() const;
    const float &lNuocCSCT() const;
    const bool &daNopTienDN() const;
    const unsigned long &lGiaPhong() const;
    bool operator==(const Phong &) const;
    Phong &operator=(const Phong &);

    void cMaPhong(const string &);
    void cMoTa(const string &);
    void cSoNguoiHienTai(const unsigned int &);
    void cSoNguoiToiDa(const unsigned int &);
    void cDienCSDT(const float &);
    void cDienCSCT(const float &);
    void cNuocCSDT(const float &);
    void cGiaPhong(const unsigned long &);
    void cNuocCSCT(const float &);
    void cNopTienDN(const bool &);

    // dùng danh mảng chứa các dữ liệu để cập nhật
    void cThongTin(const Vector<string> &);
    Vector<string> lThongTin();

    void hienThiThongTin() const; // hiển thị thông tin ra màng hình console
};

#endif
