#ifndef _NTN_APP_H_
#define _NTN_APP_H_
    #include <Arduino.h>
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>
    #include <Adafruit_GFX.h>
    #include <Adafruit_NeoMatrix.h>
    #include <Adafruit_NeoPixel.h>
    #include <RTClib.h>
    #include "NTN_Matrix_Ws2812.h"
    #include "NTN_Printf.h"
    void NTN_APP_Int();
    void NTN_APP_Handler();
#endif