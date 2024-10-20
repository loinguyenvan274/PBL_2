#ifndef _GIAODIENCHINH
#define _GIEODIENCHINH

#include "raylib.h"
#include "giaoDien.h"
#include "quanLyGiaoDien.h"
#include "hopChu.h"
#include "hop.h"
#include "bang.h"

class giaoDienChinh : public giaoDien
{
private:
    quanLyGiaoDien qLGiaoDien;
    Font font28;
    hopChu a1;
    hopChu a2;
    int soSinhVien;
    Bang *table;

public:
    giaoDienChinh(quanLyGiaoDien &qLGiaoDien) : qLGiaoDien(qLGiaoDien)
    {

        soSinhVien = 200;
        font28 = LoadFontEx("arial.ttf", 28, const_cast<int *>(vietnameseCodepoints), sizeof(vietnameseCodepoints) / sizeof(int));
        a1 = hopChu({5, 50, 500, 36}, "xin chào các bạn ở đây", BLUE, RED, WHITE);
        a2 = hopChu({600, 50, 400, 50}, "xin Chao moi nguoi", BLUE, BLUE, WHITE);
        table = new Bang({10, 200}, 8, soSinhVien + 1, {250, 36});
        table->cTieuDe(true);
        table->cDangHangCot(3, 0);

        (*table)(0, 0).cNoiDung("STT");
        (*table)(0, 1).cNoiDung("Họ và tên");
        (*table)(0, 2).cNoiDung("Ngày sinh");
        (*table)(0, 3).cNoiDung("MSV");
        (*table)(0, 4).cNoiDung("Ngày ở");
        (*table)(0, 5).cNoiDung("Số Tháng");
        (*table)(0, 6).cNoiDung("Mã phòng");
        (*table)(0, 7).cNoiDung("Xóa");

        table->cCot(0, 60);
        table->cCot(1, 280);
        table->cCot(2, 250);
        table->cCot(3, 150);
        table->cCot(4, 250);
        table->cCot(5, 145);
        table->cCot(6, 250);
        table->cCot(7, 60);
        for (int i = 1; i <= soSinhVien; i++)
        {
            (*table)(i, 0).cNoiDung(to_string(i));
        }
        for (int i = 0; i < 200; i++)
        {
            if (i % 2 == 0)
                table->cMauTheoHang(i, {184, 184, 255, 255});
            else
                table->cMauTheoHang(i, {255, 238, 221, 255});
        }
        table->cKieuChu(font28);
        table->cGioHanBD(table->lViTri().y, GetScreenHeight());

        a1.cKieuChu(font28);
        a2.cKieuChu(font28);

        a2.cCoChu(45);
        a1.cDoDayVien(2.0f);
    }
    void capNhatTT() override
    {
        a1.capNhatTT();
        table->capNhatTT();
    }
    void bieuDien() override
    {
        a1.bieuDien();
        a2.bieuDien();
        table->bieuDien();
    }
    ~giaoDienChinh()
    {
        UnloadFont(font28);
        delete table;
    }
};
#endif