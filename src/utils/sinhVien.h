#ifndef _SINHVIEN
#define _SINHVIEN
#include <string>
#include "Nguoi.h"
#include "QuanLy.h"
class SinhVien : public Nguoi
{
private:
    string ngayBatDauO;
    string maPhong;
    string thoiGianO;

public:
    SinhVien(const string & = "", const string & = "", const string & = "");
    void cNgayBatDauO(const string &);
    void cMaPhong(const string &);
    void cThoiGianO(const string &);
    string lNgayBatDauO();
    string lMaPhong();
    string lThoiGianO();
    void bieuDien();
    void cThongTin(const QuanLy<string> &);
    QuanLy<string> lThongTin();
    ~SinhVien();
};
#endif