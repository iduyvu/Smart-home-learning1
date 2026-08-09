#include "GardenLight.h"
#include <iostream>

using namespace std;

GardenLight::GardenLight(string n) : Device(n) {}

void GardenLight::toggle() {
    isOn = !isOn;
    cout << "[Đèn sân vườn] " << name << " hiện đã " << getStatusString() << endl;
}

void GardenLight::turnOff() {
    if (isOn) {
        isOn = false;
        cout << "[Đèn sân vườn] " << name << " hiện đã TẮT." << endl;
    } else {
        cout << "[Đèn sân vườn] " << name << " đã ở trạng thái TẮT." << endl;
    }
}