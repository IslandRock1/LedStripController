#include <Arduino.h>
#include <FastLed.h>

#include "LedController.hpp"

#define NUM_LEDS 60
#define DATA_PIN 33
CRGB leds[NUM_LEDS];
CRGB crgb;

LedController controller;

void cycle(int start, int end) {
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
}

void setup() {
    delay(3000); // To protect from to much power consumption??

    controller = LedController();
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {

    auto midLeft = NUM_LEDS / 2;
    auto midRight = midLeft + 1;

    auto next = controller.nextHueColor();

    leds[midLeft] = crgb.setRGB(next.r, next.g, next.b);;
    leds[midRight] = crgb.setRGB(next.r, next.g, next.b);

    cycle(midLeft, 0);
    cycle(midRight, NUM_LEDS);

    delay(10);

}