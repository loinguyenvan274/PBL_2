#include "SinhVien.h"

SinhVien::SinhVien(const string &hoVaTenDV, const string &maDV, const string &ngaySinhDV) : Nguoi(hoVaTenDV, maDV, ngaySinhDV)
{

    maPhong = "";
}
void SinhVien::cNgayBatDauO(const string &thoiGianDV) { sDT = thoiGianDV; }
void SinhVien::cMaPhong(const string &maPhongDV) { maPhong = maPhongDV; }
void SinhVien::cThoiGianO(const string &thoiGianODV) { gioiTinh = thoiGianODV; }
string SinhVien::lSDT() const { return sDT; }
string SinhVien::lMaPhong() const { return maPhong; }
string SinhVien::lGioiTinh() const { return gioiTinh; }
void SinhVien::bieuDien() const
{
    cout << "Ten: " << hoVaTen << endl;
    cout << "Ma Sinh Vien: " << ma << endl;
    cout << "ma Phong" << maPhong << endl;
}
Vector<string> SinhVien::lThongTin() const
{
    /*
    list theo theo thứ tự :họ và tên , ngày sinh, mã ,ngày bắt đầu ỏ,thời gian ở, mã phòng
    */
    Vector<string> dSThuocTinh(6);
    dSThuocTinh[0] = hoVaTen;
    dSThuocTinh[1] = ngaySinh;
    dSThuocTinh[2] = ma;
    dSThuocTinh[3] = sDT;
    dSThuocTinh[4] = gioiTinh;
    dSThuocTinh[5] = maPhong;
    return dSThuocTinh;
}
void SinhVien::cThongTin(const Vector<string> &dSThuocTinhDV)
{
    hoVaTen = dSThuocTinhDV[0];
    ngaySinh = dSThuocTinhDV[1];
    ma = dSThuocTinhDV[2];
    sDT = dSThuocTinhDV[3];
    gioiTinh = dSThuocTinhDV[4];
    maPhong = dSThuocTinhDV[5];
}
SinhVien &SinhVien::operator=(const SinhVien &sinhvien)
{
    hoVaTen = sinhvien.hoVaTen;
    ngaySinh = sinhvien.lngaySinh();
    sDT = sinhvien.lSDT();
    gioiTinh = sinhvien.lGioiTinh();
    ma = sinhvien.lMa();
    maPhong = sinhvien.lMaPhong();
    return *this;
}

SinhVien::~SinhVien() {}
