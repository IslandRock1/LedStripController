//
// Created by Øystein Bringsli.
//

#include <cmath>
#include <FastLED.h>
#include "LedController.hpp"

#define NUM_LEDS 144
#define DATA_PIN 33

CRGB leds[NUM_LEDS];
CRGB crgb;

LedController::LedController()
    : prevHueCycle(millis()) {
}

void LedController::init() {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    FastLED.setMaxRefreshRate(0);
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
    float colorSize = 255.0;
    auto r = static_cast<int>((r1 + m) * colorSize);
    auto g = static_cast<int>((g1 + m) * colorSize);
    auto b = static_cast<int>((b1 + m) * colorSize);

    return {r, g, b};
}

void LedController::cycle(LedController::RGB nextColor, int start, int end) {
    for (int i = end; i > start; i--)
    {
        leds[i] = leds[i - 1];
    }

    leds[start].r = nextColor.r;
    leds[start].g = nextColor.g;
    leds[start].b = nextColor.b;
}

void LedController::cycleHue() {
    unsigned long hueTimeStep = 200;
    if ((millis() - prevHueCycle) > hueTimeStep) {
        auto next = nextHueColor();
        cycle(next, 0, NUM_LEDS - 1);
        prevHueCycle = millis();
    }
}

void LedController::step() {
    cycleHue();
    FastLED.show();
}