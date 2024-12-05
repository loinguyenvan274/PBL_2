#include <windows.h>
#include <imm.h>
#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

#pragma comment(lib, "Imm32.lib")

std::string wstring_to_utf8(const std::wstring &wstr)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

std::wstring utf8_to_wstring(const std::string &str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}

void CancelIMEComposition()
{
    HWND hwnd = GetForegroundWindow();
    HIMC hIMC = ImmGetContext(hwnd);

    if (hIMC)
    {
        ImmNotifyIME(hIMC, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
        ImmReleaseContext(hwnd, hIMC);
    }
}

std::wstring GetIMEComposition()
{
    HWND hwnd = GetForegroundWindow();
    HIMC hIMC = ImmGetContext(hwnd);

    if (hIMC)
    {
        DWORD dwSize = ImmGetCompositionStringW(hIMC, GCS_COMPSTR, nullptr, 0);
        if (dwSize > 0)
        {
            std::wstring buffer(dwSize / sizeof(wchar_t), L'\0');
            ImmGetCompositionStringW(hIMC, GCS_COMPSTR, &buffer[0], dwSize);
            return buffer;
        }
        ImmReleaseContext(hwnd, hIMC);
    }
    return L"";
}


