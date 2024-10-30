#pragma once
#include "Vector.h"
#include <string>
using namespace std;
class Nguoi
{
protected:
    string hoVaTen;
    string gioiTinh;
    string ma;
    string ngaySinh;

public:
    Nguoi(const string & = "", const string & = "", const string & = "");
    void cDanhTinh(const string &, const string &, const string &);
    void cHoVaTen(const string &);
    void cNgaySinh(const string &);
    void cMa(const string &);
    string lHoVaTen() const;
    string lMa() const;
    string lngaySinh() const;
    friend bool operator==(const Nguoi &, const Nguoi &);
    virtual ~Nguoi();
};
bool operator==(const Nguoi &, const Nguoi &);