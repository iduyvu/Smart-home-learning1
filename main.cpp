#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

// Forward declarations
class Heater;
class Cooler;

// --- Abstract Base Class ---
class Device {
protected:
    string name;
    bool isOn;
public:
    Device(string n) : name(n), isOn(false) {}
    virtual ~Device() {}

    // Pure virtual function enforcing polymorphism
    virtual void toggle() = 0;

    string getName() const { return name; }
    bool getStatus() const { return isOn; }

    // Overload unary operator! to simulate malfunction or reboot
    virtual void operator!() {
        cout << "[!] WARNING: Device '" << name << "' is malfunctioning/rebooting!" << endl;
        isOn = false;
    }
};

// --- Derived Classes ---
class Light : public Device {
public:
    Light(string n) : Device(n) {}

    void toggle() override {
        isOn = !isOn;
        cout << "[Light] " << name << " is now " << (isOn ? "ON" : "OFF") << endl;
    }

    void turnOff() {
        if (isOn) {
            toggle();
        } else {
            cout << "[Light] " << name << " is already OFF." << endl;
        }
    }
};

class SmartLock : public Device {
private:
    bool isLocked;
public:
    SmartLock(string n) : Device(n), isLocked(false) {}

    void toggle() override {
        isOn = !isOn;
        isLocked = !isLocked;
        cout << "[SmartLock] " << name << " is now " << (isLocked ? "LOCKED" : "UNLOCKED") << endl;
    }

    void lock() {
        if (!isLocked) {
            toggle();
        } else {
            cout << "[SmartLock] " << name << " is already LOCKED." << endl;
        }
    }
};

class SecurityCamera : public Device {
private:
    bool isArmed;
    string authKey;
public:
    SecurityCamera(string n, string key) : Device(n), isArmed(false), authKey(key) {}

    void toggle() override {
        isOn = !isOn;
        cout << "[SecurityCamera] " << name << " power is now " << (isOn ? "ON" : "OFF") << endl;
    }

    bool authenticate(const string& key) {
        if (key == authKey) {
            cout << "[SecurityCamera] Authentication SUCCESS for " << name << "." << endl;
            return true;
        } else {
            cout << "[SecurityCamera] ERROR: Authentication FAILED for " << name << "! Unauthorized access attempt." << endl;
            return false;
        }
    }

    void arm(const string& key) {
        if (authenticate(key)) {
            isArmed = true;
            cout << "[SecurityCamera] " << name << " is now ARMED." << endl;
        } else {
            cout << "[SecurityCamera] Action denied: " << name << " could not be armed due to auth failure." << endl;
        }
    }
};

class Heater : public Device {
public:
    Heater(string n) : Device(n) {}
    void toggle() override {
        isOn = !isOn;
        cout << "[Heater] " << name << " is now " << (isOn ? "ON" : "OFF") << endl;
    }
};

class Cooler : public Device {
public:
    Cooler(string n) : Device(n) {}
    void toggle() override {
        isOn = !isOn;
        cout << "[Cooler] " << name << " is now " << (isOn ? "ON" : "OFF") << endl;
    }
};

class Thermostat : public Device {
private:
    int temperature;
    Heater* linkedHeater;
    Cooler* linkedCooler;
public:
    Thermostat(string n, Heater* h = nullptr, Cooler* c = nullptr)
        : Device(n), temperature(22), linkedHeater(h), linkedCooler(c) {}

    void toggle() override {
        isOn = !isOn;
        cout << "[Thermostat] " << name << " is now " << (isOn ? "ON" : "OFF") << endl;
    }

    void setTemperature(int temp) {
        temperature = temp;
        cout << "[Thermostat] " << name << " target temperature set to " << temperature << "°C" << endl;
    }

    void triggerFeedbackLoop() {
        cout << "\n--- Initiating Scenario A: Environment Feedback Loop ---" << endl;
        int currentTemp = 18;
        int targetTemp = 22;
        int iterations = 0;

        while (iterations < 6) {
            this_thread::sleep_for(chrono::milliseconds(800));
            if (currentTemp < targetTemp) {
                cout << "[Thermostat] Reading: " << currentTemp << "°C (Too cold!). Triggering Heater..." << endl;
                if (!linkedHeater->getStatus()) linkedHeater->toggle();
                if (linkedCooler->getStatus()) linkedCooler->toggle();

                currentTemp += 10; // Instantly heats up past target
                cout << "   -> [Environment] Heater caused temperature to spike to " << currentTemp << "°C!" << endl;
            } else {
                cout << "[Thermostat] Reading: " << currentTemp << "°C (Too hot!). Triggering Cooler..." << endl;
                if (!linkedCooler->getStatus()) linkedCooler->toggle();
                if (linkedHeater->getStatus()) linkedHeater->toggle();

                currentTemp -= 10; // Instantly cools down below target
                cout << "   -> [Environment] Cooler caused temperature to drop to " << currentTemp << "°C!" << endl;
            }
            iterations++;
        }
        cout << "[System] Warning: Infinite feedback loop detected! Force terminating HVAC operations." << endl;
        if (linkedHeater->getStatus()) linkedHeater->toggle();
        if (linkedCooler->getStatus()) linkedCooler->toggle();
    }
};

