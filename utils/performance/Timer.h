//
// Created by alejandro on 27/3/26.
//

#ifndef CATALOGOPRODUCTOS_TIMER_H
#define CATALOGOPRODUCTOS_TIMER_H
#include <chrono>


class Timer {

    public:
    static std::chrono::high_resolution_clock::time_point startTime;



    void startTimer();
    long long stopTimer();


};


#endif //CATALOGOPRODUCTOS_TIMER_H