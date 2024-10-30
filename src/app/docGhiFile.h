#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include "Vector.h"

using namespace std;
class docGhiFile
{
    string duongDan;

private:
public:
    docGhiFile(const string &);
    const Vector<Vector<string>> &docData();
    void ghiData(const Vector<Vector<string>> &);
    ~docGhiFile();
};
