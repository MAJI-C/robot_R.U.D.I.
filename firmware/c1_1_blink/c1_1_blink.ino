// c1.1 Blink: fast blink, to tell it apart from the factory sketch
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // on-board LED "L", pin 13
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
}