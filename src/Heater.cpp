#include "Heater.h"
#include <iostream>

using namespace std;

Heater::Heater(string n) : Device(n, 2000.0) {} // Máy sưởi 2000W

void Heater::toggle() {
    setPowerState(!isOn);
    cout << "[Máy sưởi] " << name << " hiện đã " << getStatusString() << endl;
}