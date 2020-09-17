#define dirPin 3
#define stepPin 6
#define buttonPin 2
#define enablePin 4

#define CLOCKWISE HIGH
#define ANTI_CLOCK LOW

#define PI 3.14f

enum Modes {OFF, ST_HIGH, ST_LOW, TONE};

int buttonState = 0;
volatile int mode = 0;
int prevMode = 0;
unsigned int freq = 1000;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), toggleStepperMotorDriver, 
                  RISING);
  digitalWrite(dirPin, CLOCKWISE);
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
    digitalWrite(dirPin, CLOCKWISE);
    if (prevMode != mode){
      Serial.println("Motor is on HIGH.");
    }
  }
  if (mode == ST_LOW) {
    digitalWrite(stepPin, LOW);
    digitalWrite(dirPin, CLOCKWISE);
    if (prevMode != mode) {
      Serial.println("Motor is on LOW");
    }
  }
  if (mode == TONE) {
    digitalWrite(dirPin, CLOCKWISE);
    digitalWrite(enablePin, LOW);
    tone(stepPin,freq);
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
