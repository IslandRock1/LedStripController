//
// Created by Øystein Bringsli.
//

#ifndef LEDSTRIPCONTROLLER_LEDCONTROLLER_HPP
#define LEDSTRIPCONTROLLER_LEDCONTROLLER_HPP

#include "DateTime.hpp"

class LedController {

public:
    struct RGB{
        int r;
        int g;
        int b;
    };

    LedController();
    void init();

    RGB nextHueColor();
    static void cycle(RGB nextColor, int start, int end);
    void step();
    static void flash();

private:
    float hue = 1.0;
    unsigned long prevHueCycle;

    RGB currentColorTimer = {1, 1, 1};
    unsigned long prevColorChangeTime;
    unsigned long prevCycleChangeTime;

    DateTime dateTime;
    DateTime::TimeState currentTimeState;
    void updateTimeState();

    static void setAll(RGB color);
    static void turnOff();
    void fadeIn();
    void fadeOut();
    void cycleHue();

};


#endif //LEDSTRIPCONTROLLER_LEDCONTROLLER_HPP
