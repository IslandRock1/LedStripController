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
private:
    float hue = 1.0;
};


#endif //LEDSTRIPCONTROLLER_LEDCONTROLLER_HPP
