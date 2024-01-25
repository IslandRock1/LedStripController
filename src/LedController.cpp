//
// Created by Øystein Bringsli.
//

#include "LedController.hpp"



double myFmod(double x, double y) {
    if (y == 0.0) {
        // Handle division by zero
        return 0.0;
    }

    double quotient = x / y;
    double intPart = static_cast<int>(quotient); // Integer part of the quotient
    return x - y * intPart;
}

double myAbs(double x) {
    return (x < 0) ? -x : x;
}

RGB LedController::nextHueColor() {

    hue++;
    hue = myFmod(hue, 360);

    auto hueNormalized = hue / 60.0;
    double chroma = 1.0;

    // Calculate intermediate values

    double x = chroma * (1.0 - myAbs(myFmod(hueNormalized, 2.0) - 1.0));
    double r1, g1, b1;

    if (hueNormalized < 1.0) {
        r1 = chroma;
        g1 = x;
        b1 = 0.0;
    } else if (hueNormalized < 2.0) {
        r1 = x;
        g1 = chroma;
        b1 = 0.0;
    } else if (hueNormalized < 3.0) {
        r1 = 0.0;
        g1 = chroma;
        b1 = x;
    } else if (hueNormalized < 4.0) {
        r1 = 0.0;
        g1 = x;
        b1 = chroma;
    } else if (hueNormalized < 5.0) {
        r1 = x;
        g1 = 0.0;
        b1 = chroma;
    } else {
        r1 = chroma;
        g1 = 0.0;
        b1 = x;
    }

    // Calculate the lightness component
    double m = 1.0 - chroma;

    // Convert RGB values to 8-bit integers
    auto r = static_cast<int>((r1 + m) * 15);
    auto g = static_cast<int>((g1 + m) * 15);
    auto b = static_cast<int>((b1 + m) * 15);

    return {r, g, b};
}
