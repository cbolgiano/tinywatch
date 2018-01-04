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

#include "tinywatch-time.h" //NOLINT

extern int SCREEN_CENTER;

// Time Characteristic
BLELongCharacteristic timeCharacteristic
  = BLELongCharacteristic("CCC1", BLEWrite);

// Setup for time plugin.
void TinyWatchTime::setup(BLEPeripheral& existingPeripheral) {
  existingPeripheral.addAttribute(timeCharacteristic);

  timeCharacteristic.setEventHandler(BLEWritten, setTimeHandler);
}

// Set time in TimeLib when value is written to timeCharacteristic.
void TinyWatchTime::setTimeHandler(BLECentral& central
  , BLECharacteristic& characteristic) {
  setTime(timeCharacteristic.valueBE());
}

// Returns a const char* that represents
// the current time.
const char* TinyWatchTime::getTimeToRender(time_t t) {
  if (isTimeSet(t)) {
    return String(addZeroPrefix(hour(t))
      + String(hour(t))
      + ":"
      + addZeroPrefix(minute(t))
      + String(minute(t))
      + ":"
      + addZeroPrefix(second(t))
      + String(second(t))).c_str();
  } else {
    return "";
  }
}

// Returns a const char* that represents
// the current date.
const char* TinyWatchTime::getDateToRender(time_t t) {
  if (isTimeSet(t)) {
    return String(addZeroPrefix(month(t))
      + String(month(t))
      + "/"
      + addZeroPrefix(day(t))
      + String(day(t))
      + "/"
      + String(year(t))).c_str();
  } else {
    return "";
  }
}

// Render time using display.
void TinyWatchTime::drawTime(TinyScreen display) {
  display.setFont(liberationSans_16ptFontInfo);
  char* timeText = reinterpret_cast<char*>(getTimeToRender(now()));
  int width = display.getPrintWidth(timeText);
  display.setCursor(SCREEN_CENTER - (width/2), 16);
  display.print(timeText);
}

// Render time using display, x, y, and font.
void TinyWatchTime::drawTime(TinyScreen display
  , int x, int y, FONT_INFO fontDescriptor) {
  display.setFont(fontDescriptor);
  char* timeText = reinterpret_cast<char*>(getTimeToRender(now()));
  display.setCursor(x, y);
  display.print(timeText);
}

// Render date using display.
void TinyWatchTime::drawDate(TinyScreen display) {
  display.setFont(liberationSans_10ptFontInfo);
  char* dateText = reinterpret_cast<char*>(getDateToRender(now()));
  int width = display.getPrintWidth(dateText);
  display.setCursor(SCREEN_CENTER - (width/2), 36);
  display.print(dateText);
}

// Render date using display, x, y, and font.
void TinyWatchTime::drawDate(TinyScreen display
  , int x, int y, FONT_INFO fontDescriptor) {
  display.setFont(fontDescriptor);
  char* dateText = reinterpret_cast<char*>(getDateToRender(now()));
  display.setCursor(x, y);
  display.print(dateText);
}


// START - Helper functions

// Add "0" if needed to time.
const char* TinyWatchTime::addZeroPrefix(int time) {
  return time < 10 ? "0" : "";
}

// Determine if value for time is set.
int TinyWatchTime::isTimeSet(time_t t) {
  return t && timeStatus() != timeNotSet;
}

// END - Helper functions
