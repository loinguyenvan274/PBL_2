#include "Phong.h"

Phong::Phong(string maPhong, int soNguoiToiDa, string moTa) : maPhong(maPhong), soNguoiToiDa(soNguoiToiDa), moTa(moTa), soNguoiHienTai(0) {}

const string &Phong::lMaPhong() const { return maPhong; }

const string &Phong::lMoTa() const { return moTa; }

const int &Phong::lSoNguoiHienTai() const { return soNguoiHienTai; }

const int &Phong::lSoNguoiToiDa() const { return soNguoiToiDa; }

void Phong::cMaPhong(const string &maPhong) { this->maPhong = maPhong; }

void Phong::cMoTa(const string &moTa) { this->moTa = moTa; }

void Phong::cSoNguoiToiDa(const int &soNguoiToiDa) { this->soNguoiToiDa = soNguoiToiDa; }

void Phong::cSoNguoiHienTai(const int &soNguoiHienTai) { this->soNguoiHienTai = soNguoiHienTai; }
QuanLy<string> Phong::lThongTin()
{
    /*
    list theo theo thứ tự :họ và tên , ngày sinh, mã ,ngày bắt đầu ỏ,thời gian ở, mã phòng
    */
    QuanLy<string> dSThuocTinh(4);
    dSThuocTinh[0] = maPhong;
    dSThuocTinh[1] = to_string(soNguoiToiDa);
    dSThuocTinh[2] = to_string(soNguoiHienTai);
    dSThuocTinh[3] = moTa;
    return dSThuocTinh;
}
void Phong::cThongTin(const QuanLy<string> &dSThuocTinhDV)
{
    maPhong = dSThuocTinhDV[0];
    soNguoiToiDa =stoi( dSThuocTinhDV[1]);
    soNguoiHienTai = stoi(dSThuocTinhDV[2]);
    moTa = dSThuocTinhDV[3];
}

void Phong::hienThiThongTin() const
{
    cout << "Ma phong: " << maPhong << endl;
    cout << "Mo ta: " << moTa << endl;
    cout << "So nguoi toi da: " << soNguoiToiDa << endl;
    cout << "so nguoi hien tai: " << soNguoiHienTai << endl;
}
