// Unit test program for analogReadFast
// http://www.avdweb.nl/arduino/libraries/fast-10-bit-adc.html

#include "avdweb_AnalogReadFast.h"
#include <Albert.h>
#include <RunningAverage.h> // https://github.com/RobTillaart/Arduino/tree/master/libraries/RunningAverage
#include <StopWatch.h>
#include <Streaming.h>

const byte adcPin = A2; // 0.1V (10 Ohm / 330 Ohm to 3.3V)
const bool doPrintStandardDeviation = 1;
const bool doprintExecutionTime = 0;
const int testsamples = 100; // max ~100 for AVR, max ~250 for SAMD21
const int ravgSamples = 16; // running average filter
const int ExcelY1corr = 10; // place graphs above each other in Excel
const int ExcelY2corr = 15;
const int ExcelY3corr = 30;
const int ExcelY4corr = 35;
const int ExcelY5corr = 53;
const int ExcelY6corr = 55;
const bool doExcelYcorr = 1; // correction for Excel graph

// compile time calculations
const int adcValue = -120; // analogRead value for 0.1V
const int O1 = doExcelYcorr * (adcValue + ExcelY1corr);
const int O2 = doExcelYcorr * (adcValue + ExcelY2corr);
const int O3 = doExcelYcorr * (adcValue + ExcelY3corr);
const int O4 = doExcelYcorr * (adcValue + ExcelY4corr);
const int O5 = doExcelYcorr * (adcValue + ExcelY5corr);
const int O6 = doExcelYcorr * (adcValue + ExcelY6corr);

Stopwatch stopwatch(micros);
RunningAverage slow10test(testsamples), fast10test(testsamples); // for the test values
#if defined(__arm__)
RunningAverage slow12ravg(ravgSamples), fast12ravg(ravgSamples); // runningAverage filter
RunningAverage slow12test(testsamples), fast12test(testsamples); // for the test values
RunningAverage slow12ravgTest(testsamples), fast12ravgTest(testsamples); // for the test values
#endif

void testAnalogRead()
{
    for (int i = 0; i < testsamples; i++)
        slow10test.addValue(analogRead(adcPin));
    for (int i = 0; i < testsamples; i++)
        fast10test.addValue(analogReadFast(adcPin));
#if defined(__arm__)
    analogReadResolution(12);
    for (int i = 0; i < testsamples; i++)
        slow12test.addValue(analogRead(adcPin));
    for (int i = 0; i < testsamples; i++)
        fast12test.addValue(analogReadFast(adcPin));
    analogReadResolution(10);
#endif
}

void testAnalogReadRavg()
{
#if defined(__arm__)
    analogReadResolution(12);
    for (int i = 0; i < testsamples; i++) {
        slow12ravg.addValue(analogRead(adcPin)); // calc runningAverage
        slow12ravgTest.addValue(slow12ravg.getAverage()); // test analogRead with runningAverage
    }
    for (int i = 0; i < testsamples; i++) {
        fast12ravg.addValue(analogReadFast(adcPin)); // calc runningAverage
        fast12ravgTest.addValue(fast12ravg.getAverage()); // test analogReadFast with runningAverage
    }
    analogReadResolution(10);
#endif
}

void printAll()
{
    const int printFromSample = 3;
    Serial << "slow10 fast10 slow12 fast12 slow12ravg fast12ravg\n";
    for (int i = printFromSample; i < testsamples; i++) {
        Serial << 4 * (int)slow10test.getElement(i) + O1, 4 * (int)fast10test.getElement(i) + O2, "";
#if defined(__arm__)
        Serial << (int)slow12test.getElement(i) + O3, (int)fast12test.getElement(i) + O4,
            (int)slow12ravgTest.getElement(i) + O5, (int)fast12ravgTest.getElement(i) + O6;
#endif
        Serial << endl;
    }
}

void printExecutionTime()
{
    stopwatch.start(); // default is analogReadResolution(10)
    analogRead(adcPin); // 425us on SAMD21
    stopwatch.stop();
    Serial << "\nslow10", stopwatch.interval, "us";

    stopwatch.start();
    analogReadFast(adcPin); // 23us on SAMD21
    stopwatch.stop();
    Serial << "\nfast10", stopwatch.interval, "us";

#if defined(__arm__)
    analogReadResolution(12);

    stopwatch.start();
    analogRead(adcPin); // 425us on SAMD21
    stopwatch.stop();
    Serial << "\nslow12", stopwatch.interval, "us";

    stopwatch.start();
    analogReadFast(adcPin); // 24us on SAMD21
    stopwatch.stop();
    Serial << "\nfast12", stopwatch.interval, "us";

    analogReadResolution(10);
#endif
}

void printStandardDeviation()
{
    Serial << "\nslow10 SD", slow10test.getStandardDeviation();
    Serial << "\nfast10 SD", fast10test.getStandardDeviation();
#if defined(__arm__)
    Serial << "\nslow12 SD", slow12test.getStandardDeviation();
    Serial << "\nfast12 SD", fast12test.getStandardDeviation();
    Serial << "\nslow12ravg SD", slow12ravgTest.getStandardDeviation();
    Serial << "\nfast12ravg SD", fast12ravgTest.getStandardDeviation();
#endif
}

void setup(void)
{
    Serial.begin(9600);
    while (!Serial)
        ;
    analogRead(adcPin); // first analogRead is wrong
    testAnalogRead(); // without running average
    testAnalogReadRavg(); // with running average
    printAll();
    if (doprintExecutionTime)
        printExecutionTime();
    if (doPrintStandardDeviation)
        printStandardDeviation();
}

void loop(void)
{
}
