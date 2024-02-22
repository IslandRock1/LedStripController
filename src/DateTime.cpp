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

    int nightTime = 2330;
    int eveningTime = 2300;
    int dayTime = 900;
    int morningTime = 830;

    switch (timeInfo.tm_wday) {
        case 0:
            // Sunday
            break;
        case 1:
            // Monday
            break;
        case 2:
            // Tuesday
            break;
        case 3:
            // Wednesday
            break;
        case 4:
            // Thursday
            break;

        case 5:
        {
            morningTime = 700;
            dayTime = 830;
        } break;

        case 6:
            // Saturday
            break;
        default:
            // Invalid weekday
            break;
    }
    
    if (time > nightTime) {return NIGHT;}
    else if (time > eveningTime) {return EVENING;}
    else if (time > dayTime) {return  DAY;}
    else if (time > morningTime) {return MORNING;}
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