#ifndef WINDOW_H
#define WINDOW_H

#include "Device.h"

class Window : public Device {
public:
    Window(std::string n);

    void toggle() override;
    void turnOff() override;
    std::string getStatusString() const override;

    bool isRemovable() const override { return true; }
};

#endif // WINDOW_H