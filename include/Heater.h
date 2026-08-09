#ifndef HEATER_H
#define HEATER_H

#include "Device.h"

class Heater : public Device {
public:
    Heater(std::string n);
    void toggle() override;
};

#endif // HEATER_H