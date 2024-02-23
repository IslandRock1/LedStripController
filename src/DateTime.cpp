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

    int morningTime = 830;
    int schoolTime = 900;
    int dayTime = 1600;
    int eveningTime = 2300;
    int nightTime = 2330;

    switch (timeInfo.tm_wday) {
        case 0:
        {
            // Sunday
            morningTime = 1000;
            schoolTime = 1030;
            dayTime = 1031;
        } break;

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
            // Friday
            morningTime = 700;
            schoolTime = 730;

            eveningTime = 2330;
            nightTime = 2400;
        } break;

        case 6:
        {
            // Saturday
            morningTime = 1000;
            schoolTime = 1030;
            dayTime = 1031;

            eveningTime = 2330;
            nightTime = 2400;

        } break;

        default:
            // Invalid weekday
            break;
    }
    
    if (time > nightTime) {return NIGHT;}
    else if (time > eveningTime) {return EVENING;}
    else if (time > dayTime) {return DAY;}
    else if (time > schoolTime) {return SCHOOL;}
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