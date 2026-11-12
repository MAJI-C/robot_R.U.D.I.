// c1.2 HC-SR04 distance to Serial Monitor intended to measure distance 
// and display it on the Serial Monitor.


// TRIG is a variable representing the Arduino pin 
// connected to the sensor's trigger input.

// assigning pins
const int TRIG_PIN = A0;
const int ECHO_PIN = A1;

// The HC-SR04 sensor works by sending out an ultrasonic pulse 
// when the trigger pin is set HIGH for at least 10 microseconds.
// setup() executes once when the Arduino starts or resets.
// loop() executes repeatedly after setup() has finished.
// void means this function does not return a value.
void setup() {
  Serial.begin(9600);
  // pinMode() is an Arduino function that sets a pin to either INPUT or OUTPUT.
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
}

void loop() {
  // 10 microsecond trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  // wait 2 microseconds to settle 
  delayMicroseconds(2);
  // approximately 5 V on a standard 5 V Uno
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // echo time in microseconds; 0 means no echo within 30 ms
  // 30 ms is the maximum time for an object at 5 m (500 cm)
  // pulseIn() returns an unsigned long, which is a 32-bit integer
  // pulseIn() is an Arduino function that measures how long a pin remains in a specified state.
  // unsigned long: a variable type that stores a non-negative integer over a large range.
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);

  if (duration == 0) {
    Serial.println("no echo");
  } else {
    float cm = duration * 0.0343 / 2.0;   // speed of sound in air, there and back
    Serial.print(cm, 1);
    Serial.println(" cm");
  }
  delay(200);
}