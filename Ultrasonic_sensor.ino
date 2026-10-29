#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Adafruit_SH110X.h>

#define trig 9
#define echo 10
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SH1106G display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Wire.begin();
  display.begin(OLED_ADDRESS, true);
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(2);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float distance = getDistance();
  display.clearDisplay();
  display.setCursor(0, 32);
  if (distance <= 30) {
    display.print(distance, 1);
    display.print(" cm");
    display.display();
    Serial.print(distance, 1);
    Serial.println(" cm");
  }
  else {
    display.print("30+ cm");
    display.display();
    Serial.println("30+ cm");
  }
  delay(100);
}

float getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH);
  float d = (duration*0.0343)/2;
  return d;
}
