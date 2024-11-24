#pragma once
#include "Vector.h"
#include <string>
using namespace std;
class Nguoi
{
protected:
    string hoVaTen;
    string ma;
    string sDT;
    bool gioiTinh;
    string ngaySinh;

public:
    Nguoi(const string & = "", const string & = "", const string & = "");
    void cDanhTinh(const string &, const string &, const string &);
    void cHoVaTen(const string &);
    void cNgaySinh(const string &);
    void cMa(const string &);
    void cSDT(const string &);
    void cGioiTinh(const bool &);
    string lSDT() const;
    bool lGioiTinh() const;
    string lHoVaTen() const;
    string lMa() const;
    string lngaySinh() const;
    friend bool operator==(const Nguoi &, const Nguoi &);
    virtual ~Nguoi();
};
bool operator==(const Nguoi &, const Nguoi &);