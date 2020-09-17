/*
 * @author Alex MacKerron, Harrison Outram
 * @brief Example program to test stepper motor and stepper motor driver works
 */

#define dirPin 6
#define stepPin 5
#define buttonPin 2
#define enablePin 4

enum Modes {OFF, ST_HIGH, ST_LOW, TONE};

#define FREQ 1000U

int buttonState = 0;
volatile int mode = 0;
int prevMode = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), toggleStepperMotorDriver, 
                  RISING);
  digitalWrite(dirPin, HIGH);
  Serial.begin(9600);
}

void loop() {
  if (mode == OFF) {
    digitalWrite(enablePin, HIGH);
    if (prevMode != mode)
      Serial.println("Push button to turn on");
  }
  if (mode == ST_HIGH) {
    digitalWrite(stepPin, HIGH);
    digitalWrite(enablePin, LOW);
    if (prevMode != mode){
      Serial.println("Motor is on HIGH.");
    }
  }
  if (mode == ST_LOW) {
    digitalWrite(stepPin, LOW);
    if (prevMode != mode) {
      Serial.println("Motor is on LOW");
    }
  }
  if (mode == TONE) {
    digitalWrite(enablePin, LOW);
    tone(stepPin, FREQ);
    if (prevMode != mode) {
      Serial.println("Motor is at a set frequency");
    }
  }
  if (mode > 3) {
    mode = 0;
    noTone(stepPin);
  }

  if (prevMode != mode)
    prevMode = mode;
}

void toggleStepperMotorDriver(void) {
  static uint32_t prevButtonPress = 0;
  if (millis() - prevButtonPress > 100) {
    Serial.println("Button has been pushed!");
    mode +=1;
    prevButtonPress = millis();
  }
}
