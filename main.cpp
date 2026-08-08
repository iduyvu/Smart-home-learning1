#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

// Forward declarations
class Heater;
class Cooler;

// --- Abstract Base Class ---
class Device {
protected:
    string name;
    bool isOn;
public:
    Device(string n) : name(n), isOn(false) {}
    virtual ~Device() {}

    // Pure virtual function enforcing polymorphism
    virtual void toggle() = 0;

    virtual void turnOff() {
        if (isOn) {
            isOn = false;
            cout << "[" << name << "] hiện đã TẮT." << endl;
        } else {
            cout << "[" << name << "] đã ở trạng thái TẮT." << endl;
        }
    }

    // Thêm hàm ép bật nguồn vào class Device
    virtual void turnOn() {
        if (!isOn) {
            isOn = true;
            cout << "[" << name << "] đã được BẬT NGUỒN trở lại." << endl;
        }
    }

    string getName() const { return name; }
    bool getStatus() const { return isOn; }
    virtual string getStatusString() const { return isOn ? "BẬT" : "TẮT"; }

    // Overload unary operator! to simulate malfunction or reboot
    virtual void operator!() {
        cout << "[!] CẢNH BÁO: Thiết bị '" << name << "' đang bị lỗi/khởi động lại!" << endl;
        isOn = false;
    }
};

// --- Derived Classes ---
class Light : public Device {
public:
    Light(string n) : Device(n) {}

    void toggle() override {
        isOn = !isOn;
        cout << "[Đèn] " << name << " hiện đã " << getStatusString() << endl;
    }

    void turnOff() override {
        if (isOn) {
            isOn = false;
            cout << "[Đèn] " << name << " hiện đã TẮT." << endl;
        } else {
            cout << "[Đèn] " << name << " đã ở trạng thái TẮT." << endl;
        }
    }
};

class SmartLock : public Device {
private:
    bool isLocked; // Thêm biến trạng thái khóa riêng biệt
public:
    // Khởi tạo khóa: Mặc định có điện (isOn = true) và Đang khóa (isLocked = true)
    SmartLock(string n) : Device(n), isLocked(true) {
        isOn = true; 
    }

    // Toggle bây giờ chỉ bật/tắt nguồn của khóa (ví dụ: hết pin, tắt hệ thống smart)
    void toggle() override {
        isOn = !isOn;
        cout << "[Khóa thông minh] Nguồn của " << name << " hiện " << (isOn ? "BẬT" : "TẮT") << endl;
    }

    void turnOff() override {
        if (isOn) {
            isOn = false;
            cout << "[Khóa thông minh] Đã tắt nguồn hệ thống " << name << ". (Chỉ có thể dùng chìa cơ)" << endl;
        } else {
            cout << "[Khóa thông minh] Nguồn " << name << " đã TẮT sẵn." << endl;
        }
    }

    // Hàm khóa/mở khóa cơ học
    void lock() {
        if (!isOn) {
            cout << "[Khóa thông minh] " << name << " đang TẮT NGUỒN, không thể khóa điện tử!" << endl;
            return;
        }
        if (!isLocked) {
            isLocked = true;
            cout << "[Khóa thông minh] " << name << " hiện ĐÃ KHÓA." << endl;
        } else {
            cout << "[Khóa thông minh] " << name << " đã ở trạng thái ĐÃ KHÓA." << endl;
        }
    }

    void unlock() {
        if (!isOn) {
            cout << "[Khóa thông minh] " << name << " đang TẮT NGUỒN, không thể mở khóa điện tử!" << endl;
            return;
        }
        if (isLocked) {
            isLocked = false;
            cout << "[Khóa thông minh] " << name << " hiện ĐÃ MỞ KHÓA." << endl;
        } else {
            cout << "[Khóa thông minh] " << name << " đã ở trạng thái ĐÃ MỞ KHÓA." << endl;
        }
    }

    string getStatusString() const override { 
        if (!isOn) return "MẤT NGUỒN";
        return isLocked ? "ĐÃ KHÓA" : "ĐÃ MỞ KHÓA"; 
    }
};

