#ifndef COMMAND_H
#define COMMAND_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "motor.h"

void setupCommandRoutes(AsyncWebServer &server);

#endif
