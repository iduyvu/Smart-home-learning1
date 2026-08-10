#include "SmartLock.h"
#include <iostream>

using namespace std;

SmartLock::SmartLock(string n) : Device(n, 5.0), isLocked(true) { // Khóa 5W
    setPowerState(true);
}

void SmartLock::toggle() {
    setPowerState(!isOn);
    cout << "[Khóa thông minh] Nguồn của " << name << " hiện " << (isOn ? "BẬT" : "TẮT") << endl;
}

void SmartLock::turnOff() {
    if (isOn) {
        setPowerState(false);
        cout << "[Khóa thông minh] Đã tắt nguồn hệ thống " << name << ". (Chỉ có thể dùng chìa cơ)" << endl;
    } else {
        cout << "[Khóa thông minh] Nguồn " << name << " đã TẮT sẵn." << endl;
    }
}

void SmartLock::lock() {
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

void SmartLock::unlock() {
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

void SmartLock::unlockEmergency() {
    isLocked = false;
    cout << "[Khóa thông minh] [BÁO CHÁY] " << name << " ĐÃ BỊ MỞ KHÓA KHẨN CẤP!" << endl;
}

string SmartLock::getStatusString() const {
    if (!isOn) return "MẤT NGUỒN";
    return isLocked ? "ĐÃ KHÓA" : "ĐÃ MỞ KHÓA";
}