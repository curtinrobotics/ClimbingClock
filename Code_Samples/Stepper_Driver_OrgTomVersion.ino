/*
  Author: Some bloke named "blueicesparks" ??????
  Date: ????
  Organisation: Curtin Robotics Club (CRoC)
  Project: Climbing Clock (2019)
  Purpose: Stepper motor controller thingy ????
*/

#define DIR 2 // Direction? directory? Dirac? What is this???
#define STEP 3
#define _EN 4 // Encoder? Envelope? Enormous Nob? Again, what is this???

void setup() {
  pinMode(2, OUTPUT); digitalWrite(2, HIGH);
  pinMode(3, OUTPUT); digitalWrite(2, HIGH);
  pinMode(8, OUTPUT); digitalWrite(8, LOW);
  pinMode(9, OUTPUT); digitalWrite(9, LOW);
  pinMode(10, OUTPUT); digitalWrite(10, LOW);
  pinMode(4, OUTPUT); digitalWrite(4, LOW);
}

float f = 0.0; // You have very weird naming standards blueicesparks

void loop() {
  digitalWrite(DIR, sin(f) > 0 ? HIGH : LOW);
  tone(STEP, 1000 * fabs(sin(f)));
  f += 0.001;
  
  if (f > 10.0) {
    f = 0.0;
    digitalWrite(_EN, digitalRead(_EN) ? LOW : HIGH );
  }
}
