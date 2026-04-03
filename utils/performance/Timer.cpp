//
// Created by alejandro on 27/3/26.
//

#include "Timer.h"

std::chrono::high_resolution_clock::time_point Timer::startTime;

void Timer::startTimer() {

    startTime = std::chrono::high_resolution_clock::now();
}

long long Timer::stopTimer() {

    auto end =
   std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast
    <
        std::chrono::nanoseconds
    >
    (end - Timer::startTime).count();
}