class SecurityCamera : public Device {
private:
    bool isArmed;
    string authKey;
public:
    SecurityCamera(string n, string key) : Device(n), isArmed(false), authKey(key) {}

    void toggle() override {
        isOn = !isOn;
        cout << "[Camera an ninh] Nguồn của " << name << " hiện đã " << getStatusString() << endl;
    }

    bool authenticate(const string& key) {
        if (key == authKey) {
            cout << "[Camera an ninh] Xác thực THÀNH CÔNG cho " << name << "." << endl;
            return true;
        } else {
            cout << "[Camera an ninh] LỖI: Xác thực THẤT BẠI cho " << name << "! Cố gắng truy cập trái phép." << endl;
            return false;
        }
    }

    void arm(const string& key) {
        // Fix: Chặn kích hoạt nếu camera đang sập nguồn
        if (!isOn) {
            cout << "[Camera an ninh] LỖI NGHIÊM TRỌNG: " << name << " đang TẮT NGUỒN, không thể kích hoạt bảo vệ!" << endl;
            return;
        }

        if (authenticate(key)) {
            isArmed = true;
            cout << "[Camera an ninh] " << name << " hiện ĐÃ KÍCH HOẠT." << endl;
        } else {
            cout << "[Camera an ninh] Từ chối thao tác: Không thể kích hoạt " << name << " do lỗi xác thực." << endl;
        }
    }
};

class Heater : public Device {
public:
    Heater(string n) : Device(n) {}
    void toggle() override {
        isOn = !isOn;
        cout << "[Máy sưởi] " << name << " hiện đã " << getStatusString() << endl;
    }
};

class Cooler : public Device {
public:
    Cooler(string n) : Device(n) {}
    void toggle() override {
        isOn = !isOn;
        cout << "[Máy lạnh] " << name << " hiện đã " << getStatusString() << endl;
    }
};

class Thermostat : public Device {
private:
    int temperature;
    Heater* linkedHeater;
    Cooler* linkedCooler;
public:
    Thermostat(string n, Heater* h = nullptr, Cooler* c = nullptr)
        : Device(n), temperature(22), linkedHeater(h), linkedCooler(c) {}

    void toggle() override {
        isOn = !isOn;
        cout << "[Bộ điều nhiệt] " << name << " hiện đã " << getStatusString() << endl;
    }

    void setTemperature(int temp) {
        temperature = temp;
        cout << "[Bộ điều nhiệt] Nhiệt độ mục tiêu của " << name << " được đặt thành " << temperature << "°C" << endl;
    }

    void triggerFeedbackLoop() {
        cout << "\n--- Bắt đầu Kịch bản A: Vòng lặp phản hồi môi trường ---" << endl;
        int currentTemp = 18;
        int targetTemp = 22;
        int iterations = 0;

        while (iterations < 6) {
            this_thread::sleep_for(chrono::milliseconds(800));
            if (currentTemp < targetTemp) {
                cout << "[Bộ điều nhiệt] Đang đọc: " << currentTemp << "°C (Quá lạnh!). Đang kích hoạt máy sưởi..." << endl;
                if (!linkedHeater->getStatus()) linkedHeater->toggle();
                if (linkedCooler->getStatus()) linkedCooler->toggle();

                currentTemp += 10; // Instantly heats up past target
                cout << "   -> [Môi trường] Máy sưởi làm nhiệt độ tăng vọt lên " << currentTemp << "°C!" << endl;
            } else {
                cout << "[Bộ điều nhiệt] Đang đọc: " << currentTemp << "°C (Quá nóng!). Đang kích hoạt máy lạnh..." << endl;
                if (!linkedCooler->getStatus()) linkedCooler->toggle();
                if (linkedHeater->getStatus()) linkedHeater->toggle();

                currentTemp -= 10; // Instantly cools down below target
                cout << "   -> [Môi trường] Máy lạnh làm nhiệt độ giảm xuống " << currentTemp << "°C!" << endl;
            }
            iterations++;
        }
        cout << "[Hệ thống] Cảnh báo: Phát hiện vòng lặp phản hồi vô hạn! Buộc chấm dứt hoạt động HVAC." << endl;
        if (linkedHeater->getStatus()) linkedHeater->toggle();
        if (linkedCooler->getStatus()) linkedCooler->toggle();
    }
};

