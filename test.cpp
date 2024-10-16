#include "raylib.h"
#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>
using namespace std;

#define MAX_INPUT_CHARS 32
#define ROWS 5
#define COLS 6

int main(void)
{
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
    // Khởi tạo cửa sổ
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Input Grid Example");

    // Tạo mảng để lưu trữ dữ liệu nhập vào
    char text[ROWS][COLS][MAX_INPUT_CHARS + 1] = { "\0" }; // Mảng để lưu trữ văn bản
    int currentRow = 0; // Dòng hiện tại
    int currentCol = 0; // Cột hiện tại
    int letterCount = 0; // Số ký tự đã nhập
    bool isEditing = false; // Kiểm tra xem có đang nhập hay không

    SetTargetFPS(60); // Thiết lập FPS

    while (!WindowShouldClose()) // Vòng lặp chính
    {
        // Xử lý sự kiện
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // Kiểm tra xem con trỏ chuột có nằm trong ô không
            for (int row = 0; row < ROWS; row++)
            {
                for (int col = 0; col < COLS; col++)
                {
                    Rectangle cell = { 100 + col * 100, 100 + row * 50, 100, 50 };
                    if (CheckCollisionPointRec(GetMousePosition(), cell))
                    {
                        currentRow = row;
                        currentCol = col;
                        isEditing = true; // Bắt đầu nhập liệu
                    }
                }
            }
        }

        // Nhập liệu từ bàn phím
        if (isEditing)
        {
            if (letterCount < MAX_INPUT_CHARS)
            {
                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    letterCount--; // Xóa ký tự cuối
                    if (letterCount < 0) letterCount = 0;
                    text[currentRow][currentCol][letterCount] = '\0'; // Kết thúc chuỗi
                }
                else
                {
                    for (int key = 32; key < 128; key++) // Kiểm tra ký tự nhập
                    {
                        if (IsKeyPressed(key))
                        {
                            text[currentRow][currentCol][letterCount] = (char)key;
                            letterCount++;
                            text[currentRow][currentCol][letterCount] = '\0'; // Kết thúc chuỗi
                            break;
                        }
                    }
                }
            }
            // Kiểm tra khi người dùng đã nhập xong ô hiện tại
            if (IsKeyPressed(KEY_ENTER))
            {
                letterCount = 0; // Đặt lại số ký tự
                isEditing = false; // Dừng nhập liệu
            }
        }

        // Vẽ mọi thứ
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Vẽ bảng
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                Rectangle cell = { 100 + col * 100, 100 + row * 50, 100, 50 };
                DrawRectangleRec(cell, LIGHTGRAY);
                DrawRectangleLinesEx(cell, 0, DARKGRAY); // Vẽ đường viền cho ô
                if(row%2 == 0)
                 DrawRectangleRec(cell, LIGHTGRAY);
                else
                 DrawRectangleRec(cell, BLUE);
                DrawText(text[row][col], 110 + col * 100, 110 + row * 50, 20, DARKGRAY); // Hiển thị văn bản trong ô
            }
        }

        // Thông báo người dùng đang nhập
        if (isEditing) 
        {
            DrawText("Editing...", 100, 70, 20, RED);
        }

        EndDrawing();
    }

    CloseWindow(); // Đóng cửa sổ
    return 0;
}
