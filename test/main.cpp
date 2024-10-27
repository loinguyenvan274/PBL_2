#include "raylib.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Gán hình ảnh với chiều rộng cố định");

    // Tải ảnh từ file
    Texture2D texture = LoadTexture("./test/close.png");

    // Đặt chiều rộng cố định cho ô
    float fixedWidth = 20;                                    // Chiều rộng mong muốn cho ô
    float aspectRatio = (float)texture.height / texture.width; // Tỷ lệ chiều cao / chiều rộng của ảnh

    // Tính chiều cao tự khớp với tỷ lệ
    float calculatedHeight = fixedWidth * aspectRatio;

    // Định nghĩa vùng đích
    Rectangle targetRect = {100, 100, fixedWidth, calculatedHeight}; // Ô với chiều rộng cố định và chiều cao tự khớp

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Vẽ ảnh vào ô
        DrawTexturePro(texture,
                       (Rectangle){0, 0, texture.width, texture.height}, // Kích thước nguồn (toàn bộ ảnh)
                       targetRect,                                       // Kích thước đích (ô với chiều rộng cố định)
                       (Vector2){0, 0}, 0.0f, WHITE);                    // Không dịch chuyển và xoay

        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();

    return 0;
}
