#include "hopNhap.cpp"
#include "hop.cpp"

#include <raylib.h>
#include <string>
#include <iostream>
using namespace std;
int main()
{
    InitWindow(1480, 880, "làm quen");
    SetWindowPosition(45, 45);

    hopNhap a1({5, 50, 500, 36}, "xin chào các bạn ở đây", BLUE, RED, WHITE);
    hopNhap a2({600, 50, 400, 50}, "xin Chao moi nguoi", BLUE, BLUE, WHITE);
    a2.cCoChu(45);
    a1.cDoDayVien(2.0f);
    while (!WindowShouldClose())
    {
        a1.capNhatTT();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        a1.bieuDien();
        a2.bieuDien();
        EndDrawing();
    }
    // UnloadDroppedFiles(a);
    CloseWindow();
    return 0;
}