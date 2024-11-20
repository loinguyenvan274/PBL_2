#include <hpdf.h>
#include <iostream>

int main()
{
    HPDF_Doc pdf = HPDF_New(NULL, NULL);
    if (!pdf)
    {
        std::cerr << "Error: cannot create PdfDoc object\n";
        return 1;
    }

    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, font, 24);
    HPDF_Page_TextOut(page, 50, 800, "Hello, libharu!");
    HPDF_Page_EndText(page);

    HPDF_SaveToFile(pdf, "example.pdf");

    HPDF_Free(pdf);
    return 0;
}
