import random

bodem = 0
# Hàm sinh mã ngẫu nhiên từ A00000 đến A04999
def generate_random_room_code():
    random_num = random.randint(0, 9999)  # Sinh số ngẫu nhiên từ 0 đến 4999
    return f"A{random_num:04d}"  # Định dạng với 5 chữ số

# Hàm sinh tên ngẫu nhiên
def generate_random_name():
    first_names = ["Nguyen", "Tran", "Le", "Pham", "Hoang", "Vu", "Ngo", "Dang", "Bui", "Do", "Mai", "Phan", "Ngo"]
    last_names = ["Van Loi", "Minh Tuan", "Thi Hoa", "Van An", "Thi Lan", 
                  "Minh Hai", "Thi Bich", "Van Cuong", "Minh Chau", "Thi Kim", 
                  "Van Thanh", "Minh Quang", "Thi Tam", "Van Hung"]

    first_name = random.choice(first_names)
    last_name = random.choice(last_names)
    return f"{first_name} {last_name}"

# Hàm tạo dữ liệu
def generate_data(num_lines):
    global bodem
    data = []
    student_ids = set()  # Tập hợp để theo dõi mã sinh viên đã tạo

    while len(data) < num_lines:
        name = generate_random_name()
        dob = "07/09/2005"  # Ngày sinh (có thể thay đổi nếu cần)
        
        # Tạo mã sinh viên duy nhất
        
        student_id = f"102{bodem:06d}"  # Mã sinh viên
        if student_id not in student_ids:  # Kiểm tra mã đã tồn tại chưa
            student_ids.add(student_id)  # Thêm vào tập hợp
                
        
        phone_number = f"03266190{random.randint(0, 9)}"  # Số điện thoại
        gender = random.choice(["Nam", "Nữ"])  # Giới tính ngẫu nhiên
        room_code = generate_random_room_code()  # Mã phòng ngẫu nhiên

        # Thêm dữ liệu vào danh sách
        data.append(f"{name}~{dob}~{student_id}~{phone_number}~{gender}~{room_code}~;")
        bodem += 1
    return data

# Ghi dữ liệu vào tệp
def write_data_to_file(filename, data):
    with open(filename, 'w', encoding='utf-8') as file:
        for line in data:
            file.write(line + "\n")

if __name__ == "__main__":
    num_lines = 100000  # Số dòng dữ liệu cần tạo
    data = generate_data(num_lines)
    write_data_to_file("data/sinhVien.csv", data)
    print("Tạo dữ liệu thành công vào tệp data.txt!")
