#ifndef INDEX_H
#define INDEX_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

void setupIndexRoutes(AsyncWebServer &server);

#endif