// --- Hub Class ---
class Hub {
private:
    vector<Device*> devices;
public:
    void addDevice(Device* d) {
        devices.push_back(d);
    }

    void toggleAll() {
        cout << "\n--- 1. Chuyển đổi Đa hình Thông thường ---" << endl;
        for (Device* d : devices) {
            d->toggle();
            this_thread::sleep_for(chrono::milliseconds(300));
        }
    }

    void demonstrateOverload() {
        cout << "\n--- 2. Trình diễn Nạp chồng Toán tử (!Device) ---" << endl;
        if (devices.size() >= 2) {
            !(*devices[0]); // Using overloaded operator!
            this_thread::sleep_for(chrono::milliseconds(400));
            !(*devices[1]);
        }
    }

    void listDevices() const {
        cout << "\n--- Các Thiết Bị Đã Kết Nối ---" << endl;
        for (size_t i = 0; i < devices.size(); ++i) {
            cout << i + 1 << ". " << devices[i]->getName() << " [" << devices[i]->getStatusString() << "]" << endl;
        }
    }

    size_t getDeviceCount() const {
        return devices.size();
    }

    Device* getDevice(size_t index) {
        if (index < devices.size()) {
            return devices[index];
        }
        return nullptr;
    }

    void executeGoodNightMacro(Thermostat* thermo, SmartLock* frontDoor, SecurityCamera* cam, const string& authKey) {
        cout << "\n---Đang thực thi Macro 'Chúc Ngủ Ngon' (5+ thiết bị) ---" << endl;

        cout << "Bước 1: Quản lý nguồn điện (Kích hoạt BYPASS An ninh)..." << endl;
        for (Device* d : devices) {
            // Nhận diện thiết bị an ninh
            if (dynamic_cast<SmartLock*>(d) != nullptr || dynamic_cast<SecurityCamera*>(d) != nullptr) {
                
                // CƠ CHẾ BYPASS: Nếu phát hiện thiết bị an ninh đang TẮT/MẤT NGUỒN -> ÉP BẬT
                if (!d->getStatus()) {
                    cout << "[HỆ THỐNG BYPASS] Cảnh báo: '" << d->getName() << "' đang mất nguồn! Đang ép cấp nguồn khẩn cấp..." << endl;
                    d->turnOn(); 
                    this_thread::sleep_for(chrono::milliseconds(300));
                } else {
                    cout << "[Hệ thống] Bỏ qua ngắt nguồn thiết bị an ninh: " << d->getName() << endl;
                }
                continue; 
            }
            
            // Nếu không phải thiết bị an ninh, tiến hành tắt bình thường
            d->turnOff();
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        cout << "\nBước 2: Đặt Bộ điều nhiệt thành 26°C..." << endl;
        thermo->setTemperature(26);
        this_thread::sleep_for(chrono::milliseconds(500));

        cout << "Bước 3: Khóa Cửa Chính..." << endl;
        frontDoor->lock(); 
        this_thread::sleep_for(chrono::milliseconds(500));

        cout << "Bước 4: Kích hoạt Camera an ninh..." << endl;
        cam->arm(authKey); 
        this_thread::sleep_for(chrono::milliseconds(500));

        cout << "[Đã hoàn thành thực thi Macro 'Chúc Ngủ Ngon']" << endl;
    }
};

void demoFeedbackLoop(Thermostat* thermo) {
    thermo->triggerFeedbackLoop();
}

void demoUnauthorizedAccess(SecurityCamera* cam) {
    cout << "\n--- 5. Kịch bản B: Cố gắng truy cập trái phép ---" << endl;
    cout << "Đang thử kích hoạt Camera an ninh với khóa 'HACKER99'..." << endl;
    this_thread::sleep_for(chrono::milliseconds(800));
    cam->arm("HACKER99");
}

void showMenu() {
    cout << "\n=================================================" << endl;
    cout << "    Trung Tâm Nhà Thông Minh - Bảng Điều Khiển   " << endl;
    cout << "=================================================" << endl;
    cout << "1. Liệt kê tất cả thiết bị" << endl;
    cout << "2. Chuyển đổi một thiết bị cụ thể" << endl;
    cout << "3. Chuyển đổi tất cả thiết bị (Demo Đa Hình)" << endl;
    cout << "4. Mô phỏng lỗi thiết bị (Demo Nạp Chồng Toán Tử)" << endl;
    cout << "5. Thực thi Macro 'Chúc Ngủ Ngon'" << endl;
    cout << "6. Chạy Kịch bản A: Vòng lặp phản hồi" << endl;
    cout << "7. Chạy Kịch bản B: Truy cập trái phép" << endl;
    cout << "8. Thoát" << endl;
    cout << "=================================================" << endl;
    cout << "Nhập lựa chọn của bạn: ";
}

int main() {
    // Initialize Devices
    Light* livingLight = new Light("Đèn Phòng Khách");
    Light* kitchenLight = new Light("Đèn Nhà Bếp");
    SmartLock* frontDoor = new SmartLock("Cửa Chính");
    SecurityCamera* frontCam = new SecurityCamera("Camera Cửa Chính", "secure123");

    Heater* hvacHeater = new Heater("Máy sưởi HVAC");
    Cooler* hvacCooler = new Cooler("Máy lạnh HVAC");
    Thermostat* mainThermo = new Thermostat("Bộ điều nhiệt Chính", hvacHeater, hvacCooler);

    Hub myHub;
    myHub.addDevice(livingLight);
    myHub.addDevice(kitchenLight);
    myHub.addDevice(frontDoor);
    myHub.addDevice(frontCam);
    myHub.addDevice(hvacHeater);
    myHub.addDevice(hvacCooler);
    myHub.addDevice(mainThermo);

    bool running = true;
    while (running) {
        showMenu();
        string choiceStr;
        if (!(cin >> choiceStr)) {
            // Handle EOF (Ctrl+D) or stream errors gracefully
            cout << "\nĐang thoát Trung tâm Nhà thông minh..." << endl;
            break;
        }

        int choice = 0;
        try {
            choice = stoi(choiceStr);
        } catch (...) {
            cout << "Đầu vào không hợp lệ. Vui lòng nhập một số." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                myHub.listDevices();
                break;
            case 2: {
                myHub.listDevices();
                cout << "Nhập số thiết bị để chuyển đổi (1-" << myHub.getDeviceCount() << "): ";
                string devChoiceStr;
                cin >> devChoiceStr;
                try {
                    int devChoice = stoi(devChoiceStr);
                    Device* d = myHub.getDevice(devChoice - 1);
                    if (d) {
                        d->toggle();
                    } else {
                        cout << "Số thiết bị không hợp lệ." << endl;
                    }
                } catch (...) {
                    cout << "Đầu vào không hợp lệ." << endl;
                }
                break;
            }
            case 3:
                myHub.toggleAll();
                break;
            case 4:
                myHub.demonstrateOverload();
                break;
            case 5:
                myHub.executeGoodNightMacro(mainThermo, frontDoor, frontCam, "secure123");
                break;
            case 6:
                demoFeedbackLoop(mainThermo);
                break;
            case 7:
                demoUnauthorizedAccess(frontCam);
                break;
            case 8:
                cout << "Đang thoát Trung tâm Nhà thông minh. Tạm biệt!" << endl;
                running = false;
                break;
            default:
                cout << "Lựa chọn không hợp lệ. Vui lòng chọn từ 1-8." << endl;
        }
    }

    // Cleanup dynamically allocated devices
    delete livingLight;
    delete kitchenLight;
    delete frontDoor;
    delete frontCam;
    delete hvacHeater;
    delete hvacCooler;
    delete mainThermo;

    return 0;
}
