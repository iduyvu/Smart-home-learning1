#include "GardenLight.h"
#include <iostream>

using namespace std;

GardenLight::GardenLight(string n) : Device(n, 30.0) {} // Đèn sân vườn 30W

void GardenLight::toggle() {
    setPowerState(!isOn);
    cout << "[Đèn sân vườn] " << name << " hiện đã " << getStatusString() << endl;
}

void GardenLight::turnOff() {
    if (isOn) {
        setPowerState(false);
        cout << "[Đèn sân vườn] " << name << " hiện đã TẮT." << endl;
    } else {
        cout << "[Đèn sân vườn] " << name << " đã ở trạng thái TẮT." << endl;
    }
}