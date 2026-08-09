#include "Cooler.h"
#include <iostream>

using namespace std;

Cooler::Cooler(string n) : Device(n) {}

void Cooler::toggle() {
    isOn = !isOn;
    cout << "[Máy lạnh] " << name << " hiện đã " << getStatusString() << endl;
}