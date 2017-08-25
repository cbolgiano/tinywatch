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

const int SCREEN_HEIGHT = 48;
const int SCREEN_WIDTH = 96;
const int SCREEN_CENTER = SCREEN_WIDTH/2;
const int MSG_X_START = SCREEN_WIDTH + 1;
const int FONT_SIZE_OFFSET = 5;

//Determines which version of TinyScreen we are using.
TinyScreen display = TinyScreen(TinyScreenPlus);
char* msg = "";
int msgX = MSG_X_START;

void setup() {
  //TinyScreen display setup.
  display.begin();
  display.setFlip(true);
  display.setBrightness(10);

#ifdef _BLE_ENABLED_
  //START time plugin.
  TinyWatchTime::setup(bLEPeripheral);
  //END time plugin.
#endif

#ifdef _BLE_ENABLED_
  //START notification plugin.
  TinyWatchNotification::setup(bLEPeripheral);
  //END notification plugin.
#endif

#ifdef _BLE_ENABLED_
  //Setting advertising id from service.                                                                                                        
  bLEPeripheral.setAdvertisedServiceUuid(tinywatchService.uuid());
  //Adding attributes for BLE peripheral.                                                                                                       
  bLEPeripheral.addAttribute(tinywatchService);
  bLEPeripheral.setLocalName("tinywatch");
  //Start BLE service.                                                                                                                          
  bLEPeripheral.begin();
#endif
}

void loop() {
  
#ifdef _BLE_ENABLED_
  bLEPeripheral.poll();
#endif

#ifdef _BLE_ENABLED_
  //START time plugin.
  TinyWatchTime::drawTime(display);
  TinyWatchTime::drawDate(display);
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

  //TODO: Make notification plugin and remove this.
//  renderMessage();
}

//TODO: Make notification plugin and remove this.
void renderMessage(){
  int width = display.getPrintWidth(msg);
  if(msg != "" && msgX > -width){
    display.setFont(liberationSans_8ptFontInfo);
    display.setCursor(msgX,48);
    display.print(msg);
    msgX--;
  } else{
    msg = "";
    msgX = MSG_X_START;
  }
}
