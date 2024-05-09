//
// Created by Øystein Bringsli.
//

#include <Arduino.h>
#include "TimerStats.hpp"

TimerStats::TimerStats(): prevTime(millis()) {}

void TimerStats::startTimer() {
    iters++;
    printIters++;

    if (iters % updateFreq == 0) {
        estimatedLoopTime /* (milliseconds) */ = static_cast<double>(millis() - prevTime) / static_cast<double>(updateFreq);
        loopsPerTimeunit  /* (loops per second) */ = static_cast<long>(1000.0 / estimatedLoopTime);
        iters = 0;
        prevTime = millis();

        updateFreq = loopsPerTimeunit;
        printTimerData();
    }
}

void TimerStats::printTimerData() const {
    Serial.print("Loops per second: ");
    Serial.print(loopsPerTimeunit);
    Serial.print(" | ");
    Serial.print("Estimated loop-time: ");
    Serial.print(estimatedLoopTime);
    Serial.println(" ms.");
}

TimerData TimerStats::getTimerData() {
    return {loopsPerTimeunit, estimatedLoopTime};
}