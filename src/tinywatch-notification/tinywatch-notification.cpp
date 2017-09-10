#include "tinywatch-notification.h"

const int SCREEN_HEIGHT = 48;
const int SCREEN_WIDTH = 96;
const int SCREEN_CENTER = SCREEN_WIDTH / 2;
const int MSG_X_START = SCREEN_WIDTH + 1;
const int FONT_SIZE_OFFSET = 5;
char* msg = "";
int msgX = MSG_X_START;

//Notification Characteristic
BLECharCharacteristic notificationCharacteristic = BLECharCharacteristic("CCC2", BLEWrite);

//Setup for notification plugin.
void TinyWatchNotification::setup(BLEPeripheral& existingPeripheral){
  existingPeripheral.addAttribute(notificationCharacteristic);

  notificationCharacteristic.setEventHandler(BLEWritten, setNotificationHandler);
}

//TODO: Set Notification
void TinyWatchNotification::setNotificationHandler(BLECentral& central, BLECharacteristic& characteristic) {
  msg = notificationCharacteristic.value();
}

//Render notification using display.
void TinyWatchNotification::drawNotification(TinyScreen display) {
  int width = display.getPrintWidth(msg);
  if (msg != "" && msgX > -width) {
    display.setFont(liberationSans_8ptFontInfo);
    display.setCursor(msgX, 48);
    display.print(msg);
    msgX--;
  } else {
    msg = "";
    msgX = MSG_X_START;
  }
}
