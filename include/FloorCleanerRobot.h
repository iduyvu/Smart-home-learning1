#ifndef FLOORCLEANERROBOT_H
#define FLOORCLEANERROBOT_H

#include "Device.h"

class FloorCleanerRobot : public Device {
public:
    FloorCleanerRobot(std::string n);

    void toggle() override;
    void turnOff() override;
    std::string getStatusString() const override;

    bool isRemovable() const override { return true; }
};

#endif // FLOORCLEANERROBOT_H