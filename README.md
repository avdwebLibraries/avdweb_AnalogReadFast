
[![Arduino CI](https://github.com/avandalen/avdweb_AnalogReadFast/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/avandalen/avdweb_AnalogReadFast/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/avandalen/avdweb_AnalogReadFast/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/avandalen/avdweb_AnalogReadFast/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/avandalen/avdweb_AnalogReadFast/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/avandalen/avdweb_AnalogReadFast.svg)](https://github.com/avandalen/avdweb_AnalogReadFast/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/avandalen/avdweb_AnalogReadFast/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/avandalen/avdweb_AnalogReadFast.svg?maxAge=3600)](https://github.com/avandalen/avdweb_AnalogReadFast/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/avandalen/library/avdweb_AnalogReadFast.svg)](https://registry.platformio.org/libraries/avandalen/avdweb_AnalogReadFast)


## avdweb_AnalogReadFast

### Description

Very fast analogRead()

The standard Arduino analogRead() takes about 112us for the AVR and 425us for the SAMD21, this is very slow. 
The new function analogReadFast() takes just 21us. 


### Compatibility

- AVR boards: Arduino Uno, Nano, Mega, Leonardo, etc.
- SAMD21 boards: Arduino Zero, SAM 15x15, etc. 

Optimized versions for other platforms are welcome.


### Related

https://www.avdweb.nl/arduino/adc-dac/fast-10-bit-adc


## Interface

```cpp
#include "avdweb_AnalogReadFast.h"
```

The interface consists of one single function, which is implemented
for AVR and SAMD.
This function replaces the default **analogRead()**

- **int inline analogReadFast(byte ADCpin)**




