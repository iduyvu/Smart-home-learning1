#include "Window.h"
#include <iostream>

using namespace std;

Window::Window(string n) : Device(n, 0.0), isLocked(false) {}

void Window::toggle() {
    setPowerState(!isOn);
    cout << "[Cửa sổ] " << name << " hiện đã " << getStatusString() << endl;
}

void Window::turnOff() {
    if (isOn) {
        setPowerState(false);
        cout << "[Cửa sổ] " << name << " hiện đã ĐÓNG." << endl;
    } else {
        cout << "[Cửa sổ] " << name << " đã ở trạng thái ĐÓNG." << endl;
    }
}

void Window::lock() {
    if (!isOn) { // Chỉ có thể khóa khi đóng (isOn == false)
        if (!isLocked) {
            isLocked = true;
            cout << "[Cửa sổ] " << name << " hiện ĐÃ KHÓA." << endl;
        } else {
            cout << "[Cửa sổ] " << name << " đã ở trạng thái ĐÃ KHÓA." << endl;
        }
    } else {
        cout << "[Cửa sổ] " << name << " đang MỞ, không thể khóa!" << endl;
    }
}

void Window::unlock() {
    if (isLocked) {
        isLocked = false;
        cout << "[Cửa sổ] " << name << " hiện ĐÃ MỞ KHÓA." << endl;
    } else {
        cout << "[Cửa sổ] " << name << " đã ở trạng thái ĐÃ MỞ KHÓA." << endl;
    }
}

void Window::unlockEmergency() {
    isLocked = false;
    setPowerState(true); // Báo cháy thì ép mở cửa sổ luôn
    cout << "[Cửa sổ] [BÁO CHÁY] " << name << " ĐÃ BỊ MỞ KHÓA KHẨN CẤP VÀ ÉP MỞ!" << endl;
}

string Window::getStatusString() const {
    if (isOn) return "MỞ";
    return isLocked ? "ĐÓNG VÀ ĐÃ KHÓA" : "ĐÓNG";
}