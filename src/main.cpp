#include <iostream>

#include "app/quanLyGiaoDien.h"

#include "app/giaoDienChinh.h"
// #include "giaoDien.h"
int main()
{

    InitWindow(1480, 880, "Quản Lý Sinh Viên Ký Túc Xá [ PBL2 Nguyễn Văn Lợi 102230026 - Nguyễn Thanh Hậu 102230013 ]");
    SetWindowPosition(45, 45);

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
    CloseWindow();
    return 0;
}