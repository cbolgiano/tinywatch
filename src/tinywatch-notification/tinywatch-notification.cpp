#include "tinywatch-notification.h"

const int SCREEN_HEIGHT = 48;
const int SCREEN_WIDTH = 96;
const int SCREEN_CENTER = SCREEN_WIDTH / 2;
const int MSG_X_START = SCREEN_WIDTH + 1;
const int TIME_UNTIL_SLEEP = 5;
char* msg = "";
int msgX = MSG_X_START;
int isNotification;

//notifySleepTime is in seconds.
int notifySleepTime = 0;

//Notification Characteristic
BLECharCharacteristic notificationCharacteristic = BLECharCharacteristic("CCC2", BLEWrite);

//Setup for notification plugin.
void TinyWatchNotification::setup(BLEPeripheral& existingPeripheral){
  existingPeripheral.addAttribute(notificationCharacteristic);

  notificationCharacteristic.setEventHandler(BLEWritten, setNotificationHandler);
}

//TODO: Set Notification
void TinyWatchNotification::setNotificationHandler(BLECentral& central, BLECharacteristic& characteristic) {
  msg = "Alert!";
}

//Render notification using display.
void TinyWatchNotification::drawNotification(TinyScreen display) {
  int width = display.getPrintWidth(msg);
  if (isNotification && ((display.getButtons(TSButtonUpperLeft)
    || display.getButtons(TSButtonUpperRight)
    || display.getButtons(TSButtonLowerLeft)
    || display.getButtons(TSButtonLowerRight))
    || now() >= notifySleepTime)) {
    isNotification = 0;
    msg = "";    
  }
  
  if (!isNotification && msg != "") {    
    isNotification = 1;
    notifySleepTime = now() + TIME_UNTIL_SLEEP;
    display.clearScreen();
    display.setFont(liberationSans_16ptFontInfo);
    display.setCursor((SCREEN_CENTER/2) - width, 16);
    display.print(msg);
  }
}
