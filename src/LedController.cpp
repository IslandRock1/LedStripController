//
// Created by Øystein Bringsli.
//

#include <cmath>
#include <FastLED.h>
#include "LedController.hpp"

#define NUM_LEDS 432
#define DATA_PIN 33

CRGB leds[NUM_LEDS];
CRGB crgb;

LedController::LedController()
    : prevColorChangeTime(millis()), prevCycleChangeTime(millis()) {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

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

void LedController::cycle(RGB nextColor, int start, int end) {
    if (start < end) {
        for (int i = end; i > start; i--)
        {
            leds[i] = leds[i - 1];
        }
    }

    else if (start > end) {
        for (int i = end; i < start; i++)
        {
            leds[i] = leds[i + 1];
        }
    }

    leds[start] = crgb.setRGB(nextColor.r, nextColor.g, nextColor.b);
}

void LedController::fadeIn() {
    unsigned long timeStep = 60000;
    if ((millis() - prevColorChangeTime) > timeStep) {
        if (currentColor.b < currentColor.g) {
            currentColor.b++;
        } else {
            currentColor.r++;
        }

        if (currentColor.r > 15) {currentColor.r = 15;}
        prevColorChangeTime = millis();
    }

    unsigned long cycleTimeStep = 200;
    if ((millis() - prevCycleChangeTime) > cycleTimeStep) {
        cycle(currentColor, 0, NUM_LEDS);
        prevCycleChangeTime = millis();
    }
}

void LedController::step() {
    fadeIn();

    FastLED.show();
}
