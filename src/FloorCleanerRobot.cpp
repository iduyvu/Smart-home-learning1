#include "FloorCleanerRobot.h"
#include <iostream>

using namespace std;

FloorCleanerRobot::FloorCleanerRobot(string n) : Device(n) {}

void FloorCleanerRobot::toggle() {
    isOn = !isOn;
    cout << "[Robot hút bụi] " << name << " hiện đã " << getStatusString() << endl;
}

void FloorCleanerRobot::turnOff() {
    if (isOn) {
        isOn = false;
        cout << "[Robot hút bụi] " << name << " hiện đã NGỪNG HOẠT ĐỘNG." << endl;
    } else {
        cout << "[Robot hút bụi] " << name << " đã ở trạng thái NGỪNG HOẠT ĐỘNG." << endl;
    }
}

string FloorCleanerRobot::getStatusString() const {
    return isOn ? "ĐANG HOẠT ĐỘNG" : "NGỪNG HOẠT ĐỘNG";
}