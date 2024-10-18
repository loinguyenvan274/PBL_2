#include "nguoi.h"
#include "coBan.h"
class sinhVien : public nguoi
{
private:
    thoiGianNTN ngayBatDauO;
    string maPhong;
    double thoiGianO;

public:
    sinhVien(const string & = "", const string & = "", const thoiGianNTN & = {0,0,2000});
    void cNgayBatDauO(const thoiGianNTN &);
    void cMaPhong(const string &);
    void cThoiGianO(const int &);
    thoiGianNTN lNgayBatDauO();
    string lMaPhong();
    double lThoiGianO();
    void bieuDien();
    ~sinhVien();
};