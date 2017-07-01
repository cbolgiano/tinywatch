#ifndef _TINYWATCH_TIME_H_
#define _TINYWATCH_TIME_H_

#ifndef _ARDUINO_H_
#include <Arduino.h>
#endif

#ifndef _TIMELIB_H_
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
  void setup();
    
  //BLE poll for timeCharacteristic value change.
  void poll();

  //Render time using diplay.
  void drawTime(TinyScreen display);

  //Render date using diplay.
  void drawDate(TinyScreen display);

  //Render time using diplay.
  void drawTime(TinyScreen display, int x, int y, FONT_INFO fontDescriptor);

  //Render date using diplay.
  void drawDate(TinyScreen display, int x, int y, FONT_INFO fontDescriptor);
}

#endif
