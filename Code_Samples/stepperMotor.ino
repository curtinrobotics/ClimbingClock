/*
  Author: Some bloke calling itself "blueicesparks" ?????
  Date: ???????
  Organisation: Curtin Robotics Club (CRoC)
  Project: Climbing Clock (2019)
  Purpose: something to do with stepper motors apparently ????
*/

#include <Tone.h>

// What do this words mean???
#define HDIR 2 // High as dirt?
#define HSTP 3 // H-stop? Hate Sleeping Tiki-Parrots???
#define H_EN 4 // Hate Every Nagger???

#define MDIR 5 // Make Dodgeball Illegal in Romania???
#define MSTP 6 // Men Stopping Tchikita Police???
#define M_EN 7 // MASSIVES: Everyone's Nuisance???

Tone hsm; // Herpes Strike Miami ???
Tone msm; // Men Seeing Men ???

void setup()
{
  // Is it necessary to specify the binary of a hexadecimal number?
  // If someone reading this doesn't understand hexadecimal, how likely is it they'll understand binary?
  DDRD |= 0xFC;  // 0b11111100 
  PORTD |= 0xFC; // 0b11111100
  hsm.begin(HSTP);
  msm.begin(MSTP);
}

// EEWWWWW!!! NOT ZOMBIE CODE!!!
//tested speeds (*.play(speed*fabs(sin(f)))
//original = 440
//300 - 
//200 - does not seem to like this one

//tested counter values
//original f = 0.001
//0.01 - super quick
//0.0005 - good but still too fast for the clock
//0.0001 - doesn't seem to work?

float f = 0.0;

void loop()
{
  digitalWrite(HDIR, sin(f) > 0 ? HIGH : LOW);
  digitalWrite(MDIR, sin(f) > 0 ? HIGH : LOW);
  //hsm.stop();
  hsm.play( 300 * fabs(sin(f)) ); //speed of motor 
  //msm.stop();
  msm.play( 300 * fabs(sin(f)) );  //speed of motor
  
  f += 0.0005; //this will affect how long the gears spin for (it's a counter for the loop below)

  if (f > 10) { 
    f = 0.0;
    PORTD ^= 0x90; // WHAT IN GOD'S NAME IS THIS???? ALWAYS comment on bitwise operations!!! 
    //digitalWrite(H_EN, digitalRead(H_EN) ? LOW : HIGH );  
    //digitalWrite(M_EN, digitalRead(M_EN) ? LOW : HIGH ); 
  }
}
