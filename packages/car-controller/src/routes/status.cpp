#include "routes/status.h"
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

void setupStatusRoutes(AsyncWebServer &server) {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response =
        request->beginResponseStream("application/json");
    DynamicJsonDocument json(1024);
    // Add your status data to the JSON object
    json["status"] = "OK";
    serializeJson(json, *response);
    request->send(response);
  });
}
