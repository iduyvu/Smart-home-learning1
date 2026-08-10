#ifndef SMARTLOCK_H
#define SMARTLOCK_H

#include "Device.h"

class SmartLock : public Device {
private:
    bool isLocked;
public:
    SmartLock(std::string n);

    void toggle() override;
    void turnOff() override;

    void lock();
    void unlock();

    std::string getStatusString() const override;

    bool isEmergencyExit() const override { return true; }
    void unlockEmergency() override;
};

#endif // SMARTLOCK_H