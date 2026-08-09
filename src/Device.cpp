#include "Device.h"

using namespace std;

Device::Device(string n) : name(n), isOn(false) {}
Device::~Device() {}

void Device::turnOff() {
    if (isOn) {
        isOn = false;
        cout << "[" << name << "] hiện đã TẮT." << endl;
    } else {
        cout << "[" << name << "] đã ở trạng thái TẮT." << endl;
    }
}

void Device::turnOn() {
    if (!isOn) {
        isOn = true;
        cout << "[" << name << "] đã được BẬT NGUỒN trở lại." << endl;
    }
}

string Device::getName() const { return name; }
bool Device::getStatus() const { return isOn; }
string Device::getStatusString() const { return isOn ? "BẬT" : "TẮT"; }

void Device::operator!() {
    cout << "[!] CẢNH BÁO: Thiết bị '" << name << "' đang bị lỗi/khởi động lại!" << endl;
    isOn = false;
}