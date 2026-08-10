#ifndef SIMULATED_CLOCK_H
#define SIMULATED_CLOCK_H

#include <chrono>

// Lớp giả lập thời gian để phục vụ cho việc test các tính năng liên quan đến thời gian dài (như tiêu thụ điện).
class SimulatedClock {
private:
    static std::chrono::system_clock::time_point currentTime;
public:
    // Lấy thời điểm hiện tại của hệ thống mô phỏng
    static std::chrono::system_clock::time_point now();

    // Tiến lên phía trước một số phút nhất định
    static void advanceTime(int minutes);
};

#endif // SIMULATED_CLOCK_H
