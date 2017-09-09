#ifndef _TINYWATCH_NOTIFICATION_H_
#define _TINYWATCH_NOTIFICATION_H_

#ifndef _ARDUINO_H_
#include <Arduino.h>
#endif

#ifndef _TINYSCREEN_H_
#include <TinyScreen.h>
#endif

#ifndef _BLE_PERIPHERAL_H_
#include <BLEPeripheral.h>
#endif

namespace TinyWatchNotification{  
  //Setup for notifications plugin.
  void setup(BLEPeripheral& existingPeripheral);

  //Capture notification.
  void setNotificationHandler(BLECentral& central, BLECharacteristic& characteristic);

  //Render notification using display.
  void drawNotification(TinyScreen display);
}

#endif
