#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "motor.h"

const char *ssid = "hello";
const char *password = "hello1234";

unsigned long currentMillis = millis();

AsyncWebServer server(80);

const int A1A = 33;
const int A1B = 32;
const int B1A = 25;
const int B1B = 26;

const int A2A = 19;
const int A2B = 21;
const int B2A = 23;
const int B2B = 22;

int speed = 51;

void setup()
{
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
  if (!LittleFS.begin())
  {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  // Connect to WIFI
  WiFi.softAP(ssid, password);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
  // if (WiFi.waitForConnectResult() != WL_CONNECTED)
  // {
  //   Serial.printf("WiFi Failed!\n");
  //   return;
  // }


  // Route for root index.html
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/index.html", "text/html"); });

  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/index.html", "text/html"); });

  // Route for root index.css
  server.on("/app.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/app.css", "text/css"); });

  // Route for root index.js
  server.on("/app.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/app.js", "text/javascript"); });

  // Respond to toggle event
  server.on("/command", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              if (request->hasParam("m1"))
              {
                String m1 = request->getParam("m1")->value();
                setMotor(A1A, A1B, m1, atoi(request->getParam("speed")->value().c_str()));
              }
              if (request->hasParam("m2"))
              {
                String m2 = request->getParam("m2")->value();
                setMotor(B1A, B1B, m2, atoi(request->getParam("speed")->value().c_str()));
              }
              if (request->hasParam("m3"))
              {
                String m3 = request->getParam("m3")->value();
                setMotor(A2A, A2B, m3, atoi(request->getParam("speed")->value().c_str()));
              }
              if (request->hasParam("m4"))
              {
                String m4 = request->getParam("m4")->value();
                setMotor(B2A, B2B, m4, atoi(request->getParam("speed")->value().c_str()));
              }

                // delayMillis = atoi(delay.c_str());

              request->send(200, "text/plain", "Success from server"); });

  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              AsyncResponseStream *response = request->beginResponseStream("application/json");
              DynamicJsonDocument json(1024);
              // json["led1"] = digitalRead(LED_PIN_1)==LOW;
              // json["led2"] = digitalRead(LED_PIN_2)==LOW;
              // json["blinking"] = blinking;
              // json["delay"] = delayMillis;
              // json["together"] = together;
              serializeJson(json, *response);
              request->send(response); });

  server.onNotFound([](AsyncWebServerRequest *request)
                    { request->send(404, "text/plain", "Not found"); });

  server.begin();
}

void loop()
{
}
