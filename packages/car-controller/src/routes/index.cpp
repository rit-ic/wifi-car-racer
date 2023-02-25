#include "routes/index.h"

void setupIndexRoutes(AsyncWebServer &server) {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/index.html", "text/html");
  });

  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/index.html", "text/html");
  });

  server.on("/app.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/app.css", "text/css");
  });

  server.on("/app.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/app.js", "text/javascript");
  });
}