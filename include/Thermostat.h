#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "Device.h"
#include "Heater.h"
#include "Cooler.h"
#include <memory>

class Thermostat : public Device {
private:
    int temperature;
    std::shared_ptr<Heater> linkedHeater;
    std::shared_ptr<Cooler> linkedCooler;
public:
    Thermostat(std::string n, std::shared_ptr<Heater> h = nullptr, std::shared_ptr<Cooler> c = nullptr);

    void toggle() override;
    void setTemperature(int temp);
    void triggerFeedbackLoop();
};

#endif // THERMOSTAT_H