#include "Cooler.h"
#include <iostream>

using namespace std;

Cooler::Cooler(string n) : Device(n, 1500.0) {} // Máy lạnh 1500W

void Cooler::toggle() {
    setPowerState(!isOn);
    cout << "[Máy lạnh] " << name << " hiện đã " << getStatusString() << endl;
}