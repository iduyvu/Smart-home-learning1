#ifndef GARDENLIGHT_H
#define GARDENLIGHT_H

#include "Device.h"

class GardenLight : public Device {
public:
    GardenLight(std::string n);

    void toggle() override;
    void turnOff() override;

    bool isRemovable() const override { return true; }
};

#endif // GARDENLIGHT_H