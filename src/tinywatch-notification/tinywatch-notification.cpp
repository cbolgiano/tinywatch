#include "tinywatch-notification.h"

//Notification Characteristic
BLECharCharacteristic notificationCharacteristic = BLECharCharacteristic("CCC2", BLEWrite);

//Setup for notification plugin.
void TinyWatchNotification::setup(BLEPeripheral existingPeripheral){
  existingPeripheral.addAttribute(notificationCharacteristic);

  notificationCharacteristic.setEventHandler(BLEWritten, setNotificationHandler);
}

//TODO: Set Notification
void TinyWatchNotification::setNotificationHandler(BLECentral& central, BLECharacteristic& characteristic) {
  
}

//Render notification using display.
void TinyWatchNotification::drawNotification(TinyScreen display) {
  display.setFont(liberationSans_16ptFontInfo);
  char* text = (char*)"Notifications!";
  int width = display.getPrintWidth(text);
  display.setCursor((96/2) - (width/2), 16);
  display.print(text);
}
