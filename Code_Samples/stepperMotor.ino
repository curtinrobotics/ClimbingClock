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

float f = 0; 
void loop()
{
  digitalWrite(HDIR, sin(f)>0 ? HIGH : LOW);
  digitalWrite(MDIR, sin(f)>0 ? HIGH : LOW);
  //hsm.stop();
  hsm.play(440*fabs(sin(f)));
  //msm.stop();
  msm.play(440*fabs(sin(f)));  
  f+=0.001;
  if(f > 10) { 
    f = 0;
    PORTD ^= 0x90; 
    //digitalWrite(H_EN, digitalRead(H_EN) ? LOW : HIGH );  
    //digitalWrite(M_EN, digitalRead(M_EN) ? LOW : HIGH ); 
  }
}
