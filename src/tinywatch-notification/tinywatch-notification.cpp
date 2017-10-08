#include "tinywatch-notification.h"

extern int SCREEN_CENTER;

const int TIME_UNTIL_SLEEP = 5;

char* msg = "";
int isNotification = 0;

//notifySleepTime is in seconds.
int notifySleepTime = 0;

//Notification Characteristic
BLECharCharacteristic notificationCharacteristic = BLECharCharacteristic("CCC2", BLEWrite);

//Setup for notification plugin.
void TinyWatchNotification::setup(BLEPeripheral& existingPeripheral){
  existingPeripheral.addAttribute(notificationCharacteristic);

  notificationCharacteristic.setEventHandler(BLEWritten, setNotificationHandler);
}

void TinyWatchNotification::setNotificationHandler(BLECentral& central, BLECharacteristic& characteristic) {
  msg = "Alert!";
}

//Render notification using display.
void TinyWatchNotification::drawNotification(TinyScreen display) {
  int width = display.getPrintWidth(msg);
    
  drawNotification(display,(SCREEN_CENTER/2) - width, 16,liberationSans_16ptFontInfo, msg);
}

//Render notification using display.
void TinyWatchNotification::drawNotification(TinyScreen display, int x, int y, FONT_INFO fontDescriptor, char* customMsg) {
  resetNotification(display);
  
  if (!isNotification && msg != "") {
    isNotification = 1;
    notifySleepTime = now() + TIME_UNTIL_SLEEP;
    display.clearScreen();
    display.setFont(fontDescriptor);
    display.setCursor(x, y);
    display.print(customMsg);
  }
}

//START - Helper functions

void TinyWatchNotification::resetNotification(TinyScreen display) {
  if (isNotification && ((display.getButtons(TSButtonUpperLeft)
    || display.getButtons(TSButtonUpperRight)
    || display.getButtons(TSButtonLowerLeft)
    || display.getButtons(TSButtonLowerRight))
    || now() >= notifySleepTime)) {
    isNotification = 0;
    msg = "";    
  }
}

//END - Helper functions
