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

// Webserver
AsyncWebServer server(80);

void setMotor(int pin1, int pin2, String state)
{
  if (state == "FORWARD")
  {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    Serial.println("IN FW");
  }
  else if (state == "BACKWARD")
  {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    Serial.println("IN BW");
  }
  else
  {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    Serial.println("IN STP");
  }
}

const int A1A = 5;
const int A1B = 15;
const int B1A = 18;
const int B1B = 19;

const int A2A = 13;
const int A2B = 12;
const int B2A = 27;
const int B2B = 26;

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
                setMotor(A1A, A1B, m1);
              }
              if (request->hasParam("m2"))
              {
                String m2 = request->getParam("m2")->value();
                setMotor(B1A, B1B, m2);
  
              }
              if (request->hasParam("m3"))
              {
                String m3 = request->getParam("m3")->value();
                setMotor(A2A, A2B, m3);
              }
              if (request->hasParam("m4"))
              {
                String m4 = request->getParam("m4")->value();
                setMotor(B2A, B2B, m4);
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
