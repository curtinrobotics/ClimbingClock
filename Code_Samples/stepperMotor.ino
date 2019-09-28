#include <Tone.h>

#define HDIR 2
#define HSTP 3
#define H_EN 4

#define MDIR 5
#define MSTP 6
#define M_EN 7

Tone hsm;
Tone msm;

void setup()
{
  DDRD |= 0xFC;  // 0b11111100
  PORTD |= 0xFC; // 0b11111100
  hsm.begin(HSTP);
  msm.begin(MSTP);
}

//tested speeds (*.play(speed*fabs(sin(f)))
//original = 440
//300 - 
//200 - does not seem to like this one

//tested counter values
//original f = 0.001
//0.01 - super quick
//0.0005 - good but still too fast for the clock
//0.0001 - doesn't seem to work?

float f = 0; 
void loop()
{
  digitalWrite(HDIR, sin(f)>0 ? HIGH : LOW);
  digitalWrite(MDIR, sin(f)>0 ? HIGH : LOW);
  //hsm.stop();
  hsm.play(300*fabs(sin(f))); //speed of motor 
  //msm.stop();
  msm.play(300*fabs(sin(f)));  //speed of motor
  
  f+=0.0005; //this will affect how long the gears spin for (it's a counter for the loop below)

  if(f > 10) { 
    f = 0;
    PORTD ^= 0x90; 
    //digitalWrite(H_EN, digitalRead(H_EN) ? LOW : HIGH );  
    //digitalWrite(M_EN, digitalRead(M_EN) ? LOW : HIGH ); 
  }
}
