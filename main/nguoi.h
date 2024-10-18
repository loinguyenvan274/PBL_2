#pragma once
#include <string>
#include "coBan.h"
using namespace std;
class nguoi
{
protected:
    string hoVaTen;
    string ma;
    thoiGianNTN ngaySinh;

public:
    nguoi(const string & = "", const string & = "", const thoiGianNTN & = {0, 0, 2000});
    void cDanhTinh(const string &, const string &, const thoiGianNTN &);
    void cHoVaTen(const string &);
    void cNgaySinh(const thoiGianNTN &);
    void cMa(const string &);
    string lHoVaTen();
    string lMa();
    thoiGianNTN lngaySinh();
    bool operator==(const nguoi &);
    virtual ~nguoi();
};