#include "../include/raylib.h"

#include <windows.h> // Thư viện Windows API

int main()
{
    // Khởi tạo cửa sổ Raylib
    InitWindow(800, 600, "Transparent Window");
    SetTargetFPS(60);

    // Lấy handle của cửa sổ Raylib
    HWND hwnd = GetActiveWindow();
    if (!hwnd)
    {
        CloseWindow();
        return -1;
    }

    // Thiết lập cửa sổ trong suốt
    LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);
    SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED); // Thêm thuộc tính WS_EX_LAYERED

    // Đặt độ trong suốt (Alpha: 0 = hoàn toàn trong suốt, 255 = hoàn toàn không trong suốt)
    BYTE transparency = 200;          // Ví dụ: 200 là hơi trong
    COLORREF colorKey = RGB(0, 0, 0); // Không sử dụng Color Key, để nguyên alpha
    SetLayeredWindowAttributes(hwnd, colorKey, transparency, LWA_ALPHA);

    // Vòng lặp game
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // DrawText("Hello Transparent Window!", 190, 200, 20, DARKGRAY);

        EndDrawing();
    }

    // Kết thúc chương trình
    CloseWindow();
    return 0;
}
