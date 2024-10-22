#include <string>
#include <iostream>
#include "quanLyGiaoDien.h"
#include "giaoDienChinh.h"
using namespace std;
int main()
{
    InitWindow(1480, 880, "làm quen");
    SetWindowPosition(45, 45);
    quanLyGiaoDien dD;

    dD.them(new giaoDienChinh(dD));

    while (!WindowShouldClose())
    {
        dD.capNhatTT();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        dD.bieuDien();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}