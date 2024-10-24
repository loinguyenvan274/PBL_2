#include "quanLy.h"
#include "Phong.h"
#include "docGhiFile.h"
int main()
{
    docGhiFile doc("phong.csv");
    QuanLy<QuanLy<string>> docdt = doc.docData();
    QuanLy<Phong> ktx(docdt.lSoPhanTu());
    for (int i = 0; i < docdt.lSoPhanTu(); i++)
    {
        ktx[i].cThongTin(docdt[i]);
    }

    // ktx.them(Phong("A334", 8, "Phong Rat Chi La Ban"));
    // ktx.them(Phong("A00", 2, "Phong Rat Chi La Ban"));
    // ktx.them(Phong("BB4", 3, "Phong Rat Chi La Ban"));

    // QuanLy<QuanLy<string>> gd;
    for (int i = 0; i < ktx.lSoPhanTu(); i++)
    {
        ktx[i].hienThiThongTin();
        // gd.them(ktx[i].lThongTin());
    }

    // doc.ghiData(gd);
    return 0;
}