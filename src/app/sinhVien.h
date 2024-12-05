#ifndef _SINHVIEN
#define _SINHVIEN
#include <string>
#include "Nguoi.h"
#include "Vector.h"

struct HopDongThue
{
    NTN ngaySinhVienVao;
    string maPhong;
    // string loaiPhong;
    int soThangO;
    // unsigned long tienPhong;
    unsigned long tienTheChap;
    HopDongThue();
};
class SinhVien : public Nguoi
{
private:
    HopDongThue hopDong;

public:
    SinhVien(const string & = "", const string & = "", const string & = "");

    void cMaPhong(const string &);
    const HopDongThue &lHopDong() const;
    void cHopDong(const HopDongThue &);

    string lMaPhong() const;
    void bieuDien() const;
    void cThongTin(const Vector<string> &);
    SinhVien &operator=(const SinhVien &);
    Vector<string> lThongTin() const;
    ~SinhVien();
};

#endif