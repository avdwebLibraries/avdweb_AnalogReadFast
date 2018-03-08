### avdweb_AnalogReadFast
The standard Arduino analogRead() takes about 112us for the AVR and 425us for the SAMD21, this is very slow. 
The new function analogReadFast() takes just 21us. 

Compatible with:
- AVR boards: Arduino Uno, Nano, Mega, Leonardo, etc.
- SAMD21 boards: Arduino Zero, SAM 15x15, etc. 

http://www.avdweb.nl/arduino/libraries/fast-10-bit-adc.html
