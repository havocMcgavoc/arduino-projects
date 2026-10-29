#include <Adafruit_GFX.h>
#include <Wire.h>

#define trig 18
#define echo 19
#define OLED_ADDRESS 0x3C
#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128

Adafruit_SH1106G display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
)

void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Wire.begin(21, 22);
  display.begin(OLED_ADDRESS, true);
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);

}

void loop() {
  // put your main code here, to run repeatedly:
  float distance = getDistance();
  display.clearDisplay();
  display.setCursor(0, 32);
  display.print(distance);
  display.print(" cm away.");
  display.display();
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