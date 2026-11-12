// c2.1 Both motors: forward, stop, reverse, stop
const int IN1_PIN = 7;    // motor A
const int IN2_PIN = 8;
const int IN3_PIN = 11;   // motor B
const int IN4_PIN = 12;

void setMotors(bool a1, bool a2, bool b1, bool b2) {
  digitalWrite(IN1_PIN, a1);
  digitalWrite(IN2_PIN, a2);
  digitalWrite(IN3_PIN, b1);
  digitalWrite(IN4_PIN, b2);
}

void setup() {
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  setMotors(LOW, LOW, LOW, LOW);
}

void loop() {
  setMotors(HIGH, LOW, HIGH, LOW);   // both one way
  delay(2000);
  setMotors(LOW, LOW, LOW, LOW);     // stop
  delay(1000);
  setMotors(LOW, HIGH, LOW, HIGH);   // both the other way
  delay(2000);
  setMotors(LOW, LOW, LOW, LOW);     // stop
  delay(3000);
}