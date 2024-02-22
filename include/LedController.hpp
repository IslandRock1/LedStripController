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

private:
    float hue = 1.0;

    RGB currentColorTimer = {1, 1, 1};
    unsigned long prevColorChangeTime;
    unsigned long prevCycleChangeTime;

    DateTime dateTime;
    DateTime::TimeState currentTimeState;
    void updateTimeState();

    void turnOff();
    void fadeIn();
    void fadeOut();

};


#endif //LEDSTRIPCONTROLLER_LEDCONTROLLER_HPP
