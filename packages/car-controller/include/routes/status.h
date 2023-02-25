#ifndef STATUS_H
#define STATUS_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

void setupStatusRoutes(AsyncWebServer &server);

#endif
