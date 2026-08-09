#ifndef SECURITYCAMERA_H
#define SECURITYCAMERA_H

#include "Device.h"

class SecurityCamera : public Device {
private:
    bool isArmed;
    std::string authKey;
public:
    SecurityCamera(std::string n, std::string key);

    void toggle() override;
    bool authenticate(const std::string& key);
    void arm(const std::string& key);
};

#endif // SECURITYCAMERA_H