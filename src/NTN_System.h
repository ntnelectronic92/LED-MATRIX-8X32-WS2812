#ifndef _NTN_SYSTEM_H_
#define _NTN_SYSTEM_H_
    #include <Arduino.h>
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>
    #include <Adafruit_GFX.h>
    #include <Adafruit_NeoMatrix.h>
    #include <Adafruit_NeoPixel.h>
    #include <RTClib.h>
    #include "NTN_Printf.h"
    #include "NTN_DS3231_Clock.h"
    void NTN_System_Int();
    void NTN_System_Handler();
#endif