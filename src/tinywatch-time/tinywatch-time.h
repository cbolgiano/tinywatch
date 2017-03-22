#ifndef _TINYWATCH_TIME_H_
#define _TINYWATCH_TIME_H_

#include <Arduino.h>
#include <TimeLib.h>

//Sets time for TimeLib using timeInSeconds.
void setTimeToRender(long timeInSeconds);

//Returns a const char* that represents
//the current time.
const char* getTimeToRender();

#endif
