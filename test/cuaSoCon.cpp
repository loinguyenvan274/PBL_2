#include "cuaSoCon.h"

cuaSoCon::cuaSoCon(const int &chieuDai, const int &chieuCao, const int &soNut) : chieuDai(chieuDai), chieuCao(chieuCao)
{
    nutBam = QuanLy<hopChu>(soNut);
    viTrix = (GetScreenWidth() - chieuDai) / 2;
    viTriy = (GetScreenHeight() - chieuCao) / 2;
    table = nullptr;
}
Bang *cuaSoCon::lDCBang() { return table; }

hopChu &cuaSoCon::operator[](const int &diaChi)
{
    return nutBam[diaChi];
}
void cuaSoCon::capNhatTT()
{
    for (int i = 0; i < nutBam.lSoPhanTu(); i++)
        nutBam[i].capNhatTT();
    if (table != nullptr)
    {
        table->capNhatTT();
        table->vungHoatDong(0, 0, table->lSoHang(), table->lSoCot());
    }
    nutat.capNhatTT();
}
void cuaSoCon::bieuDien()
{
    
    if (table != nullptr)
        table->bieuDien(0, 0, table->lSoHang(), table->lSoCot());
    
}

cuaSoCon::~cuaSoCon()
{
    if (table != nullptr)
        delete table;
}