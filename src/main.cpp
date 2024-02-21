#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

#include "internetAccess.hpp"
#include "LedController.hpp"

LedController controller;

void setup() {
    delay(3000); // To protect from too much power consumption??

    controller = LedController();

    Serial.begin(9600); // Not used when wireless

    WiFi.begin(internetSSID, internetPassword);

    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
    }

    ArduinoOTA.begin();
}

void loop() {

    ArduinoOTA.handle();
    controller.step();
}