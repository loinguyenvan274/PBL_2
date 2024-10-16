#include <raylib.h>
#include <string>
#include <iostream>
using namespace std;
int main()
{
    InitWindow(1480, 880, "làm quen");
    Font font = LoadFontEx("arial.ttf", 28, vietnameseCodepoints, sizeof(vietnameseCodepoints) / sizeof(int));
    SetWindowPosition(45, 45);
    FilePathList a;
    string b = "helo";
    a.count = 0;
    while (!WindowShouldClose())
    {

        if (IsFileDropped())
        {
            a = LoadDroppedFiles();
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (a.count > 0)
            DrawTextEx(font, a.paths[0], (Vector2){100, 100}, 28, 1.0f, BLACK);
        else
            DrawTextEx(font, b.c_str(), (Vector2){100, 100}, 28, 1.0f, BLACK);
        EndDrawing();
    }
    UnloadDroppedFiles(a);
    UnloadFont(font);
    CloseWindow();
    return 0;
}