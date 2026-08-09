#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <string>

class Device {
protected:
    std::string name;
    bool isOn;
public:
    Device(std::string n);
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
};

#endif // DEVICE_H