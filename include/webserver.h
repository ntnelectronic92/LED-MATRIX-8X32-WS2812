#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Arduino.h>
#include <ESP8266WebServer.h>

void init_WebServer(void);
void WebServer_CallHTML(void);
void WebServer_Update(void);
void WebServer_Handle(void);

#endif // WEBSERVER_H