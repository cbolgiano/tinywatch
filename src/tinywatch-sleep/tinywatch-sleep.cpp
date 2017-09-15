#include "tinywatch-sleep.h"

//TIME_UNTIL_SLEEP is in seconds.
const int TIME_UNTIL_SLEEP = 5;

//sleepyTime is in seconds.
int sleepyTime = 0;
int isSleeping = 1;

void TinyWatchSleep::sleep(TinyScreen display){
  isSleeping = now() >= sleepyTime ? 1 : 0;
  if (display.getButtons(TSButtonUpperLeft)
       || display.getButtons(TSButtonUpperRight)
       || display.getButtons(TSButtonLowerLeft)
       || display.getButtons(TSButtonLowerRight)) {
    sleepyTime = now() + TIME_UNTIL_SLEEP;
  }
}

//timeToSleep is in seconds.
void TinyWatchSleep::sleep(TinyScreen display, int timeToSleep){
  isSleeping = now() >= sleepyTime ? 1 : 0;
  if (display.getButtons(TSButtonUpperLeft)
       || display.getButtons(TSButtonUpperRight)
       || display.getButtons(TSButtonLowerLeft)
       || display.getButtons(TSButtonLowerRight)) {
    sleepyTime = now() + timeToSleep;
  }
}
