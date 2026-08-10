#ifndef HUB_H
#define HUB_H

#include <vector>
#include <memory>
#include "Device.h"
#include "Thermostat.h"
#include "SmartLock.h"
#include "SecurityCamera.h"

class Hub {
private:
    std::vector<std::shared_ptr<Device>> devices;
public:
    void addDevice(std::shared_ptr<Device> d);
    void removeDevice(size_t index);

    void toggleAll();
    void demonstrateOverload();
    void listDevices() const;
    void listRemovableDevices() const;

    size_t getDeviceCount() const;
    std::shared_ptr<Device> getDevice(size_t index);
    std::shared_ptr<Device> getRemovableDevice(size_t removableIndex, size_t& actualIndex);

    void executeGoodNightMacro(std::shared_ptr<Thermostat> thermo, std::shared_ptr<SmartLock> frontDoor, std::shared_ptr<SecurityCamera> cam, const std::string& authKey);

    void tickTime(int minutes);
    void triggerFireAlarmMacro();
};

#endif // HUB_H