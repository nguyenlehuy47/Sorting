#ifndef TIMER_H
#define TIMER_H

#include <chrono> // Thêm thư viện này

using namespace std::chrono; // Thêm namespace này

// Hàm bắt đầu đo thời gian
high_resolution_clock::time_point startTimer();

// Hàm kết thúc đo thời gian và trả về thời gian chạy (tính bằng milliseconds)
long long endTimer(high_resolution_clock::time_point start);

#endif