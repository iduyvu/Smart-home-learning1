#include "SecurityCamera.h"
#include <iostream>

using namespace std;

SecurityCamera::SecurityCamera(string n, string key) : Device(n, 20.0), isArmed(false), authKey(key) {} // Camera 20W

void SecurityCamera::toggle() {
    setPowerState(!isOn);
    cout << "[Camera an ninh] Nguồn của " << name << " hiện đã " << getStatusString() << endl;
}

bool SecurityCamera::authenticate(const string& key) {
    if (key == authKey) {
        cout << "[Camera an ninh] Xác thực THÀNH CÔNG cho " << name << "." << endl;
        return true;
    } else {
        cout << "[Camera an ninh] LỖI: Xác thực THẤT BẠI cho " << name << "! Cố gắng truy cập trái phép." << endl;
        return false;
    }
}

void SecurityCamera::arm(const string& key) {
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