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

int DateTime::timeDiffSeconds(int t0, int t1) {
    /*
     * t1 must be bigger than t0
     */

    auto t0Hour = t0 / 10000;
    auto t0Min = (t0 % 10000) / 100;
    auto t0Sec = t0 % 100;

    auto t1Hour = t1 / 10000;
    auto t1Min = (t1 % 10000) / 100;
    auto t1Sec = t1 % 100;

    if (t1Sec < t0Sec) {
        t1Min--;
        t1Sec = 60 - t0Sec + t1Sec;
        t0Sec = 0;
    }

    if (t1Min < t0Min) {
        t1Hour--;
        t1Min = 60 - t0Min + t1Min;
        t0Min = 0;
    }

    auto hourDiff = t1Hour - t0Hour;
    auto minDiff = t1Min - t0Min;
    auto secDiff = t1Sec - t0Sec;

    return hourDiff * 60 * 60 + minDiff * 60 + secDiff;
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
    int eveningTime = 2200;
    int nightTime = 2230;

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
        {
            // Thursday
        } break;

        case 5:
        {
            // Friday
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

    else if (time > eveningTime) {

        auto T = timeDiffSeconds(eveningTime * 100, nightTime * 100);
        auto t = timeDiffSeconds(eveningTime * 100, time * 100 + timeInfo.tm_sec);
        progress = static_cast<double>(t) / static_cast<double>(T);

        return EVENING;
    }

    else if (time > dayTime) {
        auto T = timeDiffSeconds(dayTime * 100, eveningTime * 100);
        auto t = timeDiffSeconds(dayTime * 100, time * 100 + timeInfo.tm_sec);

//        Serial.print(t);
//        Serial.print(" | ");
//        Serial.println(T);

        progress = static_cast<double>(t) / static_cast<double>(T);

        return DAY;
    }

    else if (time > schoolTime) {return SCHOOL;}

    else if (time > morningTime) {
        auto T = timeDiffSeconds(morningTime * 100, schoolTime * 100);
        auto t = timeDiffSeconds(morningTime * 100, time * 100 + timeInfo.tm_sec);
        progress = static_cast<double>(t) / static_cast<double>(T);

        return MORNING;
    }

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