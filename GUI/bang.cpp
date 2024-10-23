#include "Bang.h"
Bang::Bang(const Vector2 &viTriDV, const int &soCot, const int &soHang, const Vector2 &kichCoDV) : viTri(viTriDV), soHang(soHang), soCot(soCot), tieuDe(false)
{
    chanTren = viTri.y;
    chanDuoi = GetScreenHeight();
    chanTRai = viTri.x;
    chanPhai = viTri.x + kichCoDV.x * soCot;

    cachHang = 0;
    cachCot = 0;
    hop = new hopChu *[soHang];
    for (int i = 0; i < soHang; i++)
    {
        hop[i] = new hopChu[soCot];
    }
    for (int i = 0; i < soHang; i++)
    {
        for (int j = 0; j < soCot; j++)
        {
            hop[i][j].cVitri(viTri.x + kichCoDV.x * j, viTri.y + kichCoDV.y * i);
            hop[i][j].cKichCo(kichCoDV.x, kichCoDV.y);
            hop[i][j].cDoDayVien(2.0f);
        }
    }
}
void Bang::cKieuChu(const Font &fontDV, const int &coChu)
{
    for (int i = 0; i < soHang; i++)
    {
        for (int j = 0; j < soCot; j++)
        {
            hop[i][j].cKieuChu(fontDV);
            hop[i][j].cCoChu(coChu);
        }
    }
}
void Bang::cTieuDe(const bool &tieuDeDV) { tieuDe = tieuDeDV; }
Bang::~Bang()
{

    for (int i = 0; i < soHang; i++)
    {
        delete[] hop[i];
    }
    delete[] hop;
}
void Bang::cViTri()
{
    // Xử lý vị trí ô dựa trên độ dài và độ rộng của các hàng, cột
}

void Bang::cCot(const int &cot, const double &cDai)
{
    double doDai = cDai - hop[0][cot].layKichCo().x;
    chanPhai += doDai;
    for (int i = 0; i < soHang; i++)
    {
        hop[i][cot].cKichCo(cDai, hop[i][cot].layKichCo().y);
        for (int j = cot + 1; j < soCot; j++)
        {
            hop[i][j].cVitri(hop[i][j].layViTri().x + doDai, hop[i][j].layViTri().y);
        }
    }
}

// void Bang::cHang(const int &hang, const double &rong)
// {
//     if (hang >= 0 && hang < soHang)
//         doDaiMO[hang] = rong;
// }

void Bang::cMauTheoO(const OXY &viTri, const Color &mau)
{
    // Thay đổi màu sắc của một ô
}

void Bang::cMauTheoCot(const int &cot, const Color &mau)
{
    for (int i = 0; i < soHang; ++i)
    {
        hop[i][cot].cMauNen(mau); // Gán màu cho ô trong cột
    }
}

void Bang::cMauTheoHang(const int &hang, const Color &mau)
{
    for (int i = 0; i < soCot; ++i)
    {
        hop[hang][i].cMauNen(mau); // Gán màu cho ô trong hàng
    }
}

hopChu &Bang::operator()(const int &hang, const int &cot)
{
    return hop[hang][cot]; // Truy xuất ô qua chỉ số hàng và cột
}
void Bang::cGioHanBD(const int &chanTren, const int &chanDuoi)
{
    this->chanTren = chanTren;
    this->chanDuoi = chanDuoi;
}
void Bang::bieuDien() const
{
    for (int i = 0; i < soHang; i++)
    {
        if (hop[i][0].layViTri().y >= chanTren && hop[i][0].layViTri().y <= chanDuoi)
        {
            for (int j = 0; j < soCot; j++)
            {
                hop[i][j].bieuDien();
            }
        }
    }
    if (tieuDe)
        for (int j = 0; j < soCot; j++)
            hop[0][j].bieuDien();
}
void Bang::capNhatTT() const
{
    if (GetMouseX() > chanTRai && GetMouseX() < chanPhai && GetMouseY() > chanTren && GetMouseY() < chanDuoi)
    {
        double gTCuon = GetMouseWheelMove();
        gTCuon = double(long(gTCuon * 100000000.0) / 100000000.0); // làm tròn số tránh lỗi công 2 số thập phân

        if (gTCuon > 0 && hop[1][0].layViTri().y > chanTren + hop[0][0].layKichCo().y + cachHang)
            gTCuon = 0;

        for (int i = 0 + int(tieuDe); i < soHang; i++)
            for (int j = 0; j < soCot; j++)
            {

                hop[i][j].cVitri(hop[i][j].layViTri().x, hop[i][j].layViTri().y + gTCuon * 8);
            }
    }
    for (int i = 0 + int(tieuDe); i < soHang; i++)
        for (int j = 0; j < soCot; j++)
        {
            hop[i][j].capNhatTT();
        }
}
void Bang::cDangHangCot(const int &dangHang, const int &dangCot)
{
    chanPhai += (dangCot - cachCot) * (soCot - 1);
    cachHang = dangHang;
    cachCot = dangCot;
    for (int i = 0; i < soHang; i++)
    {
        for (int j = 0; j < soCot; j++)
        {
            hop[i][j].cVitri(viTri.x + (hop[i][j].layKichCo().x + cachCot) * j, viTri.y + (hop[i][j].layKichCo().y + cachHang) * i);
        }
    }
}
const Vector2 Bang::lViTri() const { return viTri; }