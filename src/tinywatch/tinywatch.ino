#include <TinyScreen.h>
#include <SPI.h>
#include <tinywatch-time.h>
#include <tinywatch-notification.h>
#include <tinywatch-sleep.h>

#if defined(_TINYWATCH_TIME_H_) || defined(_TINYWATCH_NOTIFICATION_H_)
#define _BLE_ENABLED_
unsigned char BLE_REQ = 10;
unsigned char BLE_RDY = 2;
unsigned char BLE_RST = 9;

//Instantiate BLE peripheral.
BLEPeripheral bLEPeripheral = BLEPeripheral(BLE_REQ, BLE_RDY, BLE_RST);
BLEService tinywatchService = BLEService("CCC0");
#endif

//Determines which version of TinyScreen we are using.
TinyScreen display = TinyScreen(TinyScreenPlus);

void setup() {
  //TinyScreen display setup.
  display.begin();
  display.setFlip(true);
  display.setBrightness(10);

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

  //START time plugin.
  TinyWatchTime::drawTime(display);
  TinyWatchTime::drawDate(display);
  //END time plugin.

  //START time plugin.
  TinyWatchNotification::drawNotification(display);
  //END time plugin.
#endif

  //START sleep plugin
  TinyWatchSleep::sleep(display);
  //END sleep plugin

  //TODO: Make plugin to render background.

  //TODO: Make plugin to to render orientation.

  //TODO: Make plugin to handle button presses.

  //TODO: Make plugin to render menu.

  //TODO: Make plugin to handle sleep.

  //TODO: Make plugin to render notifications.

  //TODO: whateva whatev we do what we want...

}
