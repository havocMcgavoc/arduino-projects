#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SH1106G display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

unsigned long starttime;
int currentline = 0;
unsigned long songtime;

const String lyrics[] = {
  "Her love is in your  head",
  "you lost your        earrings in her bed",
  "You couldn't tell her you lost 'em", 
  "'cause you're scared and you're not       talking",
  "so you think of what to say",
  "then save it for     another day",
  "'cause you just never had the heart",
  "now they just drift  further apart"
};

unsigned long timestamps[] = {
  1030,
  2960,
  6360,
  9410,
  12490,
  15330,
  18520,
  21570
};

void setup() {
  // put your setup code here, to run once:
starttime = millis();

Wire.begin(21, 22);
display.begin(OLED_ADDRESS, true);

display.setTextSize(1);
display.setTextColor(SH110X_WHITE);
}

void loop() {
  // put your main code here, to run repeatedly:
unsigned long currenttime = millis();
songtime = currenttime - starttime;
if (currentline < 8 && songtime >= timestamps[currentline]) {
  display.clearDisplay();
  display.setCursor(0,16);
  display.print(lyrics[currentline]);
  display.display();
  currentline++;
}
}