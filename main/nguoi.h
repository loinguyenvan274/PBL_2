#pragma once
#include "QuanLy.h"
#include <string>
using namespace std;
class Nguoi
{
protected:
    string hoVaTen;
    string ma;
    thoiGianNTN ngaySinh;
public:
    Nguoi(const string & = "", const string & = "", const thoiGianNTN & = {0, 0, 2000});
    void cDanhTinh(const string &, const string &, const thoiGianNTN &);
    void cHoVaTen(const string &);
    void cNgaySinh(const thoiGianNTN &);
    void cMa(const string &);
    string lHoVaTen();
    string lMa();
    thoiGianNTN lngaySinh();
    friend bool operator==(const Nguoi &, const Nguoi &);
    virtual ~Nguoi();
};
bool operator==(const Nguoi &, const Nguoi &);