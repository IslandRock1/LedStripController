#include <Arduino.h>
#include <FastLed.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

#include "internetAccess.hpp"
#include "LedController.hpp"

#define NUM_LEDS 432
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
    delay(3000); // To protect from too much power consumption??

    controller = LedController();
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

    Serial.begin(9600); // Not used when wireless

    WiFi.begin(internetSSID, internetPassword);

    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
    }

    ArduinoOTA.begin();
}

void loop() {

    ArduinoOTA.handle();

    auto midLeft = NUM_LEDS / 2;
    auto midRight = midLeft + 1;

    auto next = controller.nextHueColor();

    leds[midLeft] = crgb.setRGB(next.r, next.g, next.b);;
    leds[midRight] = crgb.setRGB(next.r, next.g, next.b);

    cycle(midLeft, 0);
    cycle(midRight, NUM_LEDS);

    FastLED.show();

    delay(10);

}