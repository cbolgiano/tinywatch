#ifndef _TINYWATCH_TIME_H_
#define _TINYWATCH_TIME_H_

#ifndef _ARDUINO_H_
#include <Arduino.h>
#endif

#ifndef _TIMELIB_H
#include <TimeLib.h>
#endif

#ifndef _TINYSCREEN_H_
#include <TinyScreen.h>
#endif

#ifndef _BLE_PERIPHERAL_H_
#include <BLEPeripheral.h>
#endif

namespace TinyWatchTime{
  //Set time in TimeLib when value is written to timeCharacteristic.
  void setTimeHandler(BLECentral& central, BLECharacteristic& characteristic);

  //Returns a const char* that represents
  //the current time.
  const char* getTimeToRender(time_t t);

  //Returns a const char* that represents
  //the current date.
  const char* getDateToRender(time_t t);

  //Setup for time plugin.
  void twTimeSetup();
    
  //BLE poll for timeCharacteristic value change.
  void pollTime();

  //Render time using diplay.
  void renderTime(TinyScreen display);

  //Render date using diplay.
  void renderDate(TinyScreen display);
}

#endif
