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
    int soNguoiHienTai;

public:
    Phong(string maPhong = "", int soNguoiToiDa = 0, string moTa = "");
    const string &lMaPhong() const;
    const string &lMoTa() const;
    const int &lSoNguoiToiDa() const;
    const int &lSoNguoiHienTai() const;
    void cMaPhong(const string &);
    void cMoTa(const string &);
    void cSoNguoiHienTai(const int &);
    void cSoNguoiToiDa(const int &);
    // dùng danh mảng chứa các dữ liệu để cập nhật
    void cThongTin(const QuanLy<string> &);
    QuanLy<string> lThongTin();

    void hienThiThongTin() const; // hiển thị thông tin ra màng hình console
};

#endif
