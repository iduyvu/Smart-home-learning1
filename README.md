# 🏠 SmartHome C++ Project - Nâng Cao Tư Duy Lập Trình

## 📖 Giới Thiệu
Dự án **SmartHome** này được xây dựng với mục đích trở thành một không gian thực hành để học hỏi, rèn luyện và nâng cao kỹ năng tư duy lập trình (Logical Thinking & Problem Solving). 

Thông qua việc phát triển và mở rộng các tính năng bắt nguồn từ file `main.cpp`, dự án giúp củng cố kiến thức về cấu trúc dữ liệu, thuật toán, tư duy hệ thống và lập trình hướng đối tượng (OOP).

## 🎯 Mục Tiêu Học Tập & Rèn Luyện
Khi tham gia phát triển và đọc hiểu source code của dự án này, mục tiêu hướng tới là:
- **Tư duy Hướng đối tượng (OOP):** Áp dụng thực tế tính Đóng gói (Encapsulation), Kế thừa (Inheritance) và Đa hình (Polymorphism) qua việc thiết kế các bản thiết kế cho `Device`, `Light`, `door`, `camera`...
- **Quản lý Trạng thái (State Management):** Theo dõi, cập nhật và đồng bộ trạng thái của các thiết bị theo thời gian thực một cách chặt chẽ.
- **Tư duy Thiết kế Hệ thống (System Design):** Cách module hóa code để dễ bảo trì và mở rộng (Clean Code), thay vì nhồi nhét tất cả logic vào một file `main.cpp` duy nhất.
- **Xử lý Luồng sự kiện (Event-Driven):** Tư duy xây dựng logic tự động hóa (Ví dụ: Hệ thống tự nhận diện nhiệt độ > 30°C -> Tự động bật điều hòa).

## ⚙️ Các Tính Năng Chính (Đang xây dựng)
- [x] Quản lý danh sách các thiết bị thông minh trong nhà (Thêm, Xóa, Liệt kê).
- [x] Điều khiển bật/tắt, điều chỉnh thông số thiết bị thủ công qua giao diện Console.
- [x] Mô phỏng đọc dữ liệu từ các cảm biến (Nhiệt độ, Độ ẩm, Chuyển động).
- [x] Hệ thống vòng lặp sự kiện chính (Main Event Loop) lắng nghe tương tác của người dùng.

## 📂 Cấu trúc chương trình & Luồng chạy
Toàn bộ logic khởi tạo và luồng chạy chính được thiết lập tại `main.cpp`. Cấu trúc Execution Flow bao gồm:
1. **Khởi tạo hệ thống (Init):** Cài đặt các thông số mặc định và tạo đối tượng nhà thông minh (SmartHome Controller).
2. **Thiết lập thiết bị (Load Devices):** Đăng ký các thiết bị đầu cuối vào hệ thống.
3. **Vòng lặp chính (Main Menu):** In ra giao diện console, nhận lệnh từ bàn phím người dùng.
4. **Xử lý Logic & Cập nhật UI:** Gọi các phương thức tương ứng với lệnh và in ra trạng thái mới nhất của hệ thống.

## 🚀 Hướng Dẫn Chạy Dự Án

### Yêu cầu hệ thống
- Trình biên dịch C++ (GCC, Clang, hoặc MSVC). Cần hỗ trợ tối thiểu C++11.
- `make` (Để sử dụng Makefile)

### Cách biên dịch và chạy (Terminal/Command Prompt)

Dự án này sử dụng cấu trúc mã nguồn được phân chia thành các thư mục `src/` (chứa các file `.cpp`) và `include/` (chứa các file `.h`).

# Biên dịch thông qua Makefile
make

# Chạy chương trình
./smarthome     # Trên Linux/macOS
smarthome.exe   # Trên Windows

# Xóa các file đã biên dịch (Dọn dẹp)
make clean
