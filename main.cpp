#include <fstream>
#include <string>
#include <sstream>

int main()
{
    std::ofstream pdf("table_example.pdf", std::ios::binary);

    // Header của PDF
    pdf << "%PDF-1.4\n";

    // Catalog và Page tree
    pdf << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
    pdf << "2 0 obj\n<< /Type /Pages /Count 1 /Kids [3 0 R] >>\nendobj\n";
    pdf << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 595 842] /Contents 4 0 R >>\nendobj\n";

    // Dữ liệu cho bảng
    const int rows = 3;
    const int cols = 3;
    const int cellWidth = 100;
    const int cellHeight = 50;
    int startX = 100;
    int startY = 700;

    // Nội dung PDF
    std::stringstream content;
    content << "q\n"; // Bắt đầu một graphic state mới

    // Vẽ bảng 3x3
    for (int i = 0; i <= rows; ++i)
    {
        int y = startY - i * cellHeight;
        content << startX << " " << y << " m "
                << startX + cols * cellWidth << " " << y << " l S\n"; // Vẽ dòng ngang
    }

    for (int j = 0; j <= cols; ++j)
    {
        int x = startX + j * cellWidth;
        content << x << " " << startY << " m "
                << x << " " << startY - rows * cellHeight << " l S\n"; // Vẽ dòng dọc
    }

    // Thêm văn bản vào các ô
    content << "BT /F1 12 Tf\n";
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            int x = startX + j * cellWidth + 10; // Căn chỉnh để vào giữa ô
            int y = startY - i * cellHeight - 30;
            content << x << " " << y << " Td (" << "R" << i + 1 << "C" << j + 1 << ") Tj\n";
        }
    }
    content << "ET\n";
    content << "Q\n"; // Kết thúc graphic state

    std::string contentStr = content.str();

    // Thêm nội dung và kết thúc stream
    pdf << "4 0 obj\n<< /Length " << contentStr.length() << " >>\nstream\n";
    pdf << contentStr;
    pdf << "endstream\nendobj\n";

    // Font (Helvetica)
    pdf << "5 0 obj\n<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\nendobj\n";

    // Cross-reference table và trailer
    int xrefPosition = pdf.tellp();
    pdf << "xref\n0 6\n0000000000 65535 f \n"
        << "0000000010 00000 n \n"
        << "0000000079 00000 n \n"
        << "0000000178 00000 n \n"
        << "0000000293 00000 n \n"
        << "0000000376 00000 n \n";

    pdf << "trailer\n<< /Size 6 /Root 1 0 R >>\nstartxref\n"
        << xrefPosition << "\n%%EOF";

    pdf.close();
    return 0;
}
