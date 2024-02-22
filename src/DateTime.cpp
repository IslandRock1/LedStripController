//
// Created by Øystein Bringsli.
//

#include <Arduino.h>
#include <time.h>
#include "DateTime.hpp"

DateTime::DateTime() {}

void DateTime::init() {
    configTime(3600, 3600, "pool.ntp.org");
}

DateTime::TimeState DateTime::getTimeState() {
    struct tm timeInfo;
    if(!getLocalTime(&timeInfo)){
        Serial.println("Failed to obtain time");
        // ESP.restart();
    }

    auto time = timeInfo.tm_hour * 100 + timeInfo.tm_min;

    if (time > 2330) {return NIGHT;}
    else if (time > 2300) {return EVENING;}
    else if (time > 900) {return  DAY;}
    else if (time > 830) {return MORNING;}
    else {return NIGHT;}
}

DateTime::CurrentTime DateTime::getCurrentTime() {
    struct tm timeInfo;
    if(!getLocalTime(&timeInfo)){
        Serial.println("Failed to obtain time");
        // ESP.restart();
    }

    return {timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec};
}