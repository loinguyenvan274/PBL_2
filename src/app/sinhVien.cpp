#include "SinhVien.h"
#include <ctime>

HopDongSinhVien::HopDongSinhVien()
{
    maPhong = "";
    // loaiPhong = "";
    soThangO = 0;
    // tienPhong = 0;
    tienTheChap = 0;
}

SinhVien::SinhVien(const string &hoVaTenDV, const string &maDV, const string &ngaySinhDV) : Nguoi(hoVaTenDV, maDV, ngaySinhDV) {}
string SinhVien::lMaPhong() const { return hopDong.maPhong; }
void SinhVien::cMaPhong(const string &maPhongDV) { hopDong.maPhong = maPhongDV; }
void SinhVien::bieuDien() const
{
    cout << "Ten: " << hoVaTen << endl;
    cout << "Ma Sinh Vien: " << ma << endl;
    cout << "ma Phong" << hopDong.maPhong << endl;
}
Vector<string> SinhVien::lThongTin() const
{
    /*
    list theo theo thứ tự :họ và tên , ngày sinh, mã ,ngày bắt đầu ỏ,thời gian ở, mã phòng
    */
    Vector<string> dSThuocTinh(11);
    dSThuocTinh[0] = hoVaTen;
    dSThuocTinh[1] = ngaySinh;
    dSThuocTinh[2] = ma;
    dSThuocTinh[3] = sDT;
    dSThuocTinh[4] = "1";
    if (gioiTinh == 0)
        dSThuocTinh[4] = "0";
    dSThuocTinh[5] = hopDong.maPhong;
    dSThuocTinh[6] = to_string(hopDong.tienTheChap);
    dSThuocTinh[7] = to_string(hopDong.soThangO);
    dSThuocTinh[8] = to_string(hopDong.ngaySinhVienVao.ngay);
    dSThuocTinh[9] = to_string(hopDong.ngaySinhVienVao.thang);
    dSThuocTinh[10] = to_string(hopDong.ngaySinhVienVao.nam);

    return dSThuocTinh;
}
void SinhVien::cThongTin(const Vector<string> &dSThuocTinhDV)
{
    hoVaTen = dSThuocTinhDV[0];
    ngaySinh = dSThuocTinhDV[1];
    ma = dSThuocTinhDV[2];
    sDT = dSThuocTinhDV[3];
    gioiTinh = 1;
    if (dSThuocTinhDV[4] == "0")
        gioiTinh = 0;
    hopDong.maPhong = dSThuocTinhDV[5];
    hopDong.tienTheChap = stoul(dSThuocTinhDV[6]);
    hopDong.soThangO = stoi(dSThuocTinhDV[7]);
    hopDong.ngaySinhVienVao.ngay = stoi(dSThuocTinhDV[8]);
    hopDong.ngaySinhVienVao.thang = stoi(dSThuocTinhDV[9]);
    hopDong.ngaySinhVienVao.nam = stoi(dSThuocTinhDV[10]);
}
SinhVien &SinhVien::operator=(const SinhVien &sinhvien)
{
    hoVaTen = sinhvien.hoVaTen;
    ngaySinh = sinhvien.lngaySinh();
    sDT = sinhvien.lSDT();
    gioiTinh = sinhvien.lGioiTinh();
    ma = sinhvien.lMa();
    hopDong = sinhvien.lHopDong();
    return *this;
}
const HopDongSinhVien &SinhVien::lHopDong() const { return hopDong; }
void SinhVien::cHopDong(const HopDongSinhVien &hopDong) { this->hopDong = hopDong; }
SinhVien::~SinhVien() {}
