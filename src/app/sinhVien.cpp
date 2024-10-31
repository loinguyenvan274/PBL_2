#include "SinhVien.h"

SinhVien::SinhVien(const string &hoVaTenDV, const string &maDV, const string &ngaySinhDV) : Nguoi(hoVaTenDV, maDV, ngaySinhDV)
{
    ngayBatDauO = "";
    maPhong = "";
    thoiGianO = "";
}
void SinhVien::cNgayBatDauO(const string &thoiGianDV) { ngayBatDauO = thoiGianDV; }
void SinhVien::cMaPhong(const string &maPhongDV) { maPhong = maPhongDV; }
void SinhVien::cThoiGianO(const string &thoiGianODV) { thoiGianO = thoiGianODV; }
string SinhVien::lNgayBatDauO() const { return ngayBatDauO; }
string SinhVien::lMaPhong() const { return maPhong; }
string SinhVien::lThoiGianO() const { return thoiGianO; }
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
    dSThuocTinh[3] = ngayBatDauO;
    dSThuocTinh[4] = thoiGianO;
    dSThuocTinh[5] = maPhong;
    return dSThuocTinh;
}
void SinhVien::cThongTin(const Vector<string> &dSThuocTinhDV)
{
    hoVaTen = dSThuocTinhDV[0];
    ngaySinh = dSThuocTinhDV[1];
    ma = dSThuocTinhDV[2];
    ngayBatDauO = dSThuocTinhDV[3];
    thoiGianO = dSThuocTinhDV[4];
    maPhong = dSThuocTinhDV[5];
}
SinhVien &SinhVien::operator=(const SinhVien &sinhvien)
{
    hoVaTen = sinhvien.hoVaTen;
    ngaySinh = sinhvien.lngaySinh();
    ngayBatDauO = sinhvien.lNgayBatDauO();
    thoiGianO = sinhvien.lThoiGianO();
    ma = sinhvien.lMa();
    maPhong = sinhvien.lMaPhong();
    return *this;
}

SinhVien::~SinhVien() {}
