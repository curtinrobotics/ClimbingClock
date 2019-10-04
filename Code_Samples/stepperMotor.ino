/*
  Author: Tom Johnson
  Date: 26/09/2019
  Date: 28/09/2019 Modifications to speed and freq
  Organisation: Curtin Robotics Club (CRoC)
  Project: Climbing Clock (2019)
  Purpose: Revised version of the stepper motor code.
*/

#include <Tone.h>

#define M1_DIR 2 // Motor 1 - Direction
#define M1_STP 3 // Motor 1 - Step
#define M1_EN 4 // Motor 1 - Encoder

#define M2_DIR 5 // Motor 2 - Direction
#define M2_STP 6 // Motor 2 - Step
#define M2_EN 7 // Motor 2 - Encoder

Tone motor1; 
Tone motor2; 

void setup()
{ 
  //DDRD - maps to the digital pins 0 - 7 on the Arduino board
  //PORTD - the read and write pin
  DDRD |= 0xFC; 
  PORTD |= 0xFC;
  motor1.begin(M1_STP); //initialising pin to play a tone
  motor2.begin(M2_STP); //initialising pin to play a tone
}

float duration = 0.0; 

void loop()
{
  // if sin function > 0, then high will be written to pin. If sin function < 0, then low will be written to pin.
  digitalWrite(M1_DIR, sin(duration) > 0 ? HIGH : LOW); 
  digitalWrite(M2_DIR, sin(duration) > 0 ? HIGH : LOW);
  //hsm.stop(); //stop playing the tone
  motor1.play( 300 * fabs(sin(duration)) ); //speed of motor 
  //msm.stop(); //stop playing the tone
  motor2.play( 300 * fabs(sin(duration)) );  //speed of motor
  
  duration += 0.0005; //this will affect how long the gears spin for (it's a counter for the loop below)

  if (duration > 10) { 
    duration = 0.0;
    PORTD ^= 0x90; // resets the read/write pin (I'm pretty sure but will double check) 
    //digitalWrite(H_EN, digitalRead(H_EN) ? LOW : HIGH );  
    //digitalWrite(M_EN, digitalRead(M_EN) ? LOW : HIGH ); 
  }
}
