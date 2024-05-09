#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

#include "internetAccess.hpp"
#include "LedController.hpp"
#include "DateTime.hpp"
#include "TimerStats.hpp"

LedController controller;
DateTime dateTime;
TimerStats timer;
unsigned long prevPrintTime;

void setup() {
    // delay(3000); // To protect from too much power consumption??

    Serial.begin(115200);
    Serial.println();
    Serial.println("Serial established.");

    WiFi.begin(internetSSID, internetPassword);

    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
    }

    Serial.println("Wifi connected.");
    prevPrintTime = millis();

    controller.init();
    dateTime.init();
    ArduinoOTA.begin();
}

void printInfo() {

    auto time = dateTime.getCurrentTime();
    auto timeState = dateTime.getTimeState();
    Serial.print("Current time: ");
    Serial.print(time.hour);
    Serial.print(":");
    Serial.print(time.minute);
    Serial.print(":");
    Serial.print(time.second);

    Serial.print(". Timestate: ");
    switch (timeState) {

        case DateTime::MORNING:
        {
            Serial.print("morning");
        }
            break;
        case DateTime::SCHOOL:
        {
            Serial.print("school");
        }
            break;
        case DateTime::DAY:
        {
            Serial.print("day");
        }
            break;
        case DateTime::EVENING:
        {
            Serial.print("evening");
        }
            break;
        case DateTime::NIGHT:
        {
            Serial.print("night");
        }
            break;
    }
    Serial.print(". ");

    Serial.print("ESP32 IP Address: ");
    Serial.print(WiFi.localIP());

    Serial.print(". t: ");
    Serial.print(dateTime.progress, 8);

    Serial.println();
}

void loop() {

    ArduinoOTA.handle();
    timer.startTimer();

    int printInterval = 1000;
    if ((prevPrintTime + printInterval) < millis()) {
        printInfo();
        prevPrintTime = millis();
    }

    controller.step();
}