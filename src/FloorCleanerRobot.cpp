#include "FloorCleanerRobot.h"
#include <iostream>

using namespace std;

FloorCleanerRobot::FloorCleanerRobot(string n) : Device(n, 45.0) {} // Robot hút bụi 45W

void FloorCleanerRobot::toggle() {
    setPowerState(!isOn);
    cout << "[Robot hút bụi] " << name << " hiện đã " << getStatusString() << endl;
}

void FloorCleanerRobot::turnOff() {
    if (isOn) {
        setPowerState(false);
        cout << "[Robot hút bụi] " << name << " hiện đã NGỪNG HOẠT ĐỘNG." << endl;
    } else {
        cout << "[Robot hút bụi] " << name << " đã ở trạng thái NGỪNG HOẠT ĐỘNG." << endl;
    }
}

string FloorCleanerRobot::getStatusString() const {
    return isOn ? "ĐANG HOẠT ĐỘNG" : "NGỪNG HOẠT ĐỘNG";
}