#include "Phong.h"

Phong::Phong(string maPhong, int soNguoiToiDa, string moTa) : maPhong(maPhong), soNguoiToiDa(soNguoiToiDa), moTa(moTa) {}
string Phong::lMaPhong() const { return maPhong; }

string Phong::lMoTa() const { return moTa; }

int Phong::lSoNguoiToiDa() const { return soNguoiToiDa; }

void Phong::cMaPhong(string maPhong) { this->maPhong = maPhong; }

void Phong::cMoTa(string moTa) { this->moTa = moTa; }

void Phong::cSoNguoiToiDa(int soNguoiToiDa) { this->soNguoiToiDa = soNguoiToiDa; }

void Phong::hienThiThongTin() const
{
    cout << "Ma phong: " << maPhong << endl;
    cout << "Mo ta: " << moTa << endl;
    cout << "So nguoi toi da: " << soNguoiToiDa << endl;
}
