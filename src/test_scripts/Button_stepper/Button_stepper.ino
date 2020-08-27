/*
 * @author Alex MacKerron, Harrison Outram
 * Date: 27 Aug 2020
 * @brief test script for ensuring stepper motor works
 *        requires stepper motor driver
 */

#define dirPin 3  //Direction pin for stepper motor
#define stepPin 4  //Step pin for stepper motor
#define buttonPin 2  //Button pin for turning stepper motor driver on/off
#define enablePin 4 // pin for turning stepper motor driver on/off

#define CLOCKWISE HIGH
#define ANTI_CLOCK LOW

#define PI 3.14f
#define DEBOUNCE_TIME 100 // debounce time for button in milliseconds

float angle = 0.0f;
unsigned int freq;
volatile unsigned long prevButtonPress = 0;
volatile bool enabled = false;
bool direction = CLOCKWISE;

int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), toggleStepperMotorDriver,
                  RISING);

  Serial.begin(9600);
  Serial.println(F("Press button to start..."));
}

void loop() {
  if (enabled){
    digitalWrite(enablePin, LOW); // turn stepper motor driver on
    Serial.print(F("setting direction to "));

    if (sin(angle) > 0.0) {
      direction = CLOCKWISE;
      Serial.println(F("clockwise"));
    } else {
      direction = ANTI_CLOCK;
      Serial.println(F("anti-clockwise"));
    }
    digitalWrite(dirPin, direction);

    freq = (unsigned int)(1000.0 * fabs(sin(angle)));
    Serial.print(F("Setting frequency to ")); Serial.println(freq);
    tone(stepPin, freq);

    angle += 0.001f;

    if (angle > 4.0f * PI)
      angle = 0.0f;
  } else {
    angle = 0.0f;
    digitalWrite(enablePin, HIGH); // turn stepper motor driver off
    // wait for user to press button
  }
}

void toggleStepperMotorDriver(void) {
  if (millis() - prevButtonPress > DEBOUNCE_TIME) {
    enabled = !enabled;
    prevButtonPress = millis();
  }
}