#include <Streaming.h>
#include <StopWatch.h>
#include <Albert.h>
#include "avdweb_AnalogReadFast.h"

const byte adcPin = A1; 
  
void setup(void) 
{ Serial.begin(9600);
  while(!Serial);
  Serial << "\nanalogRead_10bit us1 analogRead_12bit us2 analogReadFast_10bit us3 analogReadFast_12bit us4";
  for(int i=0; i<10; i++) testAnalogRead();
}

void testAnalogRead()
{ static Stopwatch stopwatch(micros); 
  //delay(1000);
  
  stopwatch.start(); 
  int adc1 = analogRead(adcPin); // default resolution 10bit 425us on SAMD21 
  stopwatch.stop(); int t1 = stopwatch.interval;

  analogReadResolution(12); 
  stopwatch.start(); 
  int adc2 = analogRead(adcPin); // 425us on SAMD21 
  stopwatch.stop(); int t2 = stopwatch.interval;

  analogReadResolution(10);
  stopwatch.start(); 
  int adc3 = analogReadFast(adcPin); // 23us on SAMD21  
  stopwatch.stop(); int t3 = stopwatch.interval;

  analogReadResolution(12);
  stopwatch.start(); 
  int adc4 = analogReadFast(adcPin); // 24us on SAMD21 
  stopwatch.stop(); int t4 = stopwatch.interval;

  Serial << endl << adc1, t1, adc2, t2, adc3, t3, adc4, t4;
  analogReadResolution(10); // restore default
}

void loop(void) 
{  
}



