#ifndef _QUANLYGIAODIEN
#define _QUANLYGIAODIEN
#include "raylib.h"
#include "giaoDien.h"
#include "nganXep.h"


class quanLyGiaoDien
{
private:
    NganXep<giaoDien *> trangThai; // Sử dụng con trỏ giaoDien
public:
    void bieuDien()
    {
        trangThai.layDinh()->bieuDien(); // Truy cập con trỏ
    }
    void capNhatTT()
    {
        trangThai.layDinh()->capNhatTT(); // Truy cập con trỏ
    }
    void xoa()
    {
        trangThai.xoaDinh();
    }
    void them(giaoDien *dD) // Nhận con trỏ
    {
        trangThai.dayLen(dD);
    }
};
#endif
/*
#include <raylib.h>
#include <string>
#include <vector>

// Class Task đại diện cho một công việc
class Task
{
public:
    Task(std::string desc) : description(desc), completed(false) {}

    std::string GetDescription() const
    {
        return description;
    }

    bool IsCompleted() const
    {
        return completed;
    }

    void ToggleCompletion()
    {
        completed = !completed;
    }

private:
    std::string description;
    bool completed;
};

// Class Model để quản lý danh sách công việc
class Model
{
public:
    void AddTask(const std::string &description)
    {
        tasks.push_back(Task(description));
    }

    std::vector<Task> &GetTasks()
    {
        return tasks;
    }

private:
    std::vector<Task> tasks;
};

// Class View để quản lý giao diện
class View
{
public:
    View()
    {
        textColor = BLACK;
        buttonColor = LIGHTGRAY;
        completedColor = GREEN;
    }

    void DrawTasks(const std::vector<Task> &tasks)
    {
        for (size_t i = 0; i < tasks.size(); ++i)
        {
            const Task &task = tasks[i];
            Color color = task.IsCompleted() ? completedColor : textColor;
            DrawText(task.GetDescription().c_str(), 100, 100 + i * 30, 20, color);
        }
    }

    void DrawButtons()
    {
        // Vẽ nút "Thêm công việc"
        DrawRectangle(600, 100, 150, 50, buttonColor);
        DrawText("Thêm công việc", 610, 115, 20, BLACK);

        // Vẽ nút "Hoàn thành công việc"
        DrawRectangle(600, 160, 150, 50, buttonColor);
        DrawText("Hoàn thành công việc", 605, 175, 20, BLACK);
    }

private:
    Color textColor;
    Color buttonColor;
    Color completedColor;
};

// Class Controller để quản lý tương tác
class Controller
{
public:
    Controller(Model *model, View *view) : model(model), view(view) {}

    void OnAddTaskButtonClick()
    {
        model->AddTask("Công việc mới");
    }

    void OnCompleteTaskButtonClick()
    {
        auto &tasks = model->GetTasks();
        if (!tasks.empty())
        {
            tasks[0].ToggleCompletion();
        }
    }

    void Update()
    {
        // Kiểm tra sự kiện nhấn nút
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();

            // Kiểm tra nếu nhấn vào nút "Thêm công việc"
            if (mousePosition.x >= 600 && mousePosition.x <= 750 &&
                mousePosition.y >= 100 && mousePosition.y <= 150)
            {
                OnAddTaskButtonClick();
            }

            // Kiểm tra nếu nhấn vào nút "Hoàn thành công việc"
            if (mousePosition.x >= 600 && mousePosition.x <= 750 &&
                mousePosition.y >= 160 && mousePosition.y <= 210)
            {
                OnCompleteTaskButtonClick();
            }
        }
    }

    void Render()
    {
        view->DrawTasks(model->GetTasks());
        view->DrawButtons();
    }

private:
    Model *model;
    View *view;
};

int main()
{
    // Khởi tạo cửa sổ
    InitWindow(800, 600, "Mô hình MVC với Raylib - Quản lý công việc");

    Model model;
    View view;
    Controller controller(&model, &view);

    // Vòng lặp chính
    while (!WindowShouldClose())
    {
        // Cập nhật logic
        controller.Update();

        // Vẽ mọi thứ
        BeginDrawing();
        ClearBackground(RAYWHITE);

        controller.Render();

        EndDrawing();
    }

    // Giải phóng tài nguyên
    CloseWindow();
    return 0;
}
*/