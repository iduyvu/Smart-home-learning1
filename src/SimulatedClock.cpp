#include "SimulatedClock.h"

// Khởi tạo thời gian bắt đầu bằng thời gian thực tế lúc chạy chương trình
std::chrono::system_clock::time_point SimulatedClock::currentTime = std::chrono::system_clock::now();

std::chrono::system_clock::time_point SimulatedClock::now() {
    return currentTime;
}

void SimulatedClock::advanceTime(int minutes) {
    currentTime += std::chrono::minutes(minutes);
}
