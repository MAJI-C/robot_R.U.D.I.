
#include <Servo.h>

Servo horizontalServo;
Servo verticalServo;

const int HORIZONTAL_PIN = 10;
const int VERTICAL_PIN = 4;

void setup() {
  horizontalServo.attach(HORIZONTAL_PIN);
  verticalServo.attach(VERTICAL_PIN);

  // Start at the centre
  horizontalServo.write(90);
  verticalServo.write(90);

  delay(1000);
}

void loop() {

  // Move both servos forward
  for (int angle = 60; angle <= 120; angle += 1) {

    horizontalServo.write(angle);
    verticalServo.write(angle);

    delay(30);
  }

  // Move both servos backward
  for (int angle = 120; angle >= 60; angle -= 1) {

    horizontalServo.write(angle);
    verticalServo.write(angle);

    delay(30);
  }

}
