// Test program for analogReadFast
// http://www.avdweb.nl/arduino/libraries/fast-10-bit-adc.html


#include "avdweb_AnalogReadFast.h"


const byte adcPin = A2;     // 0.1V (10 Ohm / 330 Ohm to 3.3V)

uint32_t start, stop, sum;


void setup(void) 
{ 
  Serial.begin(9600);
  while(!Serial);
  Serial.println(__FILE__);

  delay(100);

  sum = 0;
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    sum += analogRead(adcPin);
  }
  stop = micros();
  Serial.print("REF: \t");
  Serial.println((stop - start) * 0.01);
  delay(100);


#if defined(__arm__) 
    analogReadResolution(10); 
#endif 
  sum = 0;
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    sum += analogReadFast(adcPin);
  }
  stop = micros();
  Serial.print("FAST10: \t");
  Serial.println((stop - start) * 0.01);
  delay(100);


#if defined(__arm__) 
    analogReadResolution(12); 
#endif 
  sum = 0;
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    sum += analogReadFast(adcPin);
  }
  stop = micros();
  Serial.print("FAST12: \t");
  Serial.println((stop - start) * 0.01);
  delay(100);
}

void loop(void) 
{ 
}
