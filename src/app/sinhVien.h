#ifndef _SINHVIEN
#define _SINHVIEN
#include <string>
#include "Nguoi.h"
#include "Vector.h"

struct HopDongSinhVien
{
    NTN ngaySinhVienVao;
    string maPhong;
    // string loaiPhong;
    int soThangO;
    // unsigned long tienPhong;
    unsigned long tienTheChap;
    HopDongSinhVien();
};
class SinhVien : public Nguoi
{
private:
    HopDongSinhVien hopDong;

public:
    SinhVien(const string & = "", const string & = "", const string & = "");

    void cMaPhong(const string &);
    const HopDongSinhVien &lHopDong() const;
    void cHopDong(const HopDongSinhVien &);

    string lMaPhong() const;
    void bieuDien() const;
    void cThongTin(const Vector<string> &);
    SinhVien &operator=(const SinhVien &);
    Vector<string> lThongTin() const;
    ~SinhVien();
};

#endif