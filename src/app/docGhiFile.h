#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include "Vector.h"

using namespace std;
class docGhiFile
{
private:
    string duongDan;

public:
    docGhiFile(const string &);
    const Vector<Vector<string>> &docData();
    void ghiData(const Vector<Vector<string>> &);
    static string layDuongDanTuWindows(const char *);
    ~docGhiFile();
};
