#include "tinywatch-time.h"

//Sets time for TimeLib using timeInSeconds.
void setTimeToRender(long timeInSeconds) {
  setTime(timeInSeconds);
}

//Returns a const char* that represents
//the current time.
const char* getTimeToRender() {
  return String((hour() < 10 ? "0" : "")
    + String(hour())
    + ":"
    + (minute() < 10 ? "0" : "")
    + String(minute())
    + ":"
    + (second() < 10 ? "0" : "")
    + String(second())).c_str();
}
