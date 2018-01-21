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

#include "tinywatch-sleep.h"  // NOLINT

// Is in seconds.
const int TIME_UNTIL_SLEEP = 5;

// Is in seconds.
int sleepyTime = 0;
int isSleeping = 1;

void TinyWatchSleep::sleep(TinyScreen display) {
  setSleeping();
  setSleepyTime(display, TIME_UNTIL_SLEEP);
}

// Is in seconds.
void TinyWatchSleep::sleep(TinyScreen display, int timeToSleep) {
  setSleeping();
  setSleepyTime(display, timeToSleep);
}

// START - Helper functions

void TinyWatchSleep::setSleeping() {
  isSleeping = now() >= sleepyTime ? 1 : 0;
}

void TinyWatchSleep::setSleepyTime(TinyScreen display, int timeToSleep) {
  if (TinyWatchButton::isAny(display)) {
    sleepyTime = now() + timeToSleep;
  }
}

// END - Helper functions
