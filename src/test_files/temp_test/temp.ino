/*Tests Two Temperature Sensors*/

/*Conect Centre Pins of Temp Sensor to analog pins 0 and 1
 _____
|     |
|     | (Flat Side to front)
 | | |
 | | |
5V   GND
  A0/1 */
#define tempPin1 0
#define tempPin2 1
 
float Temp1;
float Temp2;

void setup()
{
  Serial.begin(9600); 
  /* Set the analogue reference used by the ADC inputs 
     to the internal 1.1V reference */
  analogReference(INTERNAL);
}
 
void loop()
{
  /* Read the analogue pin and scale the reading to degrees centigrade 
     (10mV per degree / (1.1V Int Ref / 1024 ADC resolution)) */
  Temp1 = analogRead(tempPin1) / (10.24/1.1);
  Temp2 = analogRead(tempPin2) / (10.24/1.1);
  Serial.print("Temp Sensor 1: ");
  Serial.print(Temp1);
  Serial.print("C\nTemp Sensor 2: ");
  Serial.print(Temp2);
  Serial.println("C\n");

  delay(1000);
}
