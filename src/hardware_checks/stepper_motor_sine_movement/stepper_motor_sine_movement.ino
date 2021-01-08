/*
  @author Tom Johnson, Harrison Outram
  Date: 26/09/2019
  Editor: Ashley, Harrison Outram
  Last Updated: 6 Aug 2020
  Organisation: Curtin Robotics Club (CRoC)
  Project: Climbing Clock (2019)
  Purpose: example program to control stepper motors in sine movement
*/

#define DIR_PIN 2 // Direction
#define STEP_PIN 3 // Step
#define ENABLE_PIN 4 // enable

#define CLOCKWISE HIGH
#define ANTI_CLOCK LOW

#define PI 3.14f
#define OFF_TIME 3 // time in seconds motor is turned off

float angle = 0.0f;
unsigned int freq;
bool enabled = true, direction = CLOCKWISE;

void setup() {
  pinMode(DIR_PIN, OUTPUT); digitalWrite(DIR_PIN, HIGH);
  pinMode(STEP_PIN, OUTPUT); digitalWrite(STEP_PIN, HIGH);
  pinMode(ENABLE_PIN, OUTPUT); digitalWrite(ENABLE_PIN, LOW);

  // set microstep to full-step
  pinMode(8, OUTPUT); digitalWrite(8, LOW);
  pinMode(9, OUTPUT); digitalWrite(9, LOW);
  pinMode(10, OUTPUT); digitalWrite(10, LOW);

  Serial.begin(9600);
}

void loop() {
  if (enabled) {
    Serial.print(F("Setting direction to "));

    if (sin(angle) > 0.0) {
      direction = CLOCKWISE;
      Serial.println(F("clockwise"));
    } else {
      direction = ANTI_CLOCK;
      Serial.println(F("anti-clockwise"));
    }
    digitalWrite(DIR_PIN, direction);

    freq = (unsigned int)(1000.0 * fabs(sin(angle)));
    Serial.print(F("Setting frequency to ")); Serial.println(freq);
    tone(STEP_PIN, freq);

    angle += 0.001f;

    if (angle > 4.0f * PI) {
      angle = 0.0f;
      digitalWrite(ENABLE_PIN, HIGH);
      Serial.print(F("Turning off stepper motor driver for "));
      Serial.print(OFF_TIME); Serial.prinln(F(" seconds"));
      enabled = false;
    }
  } else {
    delay(OFF_TIME * 1000);
    Serial.println(F("Turning on stepper motor driver"));
    enabled = true;
  }
}
