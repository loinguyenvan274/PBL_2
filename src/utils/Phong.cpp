#include "Phong.h"

Phong::Phong(string maPhong, int soNguoiToiDa, string moTa) : maPhong(maPhong), soNguoiToiDa(soNguoiToiDa), moTa(moTa), soNguoiHienTai(0), dienCSCT(0.0f), dienCSDT(0.0f), nuocCSDT(0.0f), nuocCSCT(0.0f), nopTienDN(false) {}

const string &Phong::lMaPhong() const { return maPhong; }
const string &Phong::lMoTa() const { return moTa; }

const unsigned int &Phong::lSoNguoiHienTai() const { return soNguoiHienTai; }
const unsigned int &Phong::lSoNguoiToiDa() const { return soNguoiToiDa; }

const float &Phong::lDienCSDT() const { return dienCSDT; }
const float &Phong::lDienCSCT() const { return dienCSCT; }
const float &Phong::lNuocCSDT() const { return nuocCSDT; }
const float &Phong::lNuocCSCT() const { return nuocCSCT; }
const bool &Phong::daNopTienDN() const { return nopTienDN; }

void Phong::cMaPhong(const string &maPhong) { this->maPhong = maPhong; }
void Phong::cMoTa(const string &moTa) { this->moTa = moTa; }

void Phong::cSoNguoiToiDa(const unsigned int &soNguoiToiDa) { this->soNguoiToiDa = soNguoiToiDa; }
void Phong::cSoNguoiHienTai(const unsigned int &soNguoiHienTai) { this->soNguoiHienTai = soNguoiHienTai; }

void Phong::cDienCSDT(const float &dienCSDT) { this->dienCSDT = dienCSDT; }
void Phong::cDienCSCT(const float &dienCSCT) { this->dienCSCT = dienCSCT; }
void Phong::cNuocCSDT(const float &nuocCSDT) { this->nuocCSDT = nuocCSDT; }
void Phong::cNuocCSCT(const float &nuocCSCT) { this->nuocCSCT = nuocCSCT; }
void Phong::cNopTienDN(const bool &nopTienDN) { this->nopTienDN = nopTienDN; }

QuanLy<string> Phong::lThongTin()
{
    /*
    list theo theo thứ tự :họ và tên , ngày sinh, mã ,ngày bắt đầu ỏ,thời gian ở, mã phòng
    */
    QuanLy<string> thuocTinh(9);
    thuocTinh[0] = maPhong;
    thuocTinh[1] = to_string(soNguoiToiDa);
    thuocTinh[2] = to_string(soNguoiHienTai);
    thuocTinh[3] = moTa;
    thuocTinh[4] = to_string(dienCSDT);
    thuocTinh[5] = to_string(dienCSCT);
    thuocTinh[6] = to_string(nuocCSDT);
    thuocTinh[7] = to_string(nuocCSCT);
    if (nopTienDN)
        thuocTinh[8] = "1";
    else
        thuocTinh[8] = "0";
    return thuocTinh;
}
void Phong::cThongTin(const QuanLy<string> &thuocTinhDV)
{
    maPhong = thuocTinhDV[0];
    soNguoiToiDa = stoi(thuocTinhDV[1]);
    soNguoiHienTai = stoi(thuocTinhDV[2]);
    moTa = thuocTinhDV[3];
    dienCSDT = stof(thuocTinhDV[4]);
    dienCSCT = stof(thuocTinhDV[5]);
    nuocCSDT = stof(thuocTinhDV[6]);
    nuocCSCT = stof(thuocTinhDV[7]);
    if (thuocTinhDV[8] == "1")
        nopTienDN = true;
    else
        nopTienDN = false;
}

void Phong::hienThiThongTin() const
{
    cout << "Ma phong: " << maPhong << endl;
    cout << "Mo ta: " << moTa << endl;
    cout << "So nguoi toi da: " << soNguoiToiDa << endl;
    cout << "so nguoi hien tai: " << soNguoiHienTai << endl;
}
