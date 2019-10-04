/*
  Author: Tom Johnson
  Date: 26/09/2019
  Organisation: Curtin Robotics Club (CRoC)
  Project: Climbing Clock (2019)
  Purpose: To control the stepper motors for the Climbing Clock
*/

#define DIR 2 // Direction
#define STEP 3 // Step
#define _EN 4 // Encoder

void setup() {
  pinMode(2, OUTPUT); digitalWrite(2, HIGH);
  pinMode(3, OUTPUT); digitalWrite(2, HIGH);
  pinMode(8, OUTPUT); digitalWrite(8, LOW);
  pinMode(9, OUTPUT); digitalWrite(9, LOW);
  pinMode(10, OUTPUT); digitalWrite(10, LOW);
  pinMode(4, OUTPUT); digitalWrite(4, LOW);
}

float duration = 0.0;

void loop() {
  digitalWrite(DIR, sin(duration) > 0 ? HIGH : LOW);
  tone(STEP, 1000 * fabs(sin(duration)));
  duration += 0.001;
  
  if (duration > 10.0) {
    duration = 0.0;
    digitalWrite(_EN, digitalRead(_EN) ? LOW : HIGH );
  }
}
