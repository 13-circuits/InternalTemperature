/* InternalTemperature - read internal temperature of ARM processor
 * Copyright (C) 2019 LAtimes2
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* Typical usage:
 *   InternalTemperature temperature;
 *   
 *   temperature.begin();
 *   Serial.println(temperature.readTemperatureC());
 */

#ifndef InternalTemperature_h_
#define InternalTemperature_h_

#define TEMPERATURE_MAX_ACCURACY 0
#define TEMPERATURE_NO_ADC_SETTING_CHANGES 1

class InternalTemperature
{
public:
  InternalTemperature();

  //
  // Main functions
  //

  // Note: If settings_type is TEMPERATURE_MAX_ACCURACY, it will change
  //       the ADC settings to be optimal for reading temperature.
  //       If settings_type is TEMPERATURE_NO_ADC_SETTING_CHANGES, it will
  //       keep the default ADC settings or any other settings changes.
  //       readTemperature will detect the current settings and use them.
  bool begin (int temperature_settings_type = TEMPERATURE_MAX_ACCURACY);

  float readTemperatureC (void);
  float readTemperatureF (void);

  //
  //  Calibration functions
  //
  bool singlePointCalibrationC (float actualTemperatureC, float measuredTemperatureC, bool fromDefault = false);
  bool singlePointCalibrationF (float actualTemperatureF, float measuredTemperatureF, bool fromDefault = false);

  bool dualPointCalibrationC (float actualTemperature1C, float measuredTemperature1C,
                              float actualTemperature2C, float measuredTemperature2C, bool fromDefault = false);
  bool dualPointCalibrationF (float actualTemperature1F, float measuredTemperature1F,
                              float actualTemperature2F, float measuredTemperature2F, bool fromDefault = false);

  bool setVTemp25 (float volts);
  bool setSlope (float voltsPerDegreeC);
  float getVTemp25 (void);
  float getSlope (void);
  static int getUniqueID (void);

  //
  // low level utilities
  //
  float convertTemperatureC (float volts);
  static float convertUncalibratedTemperatureC (float volts);
  static float readRawTemperatureVoltage (void);
  static float readRawVoltage (int signalNumber);
  static float readUncalibratedTemperatureC (void);
  static float readUncalibratedTemperatureF (void);
  static float toCelsius (float temperatureFahrenheit);
  static float toFahrenheit (float temperatureCelsius);

private:
  static float convertTemperatureC (float volts, float vTemp25, float slope);
  static void enableBandgap (void);

private:
  float slope;
  float vTemp25;
};

#endif
