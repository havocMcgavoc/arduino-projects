int led[] = {8, 9, 10, 11, 12, 13};

void setup() {
  // put your setup code here, to run once:
for (int i = 0; i < 6; i++) {
  pinMode(led[i], OUTPUT);
}
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
for (int i = 0; i < 6; i++) {
  digitalWrite(led[i], HIGH);
  Serial.print("Turning on LED ");
  Serial.println(i + 1);
  delay(250);
}
for (int i = 0; i < 6; i++) {
  digitalWrite(led[i], LOW);
  Serial.print("Turning off LED ");
  Serial.println(i + 1);
  delay(250);
}
}