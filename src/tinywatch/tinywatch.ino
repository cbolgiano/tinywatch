#include <tinywatch-time.h>
#include <tinywatch-display.h>
#include <tinywatch-notification.h>
#include <tinywatch-sleep.h>

const int SCREEN_WIDTH = 96;
int SCREEN_CENTER = SCREEN_WIDTH / 2;
int piezoPin = A2;

extern int isNotification;

#if defined(_TINYWATCH_TIME_H_) || defined(_TINYWATCH_NOTIFICATION_H_)
#define _BLE_ENABLED_
const unsigned char BLE_REQ = 10;
const unsigned char BLE_RDY = 2;
const unsigned char BLE_RST = 9;

//Instantiate BLE peripheral.
BLEPeripheral bLEPeripheral = BLEPeripheral(BLE_REQ, BLE_RDY, BLE_RST);
BLEService tinywatchService = BLEService("CCC0");
#endif

void setup() {
  //Set piezoPin to OUTPUT to send current to piezo.
  pinMode(piezoPin, OUTPUT);
  //START display plugin.
  TinyWatchDisplay::setup();
  //END display plugin.

#ifdef _BLE_ENABLED_
  bLEPeripheral.setLocalName("tinywatch");
  //Setting advertising id from service.
  bLEPeripheral.setAdvertisedServiceUuid(tinywatchService.uuid());
  //Adding attributes for BLE peripheral.
  bLEPeripheral.addAttribute(tinywatchService);
  //Start BLE service.

  //START time plugin.
  TinyWatchTime::setup(bLEPeripheral);
  //END time plugin.

  //START notification plugin.
  TinyWatchNotification::setup(bLEPeripheral);
  //END notification plugin.

  bLEPeripheral.begin();
#endif
}

void loop() {
  
#ifdef _BLE_ENABLED_
  bLEPeripheral.poll();

  if(!isNotification){
    //START time plugin.
    TinyWatchTime::drawTime(TinyWatchDisplay::getDisplay());
    TinyWatchTime::drawDate(TinyWatchDisplay::getDisplay());
    //END time plugin.
  }
  //START time plugin.
  TinyWatchNotification::drawNotification(TinyWatchDisplay::getDisplay());
  //END time plugin.
#endif

  //START sleep plugin
  TinyWatchSleep::sleep(TinyWatchDisplay::getDisplay());
  //END sleep plugin

  //START display plugin.
  TinyWatchDisplay::manageDisplay();
  //END display plugin.

  //TODO: Make plugin to render background.

  //TODO: Make plugin to to render orientation.

  //TODO: Make plugin to handle button presses.

  //TODO: Make plugin to render menu.

  //TODO: whateva whateva we do what we want...

}
