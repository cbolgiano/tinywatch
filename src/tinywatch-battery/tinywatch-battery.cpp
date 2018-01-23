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

#include "tinywatch-battery.h"  // NOLINT

extern int SCREEN_WIDTH;

// TinyScreen+ min voltage is 2.7V and max voltage is 5.5V.
// The sense pin for is A4. Found in Schematic.
// Pin 3 is used for activation. Supposed to prolong battery duration.
Battery battery(2700, 5500, A4, 3);

// Setup for battery plugin.
void TinyWatchBattery::setup() {
  battery.begin();
}

// Draw batter level line.
void TinyWatchBattery::drawBatteryLevel(TinyScreen display) {
  drawBatteryLevel(display, 0, 62, 2);
}

// Draw battery level line at location (x,y) at a specific
// height using display. Width is defined by battery level.
void TinyWatchBattery::drawBatteryLevel(TinyScreen display
  , int x, int y, int height) {
  int batteryLevel = battery.level();
  if (batteryLevel > SCREEN_WIDTH) {
    batteryLevel = SCREEN_WIDTH;
  }
  display.drawRect(x, y, batteryLevel
    , height, TSRectangleFilled, TS_8b_Green);
}
