#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Wire.h>
#include <WiFi.h>
#include <time.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Credentials.h"

HTTPClient http;

#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128
#define OLED_ADDRESS 0x3C

const int sda = 21;
const int scl = 22;
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
String apiKey = API_KEY;
const char* days[] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};
String url = "https://api.openweathermap.org/data/2.5/weather?q=Bengaluru&appid=" + String(apiKey) + "&units=metric";

struct tm timeInfo;

Adafruit_SH1106G display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

void setup() {
  // put your setup code here, to run once:
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  configTime(19800, 0, "pool.ntp.org");

  Wire.begin(sda, scl);
  display.begin(OLED_ADDRESS, true);
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);

}

unsigned long previous_time = 0;
bool firstRun = true;
float temp;
int humidity;

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long current_time = millis();

  display.clearDisplay();
  if(firstRun || current_time-previous_time >= 60000) {
    http.begin(url);
    int httpCode = http.GET();
    if(httpCode == 200) {
      String response = http.getString();

      JsonDocument doc;
      deserializeJson(doc, response);

      temp = doc["main"]["temp"];
      humidity = doc["main"]["humidity"];
      
      previous_time = current_time;;
      firstRun = false;
      http.end();
      
    }
  }
  display.setCursor(0,0);
  display.print("Temp: "+String(temp)+" C");
  display.setCursor(0,15);
  display.print("humidity: "+String(humidity)+"%");

  getLocalTime(&timeInfo);
  int hour = timeInfo.tm_hour;
  int min = timeInfo.tm_min;
  int s = timeInfo.tm_sec;
  String day = days[timeInfo.tm_wday];
  
  display.setCursor(0,30);
  display.print(String(hour)+":"+String(min)+":"+String(s));
  display.setCursor(0,45);
  display.print("Day: "+ day);
  display.display();
  delay(1000);
}