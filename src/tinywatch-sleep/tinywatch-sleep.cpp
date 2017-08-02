#include "tinywatch-sleep.h"

char isSleep = 0;

void TinyWatchSleep::sleep(TinyScreen display){
  isSleep ? display.off() : display.on();
  if (display.getButtons(TSButtonUpperLeft)
    && display.getButtons(TSButtonUpperRight)) {
    isSleep = isSleep ? 0 : 1;
    delay(250);
  }
}

void TinyWatchSleep::sleep(TinyScreen display, int timeToSleep){
  isSleep ? display.off() : display.on();
  if (display.getButtons(TSButtonUpperLeft)
    && display.getButtons(TSButtonUpperRight)) {
    isSleep = isSleep ? 0 : 1;
    delay(timeToSleep);
  }
}
