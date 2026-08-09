#include "Heater.h"
#include <iostream>

using namespace std;

Heater::Heater(string n) : Device(n) {}

void Heater::toggle() {
    isOn = !isOn;
    cout << "[Máy sưởi] " << name << " hiện đã " << getStatusString() << endl;
}