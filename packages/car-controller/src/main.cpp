#include "main.h"
#include "routes/command.h"
#include "routes/index.h"
#include "routes/status.h"

#include <Arduino.h>
#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <LittleFS.h>
#include <WiFi.h>

const int A1A = 33;
const int A1B = 32;
const int B1A = 25;
const int B1B = 26;
const int A2A = 19;
const int A2B = 21;
const int B2A = 23;
const int B2B = 22;

const char *ssid = "hello";
const char *password = "hello1234";

unsigned long currentMillis = millis();

AsyncWebServer server(80);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);
  pinMode(A2A, OUTPUT);
  pinMode(A2B, OUTPUT);
  pinMode(B2A, OUTPUT);
  pinMode(B2B, OUTPUT);

  Serial.begin(115200);
  Serial.println("Starting the LittleFS Webserver..");

  // Begin LittleFS
  if (!LittleFS.begin()) {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  WiFi.softAP(ssid, password);
  MDNS.begin("car");

  // Serve static React page
  setupIndexRoutes(server);

  // Define other endpoints
  setupCommandRoutes(server);
  setupStatusRoutes(server);

  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
  });

  server.begin();
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
