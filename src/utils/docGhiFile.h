#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include "quanLy.h"

using namespace std;
class docGhiFile
{
    string duongDan;

private:
public:
    docGhiFile(const string &);
    const QuanLy<QuanLy<string>> &docData();
    void ghiData(const QuanLy<QuanLy<string>> &);
    ~docGhiFile();
};
