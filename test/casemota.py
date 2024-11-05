import random

# Danh sách từ vựng tiếng Việt mở rộng
tu_vung = [
    "hạnh phúc", "mặt trời", "bông hoa", "cuộc sống", "niềm vui", 
    "không gian", "trái tim", "những ngày", "giấc mơ", "nụ cười",
    "thời gian", "ngôi sao", "cánh đồng", "bầu trời", "cơn gió",
    "hòa bình", "tình yêu", "khi bình minh", "làn sóng", "sắc màu",
    "dòng sông", "hồ nước", "cây cối", "ngọn núi", "biển xanh",
    "nắng ấm", "mưa phùn", "sương sớm", "cảnh đẹp", "những kỷ niệm",
    "tình bạn", "mùa thu", "mùa xuân", "giấc mơ lớn", "bước chân",
    "hành trình", "khoảnh khắc", "sống trọn vẹn", "vui vẻ", "tươi mới",
    "hành động", "ước mơ", "dòng chảy", "kỳ diệu", "thành công",
    "tương lai", "cùng nhau", "niềm tin", "khát vọng", "tự do",
    "bình yên", "yêu thương", "cảm xúc", "sự nghiệp", "đam mê",
    "trái đất", "vùng đất", "cảm giác", "sự sống", "cám ơn",
    "cảm nhận", "cơ hội", "thử thách", "trải nghiệm", "tìm kiếm",
    "giá trị", "khám phá", "mơ ước", "điều kỳ diệu", "ngọn lửa"
]

# Hàm tạo một câu ngẫu nhiên
def tao_dong_ngau_nhien():
    so_tu = random.randint(2, 5)  # Số từ trong mỗi dòng
    return ' '.join(random.choices(tu_vung, k=so_tu))

# Tạo 40000 dòng văn bản
so_dong = 40000
danh_sach_dong = [tao_dong_ngau_nhien() for _ in range(so_dong)]

# Lưu vào file
with open('du_lieu_ngau_nhien.txt', 'w', encoding='utf-8') as f:
    for dong in danh_sach_dong:
        f.write(dong + '\n')

print(f"Tạo thành công {so_dong} dòng dữ liệu vào file 'du_lieu_ngau_nhien.txt'.")
