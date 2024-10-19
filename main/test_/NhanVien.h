#ifndef _NHANVIEN
#define _NHANVIEN
#include "quanLy.h"
class nhanVien : public Nguoi
{
private:
    double thoiGianLam;
    double luongMoiGio;
    thoiGianNTN batDau;
    quanLy<NC> ngayCong;
    string moTaCongViec;

public:
    nhanVien(const string & = "", const string & = "", const thoiGianNTN & = {0, 0, 2000});
    void cThoiGianLam(const int &);
    void cMoTaCongViec(const string &);
    void cthoiGianLam(const int &);
    thoiGianGPG lThoiGianLam() const;
    string lMoTaCongViec() const;
    int lthoiGianLam() const;
    ~nhanVien();
};
#endif
