/*
 * Author: Harrison Outram
 * Date: 12/12/2019 (d/m/y)
 * Version: 1.0
 * Purpose: Collect data for PWM input vs ouput modelling
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: non-functional
 */

#define TEST_PWM_OUT 5
#define TEST_PWM_IN A1

#define PWM_SAMPLE_SIZE 100

void setup() {
  Serial.begin(9600);
  uint32_t meanPwm;

  Serial.print("analog in\n");

  for (int i = 0; i < 256; i++) {
    meanPwm = 0;
    analogWrite(TEST_PWM_OUT, i);

    for (int j = 0; j < PWM_SAMPLE_SIZE; j++) {
      meanPwm += analogRead(TEST_PWM_IN);
    }

    meanPwm /= PWM_SAMPLE_SIZE;

    //Serial.print(i); Serial.print(",");
    Serial.print(meanPwm); Serial.print("\n");
  }
  
}

void loop() {
  // code should only run once, ergo do nothing here

}
