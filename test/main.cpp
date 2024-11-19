#include <iostream>
#include <vector>
#include <ctime>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;
int main()
{
    std::string sourceFile = "m.jpg";           // Tên file gốc
    std::string destinationFile = "l.png"; // Tên file mới

    try
    {
        fs::copy_file(sourceFile, destinationFile, fs::copy_options::overwrite_existing);
        std::cout << "File copied successfully to: " << destinationFile << std::endl;
    }
    catch (const fs::filesystem_error &e)
    {
        std::cerr << "Error copying file: " << e.what() << std::endl;
    }

    return 0;
}