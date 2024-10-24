#include <iostream>

#include "app/quanLyGiaoDien.h"

#include "app/giaoDienChinh.h"
// #include "giaoDien.h"

Font giaoDien::font28;
int main()
{
    InitWindow(1480, 880, "Quản Lý Sinh Viên Ký Túc Xá [ PBL2 Nguyễn Văn Lợi 102230026 - Nguyễn Thanh Hậu 102230013 ]");
    SetWindowPosition(45, 45);

    giaoDien::font28 = LoadFontEx("assets/roboto.ttf", 26, const_cast<int *>(vietnameseCodepoints), sizeof(vietnameseCodepoints) / sizeof(int));

    quanLyGiaoDien dD;
    giaoDienChinh *dDC = new giaoDienChinh(dD);
    dD.them(dDC);

    while (!WindowShouldClose())
    {
        dD.capNhatTT();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        dD.bieuDien();
        EndDrawing();
    }

    delete dDC;
    UnloadFont(giaoDien::font28);
    CloseWindow();
    return 0;
}