
#include <Servo.h>

// -------------------- Ultrasonic sensor --------------------

const int TRIG_PIN = A0;
const int ECHO_PIN = A1;

// -------------------- Servos --------------------

const int HORIZONTAL_PIN = 10;
const int VERTICAL_PIN = 4;

Servo horizontalServo;
Servo verticalServo;

// -------------------- Motors --------------------

const int IN1_PIN = 7;    // Motor A
const int IN2_PIN = 8;
const int IN3_PIN = 11;   // Motor B
const int IN4_PIN = 12;

// -------------------- Scanning --------------------

int angles[] = {60, 70, 80, 90, 100, 110, 120};

const int COUNT = sizeof(angles) / sizeof(angles[0]);

float distances[COUNT];

const float OBSTACLE_DISTANCE = 20.0;
const float CLEAR_DISTANCE = 25.0;

// -------------------- Ultrasonic measurement --------------------

float measureDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);

  if (duration == 0) {
    return -1.0;
  }

  return duration * 0.0343 / 2.0;
}

// -------------------- Scanning --------------------

float scanDirection(int angle) {

  horizontalServo.write(angle);
  delay(500);

  return measureDistance();
}

void scanEnvironment(float distances[], int angles[], int count) {

  for (int i = 0; i < count; i++) {

    distances[i] = scanDirection(angles[i]);

    Serial.print("Angle: ");
    Serial.print(angles[i]);

    Serial.print(" Distance: ");
    Serial.println(distances[i]);
  }
}

int chooseDirection(float distances[], int angles[], int count) {

  float maxDistance = -1.0;
  int bestAngle = -1;

  for (int i = 0; i < count; i++) {

    if (distances[i] > maxDistance &&
        distances[i] > CLEAR_DISTANCE) {

      maxDistance = distances[i];
      bestAngle = angles[i];
    }
  }

  return bestAngle;
}

// -------------------- Motor control --------------------

void setMotorA(bool a1, bool a2) {

  digitalWrite(IN1_PIN, a1);
  digitalWrite(IN2_PIN, a2);
}

void setMotorB(bool b1, bool b2) {

  digitalWrite(IN3_PIN, b1);
  digitalWrite(IN4_PIN, b2);
}

void moveForward() {

  setMotorA(HIGH, LOW);
  setMotorB(HIGH, LOW);
}

void stopMotors() {

  setMotorA(LOW, LOW);
  setMotorB(LOW, LOW);
}

void turnLeft() {

  setMotorA(LOW, HIGH);
  setMotorB(HIGH, LOW);
}

void turnRight() {

  setMotorA(HIGH, LOW);
  setMotorB(LOW, HIGH);
}

void reverseMotors() {

  setMotorA(LOW, HIGH);
  setMotorB(LOW, HIGH);
}

// -------------------- Obstacle recovery --------------------

void recoverFromObstacle() {

  Serial.println("Obstacle detected");

  stopMotors();
  delay(200);

  // Reverse away from the obstacle
  reverseMotors();
  delay(1000);

  stopMotors();
  delay(200);

  // Scan the surroundings
  scanEnvironment(distances, angles, COUNT);

  // Select the clearest direction
  int bestAngle = chooseDirection(distances, angles, COUNT);

  if (bestAngle == -1) {

    Serial.println("No clear direction found");

    horizontalServo.write(90);
    stopMotors();

    return;
  }

  Serial.print("Selected angle: ");
  Serial.println(bestAngle);

  // Turn towards the selected direction
  if (bestAngle < 90) {

    turnLeft();
    delay(500);

  }
  else if (bestAngle > 90) {

    turnRight();
    delay(500);

  }
  else {

    // Best direction is straight ahead
    stopMotors();
  }

  stopMotors();

  // Return sensor to centre
  horizontalServo.write(90);
  delay(500);
}

// -------------------- Setup --------------------

void setup() {

  Serial.begin(9600);

  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);

  stopMotors();

  horizontalServo.attach(HORIZONTAL_PIN);
  verticalServo.attach(VERTICAL_PIN);

  horizontalServo.write(90);
  verticalServo.write(90);

  delay(1000);

  Serial.println("Robot ready");
}

// -------------------- Main loop --------------------

void loop() {

  float cm = measureDistance();

  Serial.print("Front distance: ");
  Serial.println(cm);

  if (cm < 0) {

    // Invalid ultrasonic reading
    stopMotors();

  }
  else if (cm < OBSTACLE_DISTANCE) {

    // Obstacle detected
    recoverFromObstacle();

  }
  else if (cm > CLEAR_DISTANCE) {

    // Path is clear
    moveForward();

  }
  else {

    // Caution zone: stop
    stopMotors();

  }

  delay(200);
}
