#include "Device.h"
#include "SimulatedClock.h"

using namespace std;

Device::Device(string n, double wattage)
    : name(n), isOn(false), powerWattage(wattage), cumulativeActiveTime(0) {}

Device::~Device() {}

void Device::setPowerState(bool newState) {
    if (isOn == newState) return;

    if (newState) {
        // Ghi lại thời điểm bắt đầu bật
        turnOnTime = SimulatedClock::now();
    } else {
        // Cộng dồn thời gian chạy từ lúc bật đến hiện tại (giả lập)
        auto now = SimulatedClock::now();
        cumulativeActiveTime += chrono::duration_cast<chrono::minutes>(now - turnOnTime);
    }
    isOn = newState;
}

void Device::turnOff() {
    if (isOn) {
        setPowerState(false);
        cout << "[" << name << "] hiện đã TẮT." << endl;
    } else {
        cout << "[" << name << "] đã ở trạng thái TẮT." << endl;
    }
}

void Device::turnOn() {
    if (!isOn) {
        setPowerState(true);
        cout << "[" << name << "] đã được BẬT NGUỒN trở lại." << endl;
    }
}

string Device::getName() const { return name; }
bool Device::getStatus() const { return isOn; }
string Device::getStatusString() const { return isOn ? "BẬT" : "TẮT"; }

void Device::operator!() {
    cout << "[!] CẢNH BÁO: Thiết bị '" << name << "' đang bị lỗi/khởi động lại!" << endl;
    setPowerState(false);
}

long long Device::getActiveMinutes() const {
    long long totalMinutes = cumulativeActiveTime.count();
    if (isOn) {
        // Nếu đang bật, tính thêm khoảng thời gian từ lúc bật đến "hiện tại" của đồng hồ giả lập
        auto now = SimulatedClock::now();
        totalMinutes += chrono::duration_cast<chrono::minutes>(now - turnOnTime).count();
    }
    return totalMinutes;
}

long long Device::getContinuousActiveMinutes() const {
    if (!isOn) return 0;
    auto now = SimulatedClock::now();
    return chrono::duration_cast<chrono::minutes>(now - turnOnTime).count();
}

double Device::getConsumedKWh() const {
    // KWh = Watt * hours / 1000
    double hours = getActiveMinutes() / 60.0;
    return (powerWattage * hours) / 1000.0;
}