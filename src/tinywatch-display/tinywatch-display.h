#ifndef _TINYWATCH_DISPLAY_H_
#define _TINYWATCH_DISPLAY_H_

#ifndef _ARDUINO_H_
#include <Arduino.h>
#endif

#ifndef _TINYSCREEN_H_
#include <TinyScreen.h>
#endif

#ifndef _SPI_H_
#include <SPI.h>
#endif

namespace TinyWatchDisplay{
  //TinyScreen display setup.
  void setup();
  
  //Manage tinywatch display.
  void manageDisplay();

  //Get display to configure.
  TinyScreen getDisplay();
}

#endif