// --- Hub Class ---
class Hub {
private:
    vector<Device*> devices;
public:
    void addDevice(Device* d) {
        devices.push_back(d);
    }

    void toggleAll() {
        cout << "\n--- 1. Normal Polymorphic Toggling ---" << endl;
        for (Device* d : devices) {
            d->toggle();
            this_thread::sleep_for(chrono::milliseconds(300));
        }
    }

    void demonstrateOverload() {
        cout << "\n--- 2. Demonstrating Operator Overloading (!Device) ---" << endl;
        if (devices.size() >= 2) {
            !(*devices[0]); // Using overloaded operator!
            this_thread::sleep_for(chrono::milliseconds(400));
            !(*devices[1]);
        }
    }

    void executeGoodNightMacro(Light* livingLight, Light* kitchenLight, Thermostat* thermo, SmartLock* frontDoor, SecurityCamera* cam, const string& authKey) {
        cout << "\n--- 3. Executing 'Good Night' Macro (5+ devices) ---" << endl;

        cout << "Step 1: Turning off Living Room Light..." << endl;
        livingLight->turnOff();
        this_thread::sleep_for(chrono::milliseconds(500));

        cout << "Step 2: Turning off Kitchen Light..." << endl;
        kitchenLight->turnOff();
        this_thread::sleep_for(chrono::milliseconds(500));

        cout << "Step 3: Setting Thermostat to 20°C..." << endl;
        thermo->setTemperature(20);
        this_thread::sleep_for(chrono::milliseconds(500));

        cout << "Step 4: Locking Front Door..." << endl;
        frontDoor->lock();
        this_thread::sleep_for(chrono::milliseconds(500));

        cout << "Step 5: Arming Security Camera..." << endl;
        cam->arm(authKey);
        this_thread::sleep_for(chrono::milliseconds(500));

        cout << "['Good Night' Macro Execution Complete]" << endl;
    }
};

void demoFeedbackLoop(Thermostat* thermo) {
    thermo->triggerFeedbackLoop();
}

void demoUnauthorizedAccess(SecurityCamera* cam) {
    cout << "\n--- 5. Scenario B: Unauthorized Access Attempt ---" << endl;
    cout << "Attempting to arm Security Camera with key 'HACKER99'..." << endl;
    this_thread::sleep_for(chrono::milliseconds(800));
    cam->arm("HACKER99");
}

int main() {
    cout << "=================================================" << endl;
    cout << "        Smart Home Hub - Demo Script             " << endl;
    cout << "=================================================" << endl;
    this_thread::sleep_for(chrono::seconds(1));

    // Initialize Devices
    Light* livingLight = new Light("Living Room Light");
    Light* kitchenLight = new Light("Kitchen Light");
    SmartLock* frontDoor = new SmartLock("Front Door");
    SecurityCamera* frontCam = new SecurityCamera("Front Door Cam", "secure123");

    Heater* hvacHeater = new Heater("HVAC Heater");
    Cooler* hvacCooler = new Cooler("HVAC Cooler");
    Thermostat* mainThermo = new Thermostat("Main Thermostat", hvacHeater, hvacCooler);

    Hub myHub;
    myHub.addDevice(livingLight);
    myHub.addDevice(kitchenLight);
    myHub.addDevice(frontDoor);
    myHub.addDevice(frontCam);
    myHub.addDevice(hvacHeater);
    myHub.addDevice(hvacCooler);
    myHub.addDevice(mainThermo);

    // 1. Normal polymorphic toggling
    myHub.toggleAll();
    this_thread::sleep_for(chrono::seconds(1));

    // 2. Operator overloading demonstration
    myHub.demonstrateOverload();
    this_thread::sleep_for(chrono::seconds(1));

    // Set some initial states to make the Good Night macro more meaningful
    if (!livingLight->getStatus()) livingLight->toggle();
    if (!kitchenLight->getStatus()) kitchenLight->toggle();
    if (frontDoor->getStatus()) frontDoor->toggle(); // ensure it's unlocked initially

    // 3. The "Good Night" Macro (5+ devices)
    myHub.executeGoodNightMacro(livingLight, kitchenLight, mainThermo, frontDoor, frontCam, "secure123");
    this_thread::sleep_for(chrono::seconds(1));

    // 4. The Feedback Loop scenario
    demoFeedbackLoop(mainThermo);
    this_thread::sleep_for(chrono::seconds(1));

    // 5. The Unauthorized Access scenario
    demoUnauthorizedAccess(frontCam);
    this_thread::sleep_for(chrono::seconds(1));

    cout << "\n=================================================" << endl;
    cout << "              Demo Completed                     " << endl;
    cout << "=================================================" << endl;

    // Cleanup dynamically allocated devices
    delete livingLight;
    delete kitchenLight;
    delete frontDoor;
    delete frontCam;
    delete hvacHeater;
    delete hvacCooler;
    delete mainThermo;

    return 0;
}
