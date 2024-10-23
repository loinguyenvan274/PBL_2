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
string SinhVien::lNgayBatDauO() { return ngayBatDauO; }
string SinhVien::lMaPhong() { return maPhong; }
string SinhVien::lThoiGianO() { return thoiGianO; }
void SinhVien::bieuDien()
{
    cout << "Ten: " << hoVaTen << endl;
    cout << "Ma Sinh Vien: " << ma << endl;
    cout << "ma Phong" << maPhong << endl;
}
QuanLy<string> SinhVien::lThongTin()
{
    /*
    list theo theo thứ tự :họ và tên , ngày sinh, mã ,ngày bắt đầu ỏ,thời gian ở, mã phòng
    */
    QuanLy<string> dSThuocTinh(6);
    dSThuocTinh[0] = hoVaTen;
    dSThuocTinh[1] = ngaySinh;
    dSThuocTinh[2] = ma;
    dSThuocTinh[3] = ngayBatDauO;
    dSThuocTinh[4] = thoiGianO;
    dSThuocTinh[5] = maPhong;
    return dSThuocTinh;
}
void SinhVien::cThongTin(const QuanLy<string> &dSThuocTinhDV)
{
    QuanLy<string> dSThuocTinh(7);
    dSThuocTinh = dSThuocTinhDV;
    hoVaTen = dSThuocTinh[0];
    ngaySinh = dSThuocTinh[1];
    ma = dSThuocTinh[2];
    ngayBatDauO = dSThuocTinh[3];
    thoiGianO = dSThuocTinh[4];
    maPhong = dSThuocTinh[5];
}

SinhVien::~SinhVien() {}
