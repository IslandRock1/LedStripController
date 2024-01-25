//
// Created by Øystein Bringsli.
//

#ifndef LEDSTRIPCONTROLLER_LEDCONTROLLER_HPP
#define LEDSTRIPCONTROLLER_LEDCONTROLLER_HPP

struct RGB{
    int r;
    int g;
    int b;
};

class LedController {
public:
    RGB nextHueColor();
private:
    float hue = 1.0;
};


#endif //LEDSTRIPCONTROLLER_LEDCONTROLLER_HPP
