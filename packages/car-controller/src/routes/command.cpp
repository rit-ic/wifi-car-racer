#include "routes/command.h"
#include "main.h"

void setupCommandRoutes(AsyncWebServer &server) {
  server.on("/command", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("m1")) {
      String m1 = request->getParam("m1")->value();
      setMotor(A1A, A1B, m1, atoi(request->getParam("speed")->value().c_str()));
    }
    if (request->hasParam("m2")) {
      String m2 = request->getParam("m2")->value();
      setMotor(B1A, B1B, m2, atoi(request->getParam("speed")->value().c_str()));
    }
    if (request->hasParam("m3")) {
      String m3 = request->getParam("m3")->value();
      setMotor(A2A, A2B, m3, atoi(request->getParam("speed")->value().c_str()));
    }
    if (request->hasParam("m4")) {
      String m4 = request->getParam("m4")->value();
      setMotor(B2A, B2B, m4, atoi(request->getParam("speed")->value().c_str()));
    }
    // delayMillis = atoi(delay.c_str());

    request->send(200, "text/plain", "Success from server");
  });
}
