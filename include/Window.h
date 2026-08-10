#ifndef WINDOW_H
#define WINDOW_H

#include "Device.h"

class Window : public Device {
private:
    bool isLocked;
public:
    Window(std::string n);

    void toggle() override;
    void turnOff() override;

    void lock();
    void unlock();

    std::string getStatusString() const override;

    bool isRemovable() const override { return true; }

    bool isEmergencyExit() const override { return true; }
    void unlockEmergency() override;
};

#endif // WINDOW_H