#include "Hub.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void Hub::addDevice(std::shared_ptr<Device> d) {
    devices.push_back(d);
}

void Hub::removeDevice(size_t index) {
    if (index < devices.size()) {
        cout << "[Trung tâm] Đã xóa thiết bị: " << devices[index]->getName() << endl;
        devices.erase(devices.begin() + index);
    }
}

void Hub::toggleAll() {
    cout << "\n--- 1. Chuyển đổi Đa hình Thông thường ---" << endl;
    for (auto& d : devices) {
        d->toggle();
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

void Hub::demonstrateOverload() {
    cout << "\n--- 2. Trình diễn Nạp chồng Toán tử (!Device) ---" << endl;
    if (devices.size() >= 2) {
        !(*devices[0]); // Using overloaded operator!
        this_thread::sleep_for(chrono::milliseconds(400));
        !(*devices[1]);
    }
}

void Hub::listDevices() const {
    cout << "\n--- Các Thiết Bị Đã Kết Nối ---" << endl;
    for (size_t i = 0; i < devices.size(); ++i) {
        cout << i + 1 << ". " << devices[i]->getName() << " [" << devices[i]->getStatusString() << "]" << endl;
    }
}

void Hub::listRemovableDevices() const {
    cout << "\n--- Các Thiết Bị Có Thể Xóa ---" << endl;
    int count = 1;
    for (size_t i = 0; i < devices.size(); ++i) {
        if (devices[i]->isRemovable()) {
            cout << count << ". " << devices[i]->getName() << " [" << devices[i]->getStatusString() << "]" << endl;
            count++;
        }
    }
    if (count == 1) {
        cout << "(Không có thiết bị nào có thể xóa)" << endl;
    }
}

size_t Hub::getDeviceCount() const {
    return devices.size();
}

std::shared_ptr<Device> Hub::getDevice(size_t index) {
    if (index < devices.size()) {
        return devices[index];
    }
    return nullptr;
}

std::shared_ptr<Device> Hub::getRemovableDevice(size_t removableIndex, size_t& actualIndex) {
    size_t count = 0;
    for (size_t i = 0; i < devices.size(); ++i) {
        if (devices[i]->isRemovable()) {
            if (count == removableIndex) {
                actualIndex = i;
                return devices[i];
            }
            count++;
        }
    }
    return nullptr;
}

void Hub::executeGoodNightMacro(std::shared_ptr<Thermostat> thermo, std::shared_ptr<SmartLock> frontDoor, std::shared_ptr<SecurityCamera> cam, const string& authKey) {
    cout << "\n---Đang thực thi Macro 'Chúc Ngủ Ngon' (5+ thiết bị) ---" << endl;

    cout << "Bước 1: Quản lý nguồn điện (Kích hoạt BYPASS An ninh)..." << endl;
    for (auto& d : devices) {
        // Nhận diện thiết bị an ninh
        if (dynamic_pointer_cast<SmartLock>(d) != nullptr || dynamic_pointer_cast<SecurityCamera>(d) != nullptr) {

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