#include <Arduino.h>

#include "LedController.hpp"
#include "TimerStats.hpp"

LedController controller;
TimerStats timer;

void setupSerial() {
    Serial.begin(115200);
    Serial.println();
    Serial.println("Serial established.");
}

void setup() {
    delay(3000); // To protect from too much power consumption??
    setupSerial();
    controller.init();
}

void loop() {
    controller.step();

    /////////////////////// TIMER STATS ///////////////////////
    timer.startTimer();
    // without FastLED.show()
    // Loops/s: ~120_000, Looptime: ~8.33 us
    // with FastLED.show()
    // Loops/s: ~226, Looptime: ~4.42 ms
}