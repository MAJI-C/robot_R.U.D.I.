// c1.4 One motor through the L298N: forward, stop, reverse, stop
const int IN1_PIN = 7;
const int IN2_PIN = 8;

void setup() {
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
}

void loop() {
  digitalWrite(IN1_PIN, HIGH);   // one direction
  digitalWrite(IN2_PIN, LOW);
  delay(2000);

  digitalWrite(IN1_PIN, LOW);    // stop
  digitalWrite(IN2_PIN, LOW);
  delay(1000);

  digitalWrite(IN1_PIN, LOW);    // other direction
  digitalWrite(IN2_PIN, HIGH);
  delay(2000);

  digitalWrite(IN1_PIN, LOW);    // stop
  digitalWrite(IN2_PIN, LOW);
  delay(3000);
}