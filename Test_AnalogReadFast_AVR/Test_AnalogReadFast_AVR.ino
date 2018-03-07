#include <Streaming.h>
#include <StopWatch.h>
#include <Albert.h>
#include <avdweb_AnalogReadFast.h>

const byte adcPin = A1; 
  
void setup(void) 
{ Serial.begin(9600);
  while(!Serial);
  Serial << "\nanalogRead_10bit us1 analogReadFast_10bit us3";
  for(int i=0; i<10; i++) testAnalogRead();
}

void testAnalogRead()
{ static Stopwatch stopwatch(micros); 
  //delay(1000);
  
  stopwatch.start(); 
  int adc1 = analogRead(adcPin); // only resolution 10bit 112us on AVR 
  stopwatch.stop(); int t1 = stopwatch.interval;

  stopwatch.start(); 
  int adc2 = analogReadFast(adcPin); // 20us on AVR 
  stopwatch.stop(); int t2 = stopwatch.interval;

  Serial << endl << adc1, t1, adc2, t2;
}

void loop(void) 
{  
}



