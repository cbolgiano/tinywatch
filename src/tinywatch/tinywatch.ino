/*
  tinywatch

  Controls TinyScreen+, BLE Nordic Tinyshield, Proto Board Tinyshield, Li-po Battery 3.7V 270mAh, and DC3V/0.1A 1.5V/0.05A 10x2.7mm Coin Mobile Phone Vibration Motor to work as a smart watch.

  The circuit:
    * The Proto Tinyshield uses pins:
    ** 5 and 6 set to output
    * The BLE Tinyshield uses pins:
    ** 2-SPI_IRQ: Interupts output from nRF8001 to the tinyscreen+
    ** 9-BLE_RST: Reset signal to the nRF8001
    ** 10-SPI_CS: SPI chip select for the nRF8001
    ** 11-MOSI: SPI data from tinyscreen+ to transceiver
    ** 12-MISO: SPI data from transceiver to tinyscreen+
    ** 13-SCLK: Serial SPI clock from tinyscreen+ to tranceiver 

*/

#include <tinywatch-time.h>
#include <tinywatch-display.h>
#include <tinywatch-notification.h>
#include <tinywatch-sleep.h>

//Width of tinyscreen+'s display in pixels.
const int SCREEN_WIDTH = 96;
//Center X coordinate of tinyscreen+.
const int SCREEN_CENTER = SCREEN_WIDTH / 2;
int piezoPins = { 5, 6 };
//Notification flag. True if notification is rendered.
extern int isNotification;

//True if tinywatch-time or tinywatch-notification is included.
#if defined(_TINYWATCH_TIME_H_) || defined(_TINYWATCH_NOTIFICATION_H_)

//Derective that enables BLE.
#define _BLE_ENABLED_

//SPI chip select for the nRF8001.
const unsigned char BLE_REQ = 10;
//Interrupt output from the nRF8001 to the tinyscreen+.
const unsigned char BLE_RDY = 2;
//Reset signal to the nRF8001.
const unsigned char BLE_RST = 9;

//BLE device and pin configuration.
BLEPeripheral bLEPeripheral = BLEPeripheral(BLE_REQ, BLE_RDY, BLE_RST);
//BLE device's service with uuid.
//TODO: Generate uuid.
BLEService tinywatchService = BLEService("CCC0");
#endif

void setup() {
  //Set piezoPins[0] and piezoPins[1] to OUTPUT to send current to piezo element.
  pinMode(piezoPins[0], OUTPUT);
  pinMode(piezoPins[1], OUTPUT);

  //START display plugin.
  TinyWatchDisplay::setup();
  //END display plugin.

#ifdef _BLE_ENABLED_
  //Name of BLE device when pairing with host device.
  bLEPeripheral.setLocalName("tinywatch");
  //Setting advertising id from service.
  bLEPeripheral.setAdvertisedServiceUuid(tinywatchService.uuid());
  //Adding attributes for BLE peripheral.
  bLEPeripheral.addAttribute(tinywatchService);
  
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

  //Do not draw time and date when notification is rendered.
  if(!isNotification){
    //START time plugin.
    TinyWatchTime::drawTime(TinyWatchDisplay::getDisplay());
    TinyWatchTime::drawDate(TinyWatchDisplay::getDisplay());
    //END time plugin.
  }
  //START notification plugin.
  TinyWatchNotification::drawNotification(TinyWatchDisplay::getDisplay());
  TinyWatchNotification::vibrate();
  //END notification plugin.
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
