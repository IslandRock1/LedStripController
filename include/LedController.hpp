//
// Created by Øystein Bringsli.
//

#ifndef LEDSTRIPCONTROLLER_LEDCONTROLLER_HPP
#define LEDSTRIPCONTROLLER_LEDCONTROLLER_HPP

#include <vector>

class LedController {

public:
    LedController();
    static void init();

    void step();

private:
    struct RGB{
        int r;
        int g;
        int b;
    };

    float hue = 1.0;
    RGB nextHueColor();
    unsigned long prevHueCycle;

    void cycleHue();
    static void cycle(RGB nextColor, int start, int end);
};


#endif //LEDSTRIPCONTROLLER_LEDCONTROLLER_HPP
