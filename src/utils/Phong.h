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
    unsigned int soNguoiToiDa;
    unsigned int soNguoiHienTai;
    float dienCSDT, dienCSCT, nuocCSDT, nuocCSCT;

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

    void cMaPhong(const string &);
    void cMoTa(const string &);
    void cSoNguoiHienTai(const unsigned int &);
    void cSoNguoiToiDa(const unsigned int &);
    void cDienCSDT(const float &);
    void cDienCSCT(const float &);
    void cNuocCSDT(const float &);
    void cNuocCSCT(const float &);

    // dùng danh mảng chứa các dữ liệu để cập nhật
    void cThongTin(const QuanLy<string> &);
    QuanLy<string> lThongTin();

    void hienThiThongTin() const; // hiển thị thông tin ra màng hình console
};

#endif
