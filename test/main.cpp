#include "../include/raylib.h"
#include <iostream>
using namespace std;
int main(void)
{
    // Khởi tạo cửa sổ
    InitWindow(800, 600, "Màng phủ màu với RGB");

    // Biến màu cho lớp phủ
    Color overlayColor = (Color){255, 0, 0, 128}; // Màu đỏ trong suốt

    // Biến để lưu giá trị RGB
    int r = 255, g = 0, b = 0, mm = 0; // Mặc định màu đỏ

    while (!WindowShouldClose())
    {
        // Kiểm tra phím để thay đổi giá trị RGB
        if (IsKeyPressed(KEY_R))
            r = (r + 2) % 256; // Tăng giá trị đỏ
        if (IsKeyPressed(KEY_G))
            g = (g + 2) % 256; // Tăng giá trị xanh
        if (IsKeyPressed(KEY_B))
            b = (b + 2) % 256; // Tăng giá trị
        if (IsKeyPressed(KEY_M))
            mm = (mm + 2) % 256; // Tăng giá trị lam
        if (IsKeyPressed(KEY_N))
            cout << r << " " << g << " " << b << " " << mm << endl;
        // Cập nhật màu lớp phủ với kiểu chuyển đổi
        overlayColor = (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, 128}; // Độ trong suốt 128

        // Bắt đầu vẽ
        BeginDrawing();
        ClearBackground(RAYWHITE); // Làm sạch nền

        // Vẽ nhiều hình chữ nhật với màu khác nhau
        for (int i = 0; i < 5; i++)
        {
            DrawRectangle(100, 100 + i * 80, 600, 70, (Color){0, 0, (unsigned char)(i * 50), mm});
        }

        // Vẽ lớp phủ màu
        DrawRectangle(100, 100, 600, 400, overlayColor);

        DrawText("Nhấn R, G, B để thay đổi màu lớp phủ", 100, 20, 20, DARKGRAY);

        EndDrawing();
    }

    // Giải phóng tài nguyên
    CloseWindow();

    return 0;
}
