#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main()
{
    // Mở file dữ liệu
    std::ifstream file("data.txt");
    if (!file.is_open())
    {
        std::cerr << "Không thể mở file!" << std::endl;
        return 1;
    }

    std::map<int, int> digitCount; // Lưu trữ số lượng các số có số chữ số cụ thể

    int number;
    while (file >> number)
    {
        int numDigits = std::to_string(abs(number)).length(); // Đếm số chữ số của số tuyệt đối
        digitCount[numDigits]++;                              // Tăng số lượng cho số chữ số đó
    }

    // In kết quả: đếm số lượng các số có 1 chữ số, 2 chữ số, v.v.
    std::cout << "fjdkjfkdjf" << std::endl;
    for (const auto &entry : digitCount)
    {
        std::cout << "so co" << entry.first << " chu so: " << entry.second << std::endl;
    }

    file.close(); // Đóng file
    return 0;
}
