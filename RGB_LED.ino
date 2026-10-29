#define red 13
#define green 11
#define blue 10

void setup() {
  // put your setup code here, to run once:
pinMode(red, OUTPUT);
pinMode(green, OUTPUT);
pinMode(blue, OUTPUT);
pinMode(12, OUTPUT);
digitalWrite(12, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(red, HIGH);
delay(500);
digitalWrite(red, LOW);
digitalWrite(green, HIGH);
delay(500);
digitalWrite(green, LOW);
digitalWrite(blue, HIGH);
delay(500);
digitalWrite(blue, LOW);
}
