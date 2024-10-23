#include "docGhiFile.h"

docGhiFile::docGhiFile(const string &tenPath) : duongDan(tenPath) {}
const QuanLy<QuanLy<string>> &docGhiFile::docData()
{
    fstream docFile(duongDan, ios::in | ios::app);
    string line;
    QuanLy<QuanLy<string>> *dSDoiTuong = new QuanLy<QuanLy<string>>();

    while (getline(docFile, line))
    {
        QuanLy<string> doiTuong;
        std::stringstream ss(line);

        string token;
        while (getline(ss, token, ','))
        {
            doiTuong.them(token);
        }
        dSDoiTuong->them(doiTuong);
    }

    docFile.close();
    return *dSDoiTuong;
}
void docGhiFile::ghiData(const QuanLy<QuanLy<string>> &dSDoiTuong)
{
    fstream ghiFile(duongDan, ios::out | ios::trunc);

    size_t dong = dSDoiTuong.lSoPhanTu();
    for (size_t i = 0; i < dong; i++)
    {
        size_t cot = dSDoiTuong[i].lSoPhanTu();
        for (size_t j = 0; j < cot; j++)
        {
            ghiFile << dSDoiTuong[i][j];
            if (j < cot - 1)
                ghiFile << ",";
        }
        ghiFile << "\n";
    }
    ghiFile.close();
}
docGhiFile::~docGhiFile() {}