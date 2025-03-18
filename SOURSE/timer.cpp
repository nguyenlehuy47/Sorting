#include <chrono>
#include "utils/timer.h"

using namespace std::chrono;

// Hàm bắt đầu đo thời gian
high_resolution_clock::time_point startTimer() {
    return high_resolution_clock::now();
}

// Hàm kết thúc đo thời gian và trả về thời gian chạy (tính bằng milliseconds)
long long endTimer(high_resolution_clock::time_point start) {
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}