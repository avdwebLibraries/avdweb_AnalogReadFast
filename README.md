# `avdweb_AnalogReadFast` Library

Home Page <https://www.avdweb.nl/arduino/adc-dac/fast-10-bit-adc>

## Faster `analogRead()`

The standard Arduino `analogRead()` takes about `112us` for the AVR and `425us` for the SAMD21, this is very slow.
The new function analogReadFast() takes just 21us.

## Compatibility

- AVR boards: Arduino Uno, Nano, Mega, Leonardo, etc.
- SAMD21 boards: Arduino Zero, SAM 15x15, etc.

## Developer Note

Please run code formatting before committing the code.

```sh
clang-format -i src/*.* examples/**/*.ino
```

## License

`SPDX: MIT`

`avdweb_AnalogReadFast` - Fast analogRead 10/12 bit ADC for the Arduino Zero and Uno

Copyright (C) 2019-2024 Albert van Dalen <http://www.avdweb.nl>

Copyright (C) 2024 Abhijit Bose (aka. Boseji) :contributor:

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice (including the next paragraph) shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
