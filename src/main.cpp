#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

#include "internetAccess.hpp"
#include "LedController.hpp"

LedController controller;

void setup() {
    delay(3000); // To protect from too much power consumption??

    Serial.begin(115200);
    Serial.println();
    Serial.println("Serial established.");

    WiFi.begin(internetSSID, internetPassword);

    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
    }

    Serial.println("Wifi connected.");

    controller.init();
    ArduinoOTA.begin();
}

void loop() {
    ArduinoOTA.handle();
    controller.step();
}