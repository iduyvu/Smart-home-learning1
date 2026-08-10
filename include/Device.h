#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <string>
#include <chrono>

class Device {
protected:
    std::string name;
    bool isOn;

    // Thuộc tính năng lượng và thời gian
    double powerWattage;
    std::chrono::system_clock::time_point turnOnTime;
    std::chrono::minutes cumulativeActiveTime;

    // Hàm tiện ích để cập nhật trạng thái và tính toán thời gian chạy một cách thống nhất
    void setPowerState(bool newState);

public:
    Device(std::string n, double wattage = 0.0);
    virtual ~Device();

    // Pure virtual function enforcing polymorphism
    virtual void toggle() = 0;

    virtual void turnOff();
    virtual void turnOn();

    std::string getName() const;
    bool getStatus() const;
    virtual std::string getStatusString() const;

    // Overload unary operator! to simulate malfunction or reboot
    virtual void operator!();

    virtual bool isRemovable() const { return false; }

    // Phương thức đo năng lượng
    long long getActiveMinutes() const;
    long long getContinuousActiveMinutes() const;
    double getConsumedKWh() const;

    // Phương thức hỗ trợ Báo Cháy (Fire Alarm)
    virtual bool isEmergencyExit() const { return false; }
    virtual void unlockEmergency() {}
};

#endif // DEVICE_H