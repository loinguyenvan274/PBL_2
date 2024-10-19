#ifndef _SINHVIEN
#define _SINHVIEN
#include <string>
#include "Nguoi.h"
#include "QuanLy.h"
class SinhVien : public Nguoi
{
private:
    thoiGianNTN ngayBatDauO;
    string maPhong;
    double thoiGianO;

public:
    SinhVien(const string & = "", const string & = "", const thoiGianNTN & = {0, 0, 2000});
    void cNgayBatDauO(const thoiGianNTN &);
    void cMaPhong(const string &);
    void cThoiGianO(const int &);
    thoiGianNTN lNgayBatDauO();
    string lMaPhong();
    double lThoiGianO();
    void bieuDien();
    ~SinhVien();
};
#endif