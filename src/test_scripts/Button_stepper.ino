#define dirPin = 3;  //Direction pin in 3
#define stepPin = 2;  //Step pin in 2
#define buttonPin = 5;  //Button pin in 5
#define enablePin = 4;

#define CLOCKWISE HIGH
#define ANTI_CLOCK LOW

#define PI 3.14f
#define OFF_TIME 3

float angle = 0.0f;
unsigned int freq;
bool enabled = false, direction = CLOCKWISE

int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(buttonPin, INPUT);
pinMode(stepPin, OUTPUT);
pinMode(dirPin, OUTPUT);

Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH){
    enabled = true
  }
  if (enabled){
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
    Serial.print(F("Setting frequency to ")): Serial.println(freq);
    tone(stepPin, freq);

    angle += 0.001f;

    if (angle > 4.0f * PI) {
      angle = 0.0f;
      digitalWrite(enablePin, HIGH)
      Serial.print(F("Turning off stepper motor driver for "));
      Serial.print(OFF_TIME); Serial.println(F(" seconds"));
    }
  } else {
    Serial.println(F("Press button to start "))
    enabled = true;
  }
}
