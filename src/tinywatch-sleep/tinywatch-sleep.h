#ifndef _TINYWATCH_SLEEP_H_
#define _TINYWATCH_SLEEP_H_

#ifndef _ARDUINO_H_
#include <Arduino.h>
#endif

#ifndef _TIMELIB_H_
#include <TimeLib.h>
#endif

#ifndef _TINYSCREEN_H_
#include <TinyScreen.h>
#endif

namespace TinyWatchSleep{
  //Render time using diplay.
  void sleep(TinyScreen display);

  //Sleep for the value of timeToSleep.
  void sleep(TinyScreen display, int timeToSleep);

  void setSleeping();

  void setSleepyTime(TinyScreen display, int timeToSleep);
}

#endif
