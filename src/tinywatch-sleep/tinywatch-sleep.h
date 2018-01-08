/*
MIT License

Copyright (c) 2018 Christopher Bolgiano

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _TINYWATCH_SLEEP_H_ // NOLINT
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

namespace TinyWatchSleep {
  // Render time using diplay.
  void sleep(TinyScreen display);

  // Sleep for the value of timeToSleep.
  void sleep(TinyScreen display, int timeToSleep);

  void setSleeping();

  void setSleepyTime(TinyScreen display, int timeToSleep);
}  // namespace TinyWatchSleep

#endif  // _TINYWATCH_SLEEP_H_ NOLINT
