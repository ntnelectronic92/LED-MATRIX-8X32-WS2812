#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Preferences.h>
#include "matrix.h"
#include "webserver.h"
#include "userdata.h"

void setup()
{
  Serial.begin(115200);
  init_UserData();
  init_Matrix_Ws2812();
  init_WebServer();
}

void loop()
{
  WebServer_Handle();
  Matrix_Ws2812_Handle();
}