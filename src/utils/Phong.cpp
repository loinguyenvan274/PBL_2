#include "Phong.h"

Phong::Phong(string maPhong, int soNguoiToiDa, string moTa) : maPhong(maPhong), soNguoiToiDa(soNguoiToiDa), moTa(moTa), soNguoiHienTai(0), dienCSCT(0.0f), dienCSDT(0.0f), nuocCSDT(0.0f), nuocCSCT(0.0f) {}

const string &Phong::lMaPhong() const { return maPhong; }
const string &Phong::lMoTa() const { return moTa; }

const unsigned int &Phong::lSoNguoiHienTai() const { return soNguoiHienTai; }
const unsigned int &Phong::lSoNguoiToiDa() const { return soNguoiToiDa; }

const float &Phong::lDienCSDT() const { return dienCSDT; }
const float &Phong::lDienCSCT() const { return dienCSCT; }
const float &Phong::lNuocCSDT() const { return nuocCSDT; }
const float &Phong::lNuocCSCT() const { return nuocCSCT; }

void Phong::cMaPhong(const string &maPhong) { this->maPhong = maPhong; }
void Phong::cMoTa(const string &moTa) { this->moTa = moTa; }

void Phong::cSoNguoiToiDa(const unsigned int &soNguoiToiDa) { this->soNguoiToiDa = soNguoiToiDa; }
void Phong::cSoNguoiHienTai(const unsigned int &soNguoiHienTai) { this->soNguoiHienTai = soNguoiHienTai; }

void Phong::cDienCSDT(const float &dienCSDT) { this->dienCSDT = dienCSDT; }
void Phong::cDienCSCT(const float &dienCSCT) { this->dienCSCT = dienCSCT; }
void Phong::cNuocCSDT(const float &nuocCSDT) { this->nuocCSDT = nuocCSDT; }
void Phong::cNuocCSCT(const float &nuocCSCT) { this->nuocCSCT = nuocCSCT; }

QuanLy<string> Phong::lThongTin()
{
    /*
    list theo theo thứ tự :họ và tên , ngày sinh, mã ,ngày bắt đầu ỏ,thời gian ở, mã phòng
    */
    QuanLy<string> dSThuocTinh(8);
    dSThuocTinh[0] = maPhong;
    dSThuocTinh[1] = to_string(soNguoiToiDa);
    dSThuocTinh[2] = to_string(soNguoiHienTai);
    dSThuocTinh[3] = moTa;
    dSThuocTinh[4] = to_string(dienCSDT);
    dSThuocTinh[5] = to_string(dienCSCT);
    dSThuocTinh[6] = to_string(nuocCSDT);
    dSThuocTinh[7] = to_string(nuocCSCT);
    return dSThuocTinh;
}
void Phong::cThongTin(const QuanLy<string> &dSThuocTinhDV)
{
    maPhong = dSThuocTinhDV[0];
    soNguoiToiDa = stoi(dSThuocTinhDV[1]);
    soNguoiHienTai = stoi(dSThuocTinhDV[2]);
    moTa = dSThuocTinhDV[3];
    dienCSDT = stof(dSThuocTinhDV[4]);
    dienCSCT = stof(dSThuocTinhDV[5]);
    nuocCSDT = stof(dSThuocTinhDV[6]);
    nuocCSCT = stof(dSThuocTinhDV[7]);
}

void Phong::hienThiThongTin() const
{
    cout << "Ma phong: " << maPhong << endl;
    cout << "Mo ta: " << moTa << endl;
    cout << "So nguoi toi da: " << soNguoiToiDa << endl;
    cout << "so nguoi hien tai: " << soNguoiHienTai << endl;
}
