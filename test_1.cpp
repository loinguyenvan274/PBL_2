// g++ lam_quen.cpp -o lamquen -L./library/lib -I./library/include -lraylib -lwinmm -lgdi32 -lopengl32 -lole32 -lcomdlg32
#include "raylib.h"
// #include <wchar.h>
#include "UTF8.h"
#include "tinyfiledialogs.h"
#include <cstddef> // Thêm dòng này
#include <iostream>

int main()
{ // Khởi tạo cửa sổ
    InitWindow(1480, 880, "Hiển thị tiếng Việt với Raylib");

    // Tải phông chữ với các ký tự tiếng Việt đã chỉ định
    Font font = LoadFontEx("arial.ttf", 28, vietnameseCodepoints, sizeof(vietnameseCodepoints) / sizeof(int));

    // Chuỗi tiếng Việt cần hiển thị (UTF-8)
    const char *lFilterPatterns[1] = {"*.txt"};
    char const *aFileName = tinyfd_openFileDialog("Open a File", "", 1, lFilterPatterns, NULL, 0);
    if (aFileName)
    {
        std::cout << aFileName;
    }
    // Vòng lặp chính
    while (!WindowShouldClose())
    {
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Vẽ văn bản với phông chữ đã nạp
        DrawTextEx(font, aFileName, (Vector2){100, 100}, 28, 1.0f, BLACK);

        EndDrawing();
    }

    // Giải phóng tài nguyên
    UnloadFont(font);
    CloseWindow();

    return 0;
}
