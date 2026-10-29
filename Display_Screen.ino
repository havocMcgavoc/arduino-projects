#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS  0x3C

unsigned long previous_time = 0;

Adafruit_SH1106G display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

void setup() {
  Wire.begin(21, 22);
  display.begin(OLED_ADDRESS, true);

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
}

void loop() {
  unsigned long current_time = millis();
  if (current_time - previous_time >= 1000){
    previous_time = current_time;
    display.clearDisplay();
    display.setCursor(0, 32);
    display.print(current_time / 1000);
    display.print(" seconds has passed");
    display.print(" since startup");
    display.display();
  }
}