#include "Window.h"
#include <iostream>

using namespace std;

Window::Window(string n) : Device(n) {}

void Window::toggle() {
    isOn = !isOn;
    cout << "[Cửa sổ] " << name << " hiện đã " << getStatusString() << endl;
}

void Window::turnOff() {
    if (isOn) {
        isOn = false;
        cout << "[Cửa sổ] " << name << " hiện đã ĐÓNG." << endl;
    } else {
        cout << "[Cửa sổ] " << name << " đã ở trạng thái ĐÓNG." << endl;
    }
}

string Window::getStatusString() const {
    return isOn ? "MỞ" : "ĐÓNG";
}