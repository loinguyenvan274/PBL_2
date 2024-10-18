#ifndef _NHANVIEN
#define _NHANVIEN
#include "nguoi.h"
#include "coBan.h"
class nhanVien : public nguoi
{
private:
    double thoiGianLam;
    double luongMoiGio;
    thoiGianNTN batDau;
    string moTaCongViec;

public:
    nhanVien(const string & = "", const string & = "", const string & = "");
    void cThoiGianLam(const int &);
    void cMoTaCongViec(const string &);
    void cthoiGianLam(const int &);
    thoiGianGPG lThoiGianLam() const;
    string lMoTaCongViec() const;
    int lthoiGianLam() const;
    ~nhanVien();
};
#endif
