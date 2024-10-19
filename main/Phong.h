#ifndef _PHONG
#define _PHONG
#include <string>
#include "QuanLy.h"
using namespace std;
class Phong
{
private:
    string maPhong;
    string moTa;
    int soNguoiToiDa;
    QuanLy<dienNuoc> soDienNuoc();
public:
    Phong(string maPhong = "", int soNguoiToiDa = 0, string moTa = "");
    string lMaPhong() const;
    string lMoTa() const;
    int lSoNguoiToiDa() const;
    void cMaPhong(string maPhong);
    void cMoTa(string moTa);
    void cSoNguoiToiDa(int soNguoiToiDa);
    void hienThiThongTin() const;
};

#endif