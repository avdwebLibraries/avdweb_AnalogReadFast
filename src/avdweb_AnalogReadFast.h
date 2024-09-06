/**
 * avdweb_AnalogReadFast.h
 *
 * `avdweb_AnalogReadFast` Library
 * ================================
 *
 * Fast analogRead 10/12 bit ADC for the Arduino Zero and Uno
 *
 * WEBSITE: http://www.avdweb.nl/arduino/libraries/fast-10-bit-adc.html
 *
 * Sources
 * --------
 * https://github.com/avdwebLibraries/avdweb_AnalogReadFast
 *
 * License
 * --------
 * SPDX: MIT
 *
 * `avdweb_AnalogReadFast` - Fast analogRead 10/12 bit ADC for the
 *       Arduino Zero and Uno
 *
 * Copyright (C) 2019-2024 Albert van Dalen <http://www.avdweb.nl>
 * Copyright (C) 2024 Abhijit Bose (aka. Boseji) :contributor:
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Notes
 * ------
 *
 * HISTORY:
 * 1.0.0 7-3-2018 analogReadFast for SAMD21 (10/12bit) and AVR (10bit)
 *
 */

#ifndef analogReadFast_H
#define analogReadFast_H

// inline library functions must be in header
int inline analogReadFast(byte ADCpin);

#if defined(__arm__)
int inline analogReadFast(byte ADCpin)
{
    ADC->CTRLA.bit.ENABLE = 0; // disable ADC
    while (ADC->STATUS.bit.SYNCBUSY == 1)
        ; // wait for synchronization

    int CTRLBoriginal = ADC->CTRLB.reg;
    int AVGCTRLoriginal = ADC->AVGCTRL.reg;
    int SAMPCTRLoriginal = ADC->SAMPCTRL.reg;

    ADC->CTRLB.reg &= 0b1111100011111111; // mask PRESCALER bits
    ADC->CTRLB.reg |= ADC_CTRLB_PRESCALER_DIV64; // divide Clock by 64
    ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1 | // take 1 sample
        ADC_AVGCTRL_ADJRES(0x00ul); // adjusting result by 0
    ADC->SAMPCTRL.reg = 0x00; // sampling Time Length = 0

    ADC->CTRLA.bit.ENABLE = 1; // enable ADC
    while (ADC->STATUS.bit.SYNCBUSY == 1)
        ; // wait for synchronization

    int adc = analogRead(ADCpin);

    ADC->CTRLB.reg = CTRLBoriginal;
    ADC->AVGCTRL.reg = AVGCTRLoriginal;
    ADC->SAMPCTRL.reg = SAMPCTRLoriginal;

    return adc;
}
#else
int inline analogReadFast(byte ADCpin)
{
    byte ADCSRAoriginal = ADCSRA;
    ADCSRA = (ADCSRA & B11111000) | 4;
    int adc = analogRead(ADCpin); // Initialize variable and burn a read
    adc = analogRead(ADCpin); // because ADMUX takes 2.5us to switch
    ADCSRA = ADCSRAoriginal;
    return adc;
}
#endif
#endif /* analogReadFast_H */
