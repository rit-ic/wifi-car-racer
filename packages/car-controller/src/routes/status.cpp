#include "routes/status.h"
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_VL53L0X.h>
#include "main.h"

void setupStatusRoutes(AsyncWebServer &server) {
  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

    AsyncResponseStream *response =
        request->beginResponseStream("application/json");
    DynamicJsonDocument json(1024);
    // Add your status data to the JSON object
    json["milimeters"] = measure.RangeMilliMeter;
    serializeJson(json, *response);
    request->send(response);
  });
}