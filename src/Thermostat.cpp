#include "Thermostat.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

Thermostat::Thermostat(string n, std::shared_ptr<Heater> h, std::shared_ptr<Cooler> c)
    : Device(n, 10.0), temperature(22), linkedHeater(h), linkedCooler(c) {} // Bộ điều nhiệt 10W

void Thermostat::toggle() {
    setPowerState(!isOn);
    cout << "[Bộ điều nhiệt] " << name << " hiện đã " << getStatusString() << endl;
}

void Thermostat::setTemperature(int temp) {
    temperature = temp;
    cout << "[Bộ điều nhiệt] Nhiệt độ mục tiêu của " << name << " được đặt thành " << temperature << "°C" << endl;
}

void Thermostat::triggerFeedbackLoop() {
    cout << "\n--- Bắt đầu Kịch bản A: Vòng lặp phản hồi môi trường ---" << endl;
    int currentTemp = 18;
    int targetTemp = 22;
    int iterations = 0;

    while (iterations < 6) {
        this_thread::sleep_for(chrono::milliseconds(800));
        if (currentTemp < targetTemp) {
            cout << "[Bộ điều nhiệt] Đang đọc: " << currentTemp << "°C (Quá lạnh!). Đang kích hoạt máy sưởi..." << endl;
            if (linkedHeater && !linkedHeater->getStatus()) linkedHeater->toggle();
            if (linkedCooler && linkedCooler->getStatus()) linkedCooler->toggle();

            currentTemp += 10; // Instantly heats up past target
            cout << "   -> [Môi trường] Máy sưởi làm nhiệt độ tăng vọt lên " << currentTemp << "°C!" << endl;
        } else {
            cout << "[Bộ điều nhiệt] Đang đọc: " << currentTemp << "°C (Quá nóng!). Đang kích hoạt máy lạnh..." << endl;
            if (linkedCooler && !linkedCooler->getStatus()) linkedCooler->toggle();
            if (linkedHeater && linkedHeater->getStatus()) linkedHeater->toggle();

            currentTemp -= 10; // Instantly cools down below target
            cout << "   -> [Môi trường] Máy lạnh làm nhiệt độ giảm xuống " << currentTemp << "°C!" << endl;
        }
        iterations++;
    }
    cout << "[Hệ thống] Cảnh báo: Phát hiện vòng lặp phản hồi vô hạn! Buộc chấm dứt hoạt động HVAC." << endl;
    if (linkedHeater && linkedHeater->getStatus()) linkedHeater->toggle();
    if (linkedCooler && linkedCooler->getStatus()) linkedCooler->toggle();
}