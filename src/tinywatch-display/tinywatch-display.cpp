#include "tinywatch-display.h"

extern int isNotification;
extern int isSleeping;

TinyScreen display = TinyScreen(TinyScreenPlus);

void TinyWatchDisplay::setup(){
  display.begin();
  display.setFlip(true);
  display.setBrightness(10);
}

void TinyWatchDisplay::manageDisplay(){
  if(isNotification){
    display.on();
    return;
  }

  if(!isSleeping){
    display.on();
    return;
  }

  display.off();
}

TinyScreen TinyWatchDisplay::getDisplay(){
  return display;
}
