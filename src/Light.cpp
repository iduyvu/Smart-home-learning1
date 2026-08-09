#include "Light.h"
#include <iostream>

using namespace std;

Light::Light(string n) : Device(n) {}

void Light::toggle() {
    isOn = !isOn;
    cout << "[Đèn] " << name << " hiện đã " << getStatusString() << endl;
}

void Light::turnOff() {
    if (isOn) {
        isOn = false;
        cout << "[Đèn] " << name << " hiện đã TẮT." << endl;
    } else {
        cout << "[Đèn] " << name << " đã ở trạng thái TẮT." << endl;
    }
}