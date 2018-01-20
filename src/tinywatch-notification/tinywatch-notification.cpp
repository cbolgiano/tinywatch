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

#include "tinywatch-notification.h"  // NOLINT

extern int SCREEN_CENTER;

const int NOTIF_DURATION = 3;

char* msg = "";
int isNotification = 0;

// Is in seconds.
int notifySleepTime = 0;

// Notification Characteristic
BLECharCharacteristic notificationCharacteristic =
  BLECharCharacteristic("CCC2", BLEWrite);

// Setup for notification plugin.
void TinyWatchNotification::setup(BLEPeripheral* existingPeripheral) {
  existingPeripheral->addAttribute(notificationCharacteristic);

  notificationCharacteristic.setEventHandler(BLEWritten
    , setNotificationHandler);
}

void TinyWatchNotification::setNotificationHandler(BLECentral& central
  , BLECharacteristic& characteristic) {
  msg = "Alert!";
}

// Render notification using display.
void TinyWatchNotification::drawNotification(TinyScreen display) {
  int width = display.getPrintWidth(msg);

  drawNotification(display
    , (SCREEN_CENTER/2) - width, 16, liberationSans_16ptFontInfo, msg);
}

// Render notification using display.
void TinyWatchNotification::drawNotification(TinyScreen display
  , int x, int y, FONT_INFO fontDescriptor, char* customMsg) {
  resetNotification(display);

  if (!isNotification && msg != "") {
    isNotification = 1;
    notifySleepTime = now() + NOTIF_DURATION;
    TinyWatchVibrate::vibrate();
    display.clearScreen();
    display.setFont(fontDescriptor);
    display.setCursor(x, y);
    display.print(customMsg);
  }
}

// START - Helper functions

void TinyWatchNotification::resetNotification(TinyScreen display) {
  if (isNotification && (TinyWatchButton::isAny(display)
    || now() >= notifySleepTime)) {
    isNotification = 0;
    msg = "";
    // Reset sleep time.
    notifySleepTime = 0;
    TinyWatchVibrate::vibrateOff();
  }
}

// END - Helper functions
