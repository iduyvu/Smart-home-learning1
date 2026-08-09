#ifndef COOLER_H
#define COOLER_H

#include "Device.h"

class Cooler : public Device {
public:
    Cooler(std::string n);
    void toggle() override;
};

#endif // COOLER_H