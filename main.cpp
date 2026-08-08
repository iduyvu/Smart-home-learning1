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
public:
    SmartLock(string n) : Device(n) {}

    void toggle() override {
        isOn = !isOn;
        cout << "[SmartLock] " << name << " is now " << (isOn ? "LOCKED" : "UNLOCKED") << endl;
    }

    void lock() {
        if (!isOn) {
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

    void listDevices() const {
        cout << "\n--- Connected Devices ---" << endl;
        for (size_t i = 0; i < devices.size(); ++i) {
            cout << i + 1 << ". " << devices[i]->getName() << " [" << (devices[i]->getStatus() ? "ON" : "OFF") << "]" << endl;
        }
    }

    size_t getDeviceCount() const {
        return devices.size();
    }

    Device* getDevice(size_t index) {
        if (index < devices.size()) {
            return devices[index];
        }
        return nullptr;
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

void showMenu() {
    cout << "\n=================================================" << endl;
    cout << "        Smart Home Hub - Control Panel           " << endl;
    cout << "=================================================" << endl;
    cout << "1. List all devices" << endl;
    cout << "2. Toggle a specific device" << endl;
    cout << "3. Toggle all devices (Polymorphic Demo)" << endl;
    cout << "4. Simulate device malfunction (Operator Overload Demo)" << endl;
    cout << "5. Execute 'Good Night' Macro" << endl;
    cout << "6. Run Scenario A: Feedback Loop" << endl;
    cout << "7. Run Scenario B: Unauthorized Access" << endl;
    cout << "8. Exit" << endl;
    cout << "=================================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
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

    bool running = true;
    while (running) {
        showMenu();
        string choiceStr;
        if (!(cin >> choiceStr)) {
            // Handle EOF (Ctrl+D) or stream errors gracefully
            cout << "\nExiting Smart Home Hub..." << endl;
            break;
        }

        int choice = 0;
        try {
            choice = stoi(choiceStr);
        } catch (...) {
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                myHub.listDevices();
                break;
            case 2: {
                myHub.listDevices();
                cout << "Enter the device number to toggle (1-" << myHub.getDeviceCount() << "): ";
                string devChoiceStr;
                cin >> devChoiceStr;
                try {
                    int devChoice = stoi(devChoiceStr);
                    Device* d = myHub.getDevice(devChoice - 1);
                    if (d) {
                        d->toggle();
                    } else {
                        cout << "Invalid device number." << endl;
                    }
                } catch (...) {
                    cout << "Invalid input." << endl;
                }
                break;
            }
            case 3:
                myHub.toggleAll();
                break;
            case 4:
                myHub.demonstrateOverload();
                break;
            case 5:
                myHub.executeGoodNightMacro(livingLight, kitchenLight, mainThermo, frontDoor, frontCam, "secure123");
                break;
            case 6:
                demoFeedbackLoop(mainThermo);
                break;
            case 7:
                demoUnauthorizedAccess(frontCam);
                break;
            case 8:
                cout << "Exiting Smart Home Hub. Goodbye!" << endl;
                running = false;
                break;
            default:
                cout << "Invalid choice. Please select from 1-8." << endl;
        }
    }

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
