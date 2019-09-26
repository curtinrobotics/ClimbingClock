#define DIR 2
#define STEP 3
#define _EN 4

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT); digitalWrite(2, HIGH);
  pinMode(3, OUTPUT); digitalWrite(2, HIGH);
  pinMode(8, OUTPUT); digitalWrite(8, LOW);
  pinMode(9, OUTPUT); digitalWrite(9, LOW);
  pinMode(10, OUTPUT); digitalWrite(10, LOW);
  pinMode(4, OUTPUT); digitalWrite(4, LOW);
}

float f = 0;

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(DIR, sin(f)>0 ? HIGH : LOW);
  tone(STEP, 1000*fabs(sin(f)));
  f +=0.001;
  if(f > 10) { f = 0; digitalWrite(_EN, digitalRead(_EN) ? LOW : HIGH ); }
}
