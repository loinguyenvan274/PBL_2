#include "docGhiFile.h"

docGhiFile::docGhiFile(const string &tenPath) : duongDan(tenPath) {}

const Vector<Vector<string>> &docGhiFile::docData()
{
    fstream docFile(duongDan, ios::in | ios::app);
    string line;
    Vector<Vector<string>> *dSDoiTuong = new Vector<Vector<string>>();

    while (getline(docFile, line))
    {
        Vector<string> doiTuong;
        std::stringstream ss(line);

        string token;
        while (getline(ss, token, '~'))
        {
            doiTuong.them(token);
        }
        doiTuong.xoa(doiTuong.lDCCuoi());
        dSDoiTuong->them(doiTuong);
    }

    docFile.close();
    return *dSDoiTuong;
}
void docGhiFile::ghiData(const Vector<Vector<string>> &dSDoiTuong)
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
                ghiFile << '~';
        }
        ghiFile << "~ ;\n";
    }
    ghiFile.close();
}
docGhiFile::~docGhiFile() {}