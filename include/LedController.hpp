//
// Created by Øystein Bringsli.
//

#ifndef LEDSTRIPCONTROLLER_LEDCONTROLLER_HPP
#define LEDSTRIPCONTROLLER_LEDCONTROLLER_HPP

#include <vector>

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
    static void turnOff();
    static void fastLedShow();

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
    void fadeIn();
    void fadeOut();
    void cycleHue();

    double t = 1.0;
    std::vector<RGB> activationFunction(bool inverse = false) const;

};


#endif //LEDSTRIPCONTROLLER_LEDCONTROLLER_HPP
