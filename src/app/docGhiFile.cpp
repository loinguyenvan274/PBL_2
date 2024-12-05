#include "docGhiFile.h"
#define byte win_byte_override 
#include <windows.h>
#undef byte
#include <commdlg.h>

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
std::string docGhiFile::layDuongDanTuWindows(const char *dangFileMatDinh)
{
    OPENFILENAMEW ofn; 
    WCHAR fileMatDinh[256];
    MultiByteToWideChar(CP_UTF8, 0, dangFileMatDinh, -1, fileMatDinh, 256); 
    WCHAR szFile[260] = {0};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile) / sizeof(WCHAR);            
    ofn.lpstrFilter = L"All Files\0*.*\0Text Files\0*.TXT\0"; 
    ofn.nFilterIndex = 1;
    ofn.lpstrDefExt = fileMatDinh;
    ofn.lpstrTitle = L"Lưu";
    ofn.Flags = OFN_OVERWRITEPROMPT;

    if (GetSaveFileNameW(&ofn))
    { 
        char pathTraVe[256];
        WideCharToMultiByte(CP_UTF8, 0, ofn.lpstrFile, -1, pathTraVe, 256, NULL, NULL); 
        std::cout << "File duoc luu: " << pathTraVe << std::endl;
        return std::string(pathTraVe);
    }
    else
    {
        std::cout << "Co loi xay ra" << std::endl;
        return "";
    }
}

docGhiFile::~docGhiFile() {}