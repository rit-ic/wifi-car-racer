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

// Replace with your network credentials
// const char *ssid = "ALHN-5934";
// const char *password = "tZvGJ8Xw42";
const char *ssid = "hello";
const char *password = "hello1234";

unsigned long currentMillis = millis();
boolean blinking = false;
boolean together = false;
int step = 0;
unsigned long delayMillis = 1000;

// Webserver
AsyncWebServer server(80);

const int LED_PIN_1 = 2;
const int LED_PIN_2 = 12;

void toggleLED(String status, int pin)
{
  if (status == "ON")
    digitalWrite(pin, HIGH);
  else
    digitalWrite(pin, LOW);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting the LittleFS Webserver..");

  // Begin LittleFS
  if (!LittleFS.begin())
  {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  // Connect to WIFI
  // WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid, password);
  IPAddress ip = WiFi.softAP(ssid, password);
  // if (WiFi.waitForConnectResult() != WL_CONNECTED)
  // {
  //   Serial.printf("WiFi Failed!\n");
  //   return;
  // }

  Serial.print("IP Address: ");
  Serial.println(ip);

  // LED PIN
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  digitalWrite(LED_PIN_1, HIGH);
  digitalWrite(LED_PIN_2, HIGH);

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
              if (request->hasParam("pin"))
              {
                String pin = request->getParam("pin")->value();
                String value = request->getParam("value")->value();
                toggleLED(value, pin == "0" ? LED_PIN_1 : LED_PIN_2);
              }

              if (request->hasParam("blink"))
              {
                String blink = request->getParam("blink")->value();
                blinking = blink == "ON";
              }

              if (request->hasParam("delay"))
              {
                String delay = request->getParam("delay")->value();
                delayMillis = atoi(delay.c_str());
              }

              if (request->hasParam("together"))
              {
                String reqtogether = request->getParam("together")->value();
                together = reqtogether == "true";
              }

              request->send(200, "text/plain", "Success from server"); });

  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              AsyncResponseStream *response = request->beginResponseStream("application/json");
              DynamicJsonDocument json(1024);
              json["led1"] = digitalRead(LED_PIN_1)==LOW;
              json["led2"] = digitalRead(LED_PIN_2)==LOW;
              json["blinking"] = blinking;
              json["delay"] = delayMillis;
              json["together"] = together;
              serializeJson(json, *response);
              request->send(response); });

  server.onNotFound([](AsyncWebServerRequest *request)
                    { request->send(404, "text/plain", "Not found"); });

  server.begin();
}

void loop()
{
  if (millis() - currentMillis > delayMillis)
  {
    currentMillis = millis();
    if (blinking)
    {
      if (step == 0)
      {
        step = 1;
        toggleLED("OFF", LED_PIN_1);
        toggleLED(together ? "OFF" : "ON", LED_PIN_2);
      }
      else
      {
        step = 0;
        toggleLED("ON", LED_PIN_1);
        toggleLED(together ? "ON" : "OFF", LED_PIN_2);
      }
    }
  }
}