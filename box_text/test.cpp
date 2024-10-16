#include "hopNhap.cpp"

#include <raylib.h>
#include <string>
#include <iostream>
using namespace std;
int main()
{
    InitWindow(1480, 880, "làm quen");
    Font font = LoadFontEx("arial.ttf", 28, vietnameseCodepoints, sizeof(vietnameseCodepoints) / sizeof(int));
    SetWindowPosition(45, 45);

    hopNhap a1({5, 50, 500, 36}, "xin chào các bạn ở đây", BLUE, RED, WHITE);
    while (!WindowShouldClose())
    {

        a1.cDoDayVien(2.0f);
        a1.capNhatTT();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        a1.bieuDien();
        EndDrawing();
    }
    // UnloadDroppedFiles(a);
    UnloadFont(font);
    CloseWindow();
    return 0;
}