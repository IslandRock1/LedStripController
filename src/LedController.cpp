//
// Created by Øystein Bringsli.
//


#include <cmath>
#include "LedController.hpp"

LedController::LedController() {}

float myFmod(float x, float y) {
    if (y == 0.0f) {
        // Handle division by zero
        return 0.0f;
    }

    float quotient = x / y;
    return x - y * floorf(quotient);
}

float myAbs(float x) {
    return (x < 0.0f) ? -x : x;
}

LedController::RGB LedController::nextHueColor() {

    hue++;
    hue = myFmod(hue, 360.0f);

    auto hueNormalized = hue / 60.0f;
    float chroma = 1.0f;

    // Calculate intermediate values

    float x = chroma * (1.0f - myAbs(myFmod(hueNormalized, 2.0f) - 1.0f));
    float r1, g1, b1;

    if (hueNormalized < 1.0f) {
        r1 = chroma;
        g1 = x;
        b1 = 0.0f;
    } else if (hueNormalized < 2.0f) {
        r1 = x;
        g1 = chroma;
        b1 = 0.0f;
    } else if (hueNormalized < 3.0f) {
        r1 = 0.0f;
        g1 = chroma;
        b1 = x;
    } else if (hueNormalized < 4.0f) {
        r1 = 0.0f;
        g1 = x;
        b1 = chroma;
    } else if (hueNormalized < 5.0f) {
        r1 = x;
        g1 = 0.0f;
        b1 = chroma;
    } else {
        r1 = chroma;
        g1 = 0.0f;
        b1 = x;
    }

    // Calculate the lightness component
    float m = 1.0f - chroma;

    // Convert RGB values to 4-bit integers
    auto r = static_cast<int>((r1 + m) * 15);
    auto g = static_cast<int>((g1 + m) * 15);
    auto b = static_cast<int>((b1 + m) * 15);

    return {r, g, b};
}
