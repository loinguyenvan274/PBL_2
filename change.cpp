#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string a;
    bool first = true;

    while (true)
    {
        cin >> a;
        if (a == "1")
            break;

        try
        {
            // Kiểm tra xem chuỗi bắt đầu bằng "0x" hay không để xử lý số hex
            int value;
            if (a.substr(0, 2) == "0x" || a.substr(0, 2) == "0X")
            {
                value = stoi(a, nullptr, 16); // Chuyển đổi chuỗi hex
            }
            else
            {
                value = stoi(a); // Chuyển đổi chuỗi thập phân
            }

            if (value > 2047)
            {
                if (!first)
                {
                    cout << ",";
                }
                cout << a;
                first = false;
            }
        }
        catch (invalid_argument &e)
        {
            // Nếu không thể chuyển đổi, bỏ qua
            continue;
        }
        catch (out_of_range &e)
        {
            // Nếu giá trị vượt quá phạm vi, bỏ qua
            continue;
        }
    }

    cout << endl;
    return 0;
}

// #include <iostream>
// #include <string>
// #include <sstream>
// #include <iomanip>
// using namespace std;
// std::string convertUnicode(const std::string &unicodeStr)
// {
//     // Kiểm tra xem chuỗi có bắt đầu bằng "U+" hay không
//     if (unicodeStr.substr(0, 2) != "U+")
//     {
//         return "0";
//     }

//     // Lấy phần mã hex sau "U+"
//     std::string hexStr = unicodeStr.substr(2);

//     // Chuyển đổi chuỗi hex sang số nguyên
//     int codepoint;
//     std::stringstream ss;
//     ss << std::hex << hexStr; // Chuyển đổi từ chuỗi hex
//     ss >> codepoint;

//     // Định dạng lại thành chuỗi "0x" và mã hex
//     std::ostringstream oss;
//     oss << "0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << codepoint; // Đảm bảo có 4 chữ số

//     return oss.str();
// }

// int main()
// {
//     ios_base::sync_with_stdio(NULL);
//     cin.tie(NULL);
//     cout.tie(NULL);

//     std::string unicodeStr = "U+00C1"; // Ví dụ đầu vàow
//     while (unicodeStr != "1")
//     {
//         std::cin >> unicodeStr;
//         std::string hexStr = convertUnicode(unicodeStr);
//         if (hexStr != "0")
//             std::cout << hexStr << " ";
//     }
//     return 0;
// }
// #include <stdio.h>

// int main()
// {
//     wchar_t characters[] = L"̃ ́ ̣ ̈́ ΅ ῎ ῞ a A à À ả Ả ã Ã á Á ạ Ạ ǻ Ǻ ǽ Ǽ ă Ă ằ Ằ ẳ Ẳ ẵ Ẵ ắ Ắ ặ Ặ ą̆ Ą̆ ḁ̆ Ḁ̆ â Â ầ Ầ ẩ Ẩ ẫ Ẫ ấ Ấ ậ Ậ ą̂ Ą̂ ḁ̂ Ḁ̂ b B ḅ Ḅ c C ć Ć ḉ Ḉ d D ḍ Ḍ đ Đ e E è È ẻ Ẻ ẽ Ẽ é É ẹ Ẹ ḗ Ḗ ê Ê ề Ề ể Ể ễ Ễ ế Ế ệ Ệ ȩ̂ Ȩ̂ ę̂ Ę̂ ḙ̂ Ḙ̂ ḛ̂ Ḛ̂ f F g G ǵ Ǵ h H ḥ Ḥ i I ì Ì ỉ Ỉ ĩ Ĩ í Í ị Ị ḯ Ḯ j J k K ḱ Ḱ ḳ Ḳ l L ĺ Ĺ ḷ Ḷ ḹ Ḹ m M ḿ Ḿ ṃ Ṃ n N ñ Ñ ń Ń ṇ Ṇ o O ò Ò ỏ Ỏ õ Õ ṍ Ṍ ṏ Ṏ ȭ Ȭ ó Ó ọ Ọ ǿ Ǿ ṓ Ṓ ô Ô ồ Ồ ổ Ổ ỗ Ỗ ố Ố ộ Ộ ǫ̂ Ǫ̂ ơ̂ Ơ̂ ợ̂ Ợ̂ ơ Ơ ờ Ờ ở Ở ỡ Ỡ ớ Ớ ợ Ợ ǫ̛ Ǫ̛ p P ṕ Ṕ q Q r R ŕ Ŕ ṛ Ṛ ṝ Ṝ s S ś Ś ṥ Ṥ ṣ Ṣ ṩ Ṩ t T ṭ Ṭ u U ù Ù ủ Ủ ũ Ũ ṹ Ṹ ú Ú ụ Ụ ǘ Ǘ ư Ư ừ Ừ ử Ử ữ Ữ ứ Ứ ự Ự ų̛ Ų̛ v V ṽ Ṽ ṿ Ṿ w W ẃ Ẃ ẉ Ẉ x X y Y ỳ Ỳ ỷ Ỷ ỹ Ỹ ý Ý ỵ Ỵ z Z ź Ź ẓ Ẓ ἄ Ἄ ᾄ ᾌ ἅ Ἅ ᾅ ᾍ ά Ά ᾴ ἔ Ἔ ἕ Ἕ έ Έ ἤ Ἤ ᾔ ᾜ ἥ Ἥ ᾕ ᾝ ή Ή ῄ ἴ Ἴ ἵ Ἵ ί Ί ΐ ὄ Ὄ ὅ Ὅ ό Ό ὔ ὕ Ὕ ύ Ύ ϓ ΰ ὤ Ὤ ᾤ ᾬ ὥ Ὥ ᾥ ᾭ ώ Ώ ῴ ѓ Ѓ ќ Ќ";

//     wprintf(L"Hex codes:\n");
//     for (int i = 0; characters[i] != L'\0'; i++)
//     {
//         wprintf(L"0x%04X ", characters[i]);
//     }
//     wprintf(L"\n");

//     return 0;
// }
