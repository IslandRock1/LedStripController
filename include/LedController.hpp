//
// Created by Øystein Bringsli.
//

#ifndef LEDSTRIPCONTROLLER_LEDCONTROLLER_HPP
#define LEDSTRIPCONTROLLER_LEDCONTROLLER_HPP

class LedController {

public:
    struct RGB{
        int r;
        int g;
        int b;
    };

    LedController();
    RGB nextHueColor();
    static void cycle(RGB nextColor, int start, int end);
    void step();

private:
    float hue = 1.0;

    RGB currentColor = {1, 1, 1};
    unsigned long prevColorChangeTime;
    unsigned long prevCycleChangeTime;

    void fadeIn();
    void fadeOut();

};


#endif //LEDSTRIPCONTROLLER_LEDCONTROLLER_HPP
