#ifndef _SINHVIEN
#define _SINHVIEN
#include <string>
#include "Nguoi.h"
#include "Vector.h"
class SinhVien : public Nguoi
{
private:
    string ngayBatDauO;
    string thoiGianO;
    string maPhong;

public:
    SinhVien(const string & = "", const string & = "", const string & = "");
    void cNgayBatDauO(const string &);
    void cMaPhong(const string &);
    void cThoiGianO(const string &);
    bool laSinhVienHopLe();
    void cSinhVienHopLe(const bool &);

    string lNgayBatDauO() const;
    string lMaPhong() const;
    string lThoiGianO() const;
    void bieuDien() const;
    void cThongTin(const Vector<string> &);
    SinhVien &operator=(const SinhVien &);
    Vector<string> lThongTin() const;
    ~SinhVien();
};

#endif