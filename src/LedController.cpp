//
// Created by Øystein Bringsli.
//

#include <cmath>
#include <FastLED.h>
#include "DateTime.hpp"
#include "LedController.hpp"

#define NUM_LEDS 432
#define DATA_PIN 33

CRGB leds[NUM_LEDS];
CRGB crgb;

LedController::LedController()
    : prevColorChangeTime(millis()), prevCycleChangeTime(millis()), prevHueCycle(millis()) {
}

void LedController::init() {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

    dateTime = {};
    dateTime.init();

    currentTimeState = dateTime.getTimeState();
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

    leds[start].r = nextColor.r;
    leds[start].g = nextColor.g;
    leds[start].b = nextColor.b;
}

void LedController::setAll(LedController::RGB color) {
    for (auto &led : leds) {
        led.r = color.r;
        led.g = color.g;
        led.b = color.b;
    }
}

void LedController::flash() {
    for (int i = 0; i < 30; i++) {
        setAll({255, 255, 255});
        delay(1000);
        setAll({0, 0, 0});
        delay(1000);
    }
}

void LedController::turnOff() {
    setAll({0, 0, 0});
}

std::vector<LedController::RGB> LedController::activationFunction(bool inverse) const {
    LedController::RGB baseColor = {255, 255, 255};

    int steps = 255;

    double tim;
    if (inverse) {
        tim = 1 - t;
    } else {
        tim = t;
    }

    double ix = steps * NUM_LEDS * tim;

    auto val = floor(steps * tim);
    auto mod = static_cast<int>(ix) % NUM_LEDS;

    std::vector<LedController::RGB> out;
    for (int i = 0; i < NUM_LEDS; i++) {
        auto outMult = (val + (i < mod)) / steps;
        auto outR = static_cast<int>(baseColor.r * outMult);
        auto outG = static_cast<int>(baseColor.g * outMult);
        auto outB = static_cast<int>(baseColor.b * outMult);

        out.push_back({outR, outG, outB});
    }

    return out;
}

void LedController::fadeIn() {
    Serial.println("FadeIn");

    auto out = activationFunction();
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].r = out[i].r;
        leds[i].g = out[i].g;
        leds[i].b = out[i].b;
    }
}

void LedController::fadeOut() {
    Serial.println("FadeOut");

    auto out = activationFunction(true);
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].r = out[i].r;
        leds[i].g = out[i].g;
        leds[i].b = out[i].b;
    }
}

void LedController::cycleHue() {
    unsigned long hueTimeStep = 200;
    if ((millis() - prevHueCycle) > hueTimeStep) {
        auto next = nextHueColor();
        cycle(next, 0, NUM_LEDS - 1);
        prevHueCycle = millis();
    }
}

void LedController::updateTimeState() {
    auto newState = dateTime.getTimeState();
    t = dateTime.progress;

    if (newState != currentTimeState) {
        currentTimeState = newState;

        switch (currentTimeState) {

            case DateTime::MORNING:
            {
                currentColorTimer = {0, 0, 0};
            } break;

            case DateTime::DAY:
            {
                prevHueCycle = millis();
            } break;

            case DateTime::SCHOOL:
            {
                turnOff();
            }

            case DateTime::EVENING:
            {
                currentColorTimer = {255, 255, 255};
            } break;
            case DateTime::NIGHT:
            {
                turnOff();
            } break;
        }
    }
}

void LedController::step() {

    updateTimeState();

    switch (currentTimeState) {

        case DateTime::MORNING:
        {
            fadeIn();
        } break;

        case DateTime::DAY:
        {
            cycleHue();
        } break;

        case DateTime::EVENING:
        {
            fadeOut();
        } break;
    }

    FastLED.show();
}

void LedController::fastLedShow() {
    FastLED.show();
}