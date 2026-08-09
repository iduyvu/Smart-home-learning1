#ifndef LIGHT_H
#define LIGHT_H

#include "Device.h"

class Light : public Device {
public:
    Light(std::string n);

    void toggle() override;
    void turnOff() override;
};

#endif // LIGHT_H