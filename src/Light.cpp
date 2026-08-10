#include "Light.h"
#include <iostream>

using namespace std;

Light::Light(string n) : Device(n, 15.0) {} // Đèn 15W

void Light::toggle() {
    setPowerState(!isOn);
    cout << "[Đèn] " << name << " hiện đã " << getStatusString() << endl;
}

void Light::turnOff() {
    if (isOn) {
        setPowerState(false);
        cout << "[Đèn] " << name << " hiện đã TẮT." << endl;
    } else {
        cout << "[Đèn] " << name << " đã ở trạng thái TẮT." << endl;
    }
}