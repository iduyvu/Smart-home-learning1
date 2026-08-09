#include <iostream>
#include <string>
#include <memory>

#include "Hub.h"
#include "Light.h"
#include "SmartLock.h"
#include "SecurityCamera.h"
#include "Heater.h"
#include "Cooler.h"
#include "Thermostat.h"
#include "Window.h"
#include "GardenLight.h"
#include "FloorCleanerRobot.h"

using namespace std;

void demoFeedbackLoop(std::shared_ptr<Thermostat> thermo) {
    thermo->triggerFeedbackLoop();
}

void demoUnauthorizedAccess(std::shared_ptr<SecurityCamera> cam) {
    cout << "\n--- 5. Kịch bản B: Cố gắng truy cập trái phép ---" << endl;
    cout << "Đang thử kích hoạt Camera an ninh với khóa 'HACKER99'..." << endl;
    cam->arm("HACKER99");
}

void showMenu() {
    cout << "\n=================================================" << endl;
    cout << "    Trung Tâm Nhà Thông Minh - Bảng Điều Khiển   " << endl;
    cout << "=================================================" << endl;
    cout << "1. Liệt kê tất cả thiết bị" << endl;
    cout << "2. Chuyển đổi một thiết bị cụ thể" << endl;
    cout << "3. Chuyển đổi tất cả thiết bị (Demo Đa Hình)" << endl;
    cout << "4. Mô phỏng lỗi thiết bị (Demo Nạp Chồng Toán Tử)" << endl;
    cout << "5. Thực thi Macro 'Chúc Ngủ Ngon'" << endl;
    cout << "6. Chạy Kịch bản A: Vòng lặp phản hồi" << endl;
    cout << "7. Chạy Kịch bản B: Truy cập trái phép" << endl;
    cout << "8. Thoát" << endl;
    cout << "9. Thêm thiết bị" << endl;
    cout << "10. Xóa thiết bị" << endl;
    cout << "=================================================" << endl;
    cout << "Nhập lựa chọn của bạn: ";
}

int main() {
    // Initialize Devices using std::shared_ptr
    auto livingLight = make_shared<Light>("Đèn Phòng Khách");
    auto kitchenLight = make_shared<Light>("Đèn Nhà Bếp");
    auto frontDoor = make_shared<SmartLock>("Cửa Chính");
    auto frontCam = make_shared<SecurityCamera>("Camera Cửa Chính", "secure123");

    auto hvacHeater = make_shared<Heater>("Máy sưởi HVAC");
    auto hvacCooler = make_shared<Cooler>("Máy lạnh HVAC");
    auto mainThermo = make_shared<Thermostat>("Bộ điều nhiệt Chính", hvacHeater, hvacCooler);

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
            cout << "\nĐang thoát Trung tâm Nhà thông minh..." << endl;
            break;
        }

        int choice = 0;
        try {
            choice = stoi(choiceStr);
        } catch (...) {
            cout << "Đầu vào không hợp lệ. Vui lòng nhập một số." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                myHub.listDevices();
                break;
            case 2: {
                myHub.listDevices();
                cout << "Nhập số thiết bị để chuyển đổi (1-" << myHub.getDeviceCount() << "): ";
                string devChoiceStr;
                cin >> devChoiceStr;
                try {
                    int devChoice = stoi(devChoiceStr);
                    auto d = myHub.getDevice(devChoice - 1);
                    if (d) {
                        d->toggle();
                    } else {
                        cout << "Số thiết bị không hợp lệ." << endl;
                    }
                } catch (...) {
                    cout << "Đầu vào không hợp lệ." << endl;
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
                myHub.executeGoodNightMacro(mainThermo, frontDoor, frontCam, "secure123");
                break;
            case 6:
                demoFeedbackLoop(mainThermo);
                break;
            case 7:
                demoUnauthorizedAccess(frontCam);
                break;
            case 8:
                cout << "Đang thoát Trung tâm Nhà thông minh. Tạm biệt!" << endl;
                running = false;
                break;
            case 9: {
                cout << "\n--- Thêm Thiết Bị ---" << endl;
                cout << "1. Cửa sổ" << endl;
                cout << "2. Đèn sân vườn" << endl;
                cout << "3. Robot hút bụi" << endl;
                cout << "Chọn loại thiết bị (1-3): ";
                string typeChoiceStr;
                cin >> typeChoiceStr;

                try {
                    int typeChoice = stoi(typeChoiceStr);
                    cout << "Nhập tên thiết bị: ";
                    string devName;
                    cin.ignore();
                    getline(cin, devName);

                    if (typeChoice == 1) {
                        myHub.addDevice(make_shared<Window>(devName));
                        cout << "Đã thêm Cửa sổ: " << devName << endl;
                    } else if (typeChoice == 2) {
                        myHub.addDevice(make_shared<GardenLight>(devName));
                        cout << "Đã thêm Đèn sân vườn: " << devName << endl;
                    } else if (typeChoice == 3) {
                        myHub.addDevice(make_shared<FloorCleanerRobot>(devName));
                        cout << "Đã thêm Robot hút bụi: " << devName << endl;
                    } else {
                        cout << "Loại thiết bị không hợp lệ." << endl;
                    }
                } catch (...) {
                    cout << "Đầu vào không hợp lệ." << endl;
                }
                break;
            }
            case 10: {
                myHub.listRemovableDevices();
                cout << "Nhập số thiết bị để xóa (hoặc 0 để hủy): ";
                string remChoiceStr;
                cin >> remChoiceStr;
                try {
                    int remChoice = stoi(remChoiceStr);
                    if (remChoice > 0) {
                        size_t actualIndex;
                        auto d = myHub.getRemovableDevice(remChoice - 1, actualIndex);
                        if (d) {
                            myHub.removeDevice(actualIndex);
                        } else {
                            cout << "Số thiết bị không hợp lệ." << endl;
                        }
                    }
                } catch (...) {
                    cout << "Đầu vào không hợp lệ." << endl;
                }
                break;
            }
            default:
                cout << "Lựa chọn không hợp lệ. Vui lòng chọn từ 1-10." << endl;
        }
    }

    return 0;
}