#include <SPI.h>
#include <TimeLib.h>
#include <BLEPeripheral.h>
#include "lib_RenderBuffer.h"
#include "lib_StringBuffer.h"

//Determines which version of TinyScreen we are using.
TinyScreen display = TinyScreen(TinyScreenPlus);
//Buffer used for drawing.
RenderBuffer<uint8_t,20> buffer;

//Pinouts for TinyShield BLE.
#define BLE_REQ 10
#define BLE_RDY 2
#define BLE_RST 9

//Instantiate BLE peripheral.
BLEPeripheral blePeripheral = BLEPeripheral(BLE_REQ, BLE_RDY, BLE_RST);

//Uniquely identifies BLE peripheral, used for advertising.
BLEService service = BLEService("CCC0");
//Description of content sent via BLE peripheral.
BLEDescriptor desc = BLEDescriptor("CCC1", "One Watch to Rule Them All!");
//Time Characteristic
BLELongCharacteristic time = BLELongCharacteristic("CCC2", BLERead | BLEWrite);

void setup() {
  //TinyScreen display setup.
  display.begin();
  display.setFlip(true);
  display.setBrightness(8);
  display.setBitDepth(buffer.is16bit());
  bleSetup();
}

void loop(void) {
  blePeripheral.poll();
  renderTime();
}

void bleSetup(){
  messageWithSecondDelay("searching...");
  
  //Name of BLE peripheral when connecting to master.
  blePeripheral.setLocalName("tinywatch");

  //Setting advertising id from service.
  blePeripheral.setAdvertisedServiceUuid(service.uuid());
  //Adding attributes for BLE peripheral.
  blePeripheral.addAttribute(service);
  blePeripheral.addAttribute(desc);
  blePeripheral.addAttribute(time);

  //Bind events for connects and disconnects.
  blePeripheral.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  blePeripheral.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  //Start BLE service.
  blePeripheral.begin();
}

void blePeripheralConnectHandler(BLECentral& central) {
  messageWithSecondDelay("connected...");
  //Get initial time from central.
  setTime(time.value());
}

void blePeripheralDisconnectHandler(BLECentral& central) {
  messageWithSecondDelay("disconnected...");
  messageWithSecondDelay("searching...");
}

void renderTime(){
  if(time.value()){
    buffer.drawText(stringBuffer.start().put(time.value()).get(),15,8,buffer.rgb(255,0,0), &virtualDJ_5ptFontInfo);
    //buffer.drawText(stringBuffer.start().putDec(hour()).put(":").putDec(minute()).put(":").putDec(second()).get(),15,8,buffer.rgb(255,0,0), &virtualDJ_5ptFontInfo);
    refreshScreen();
  }
}

void refreshScreen(){
  buffer.flush(display);
  stringBuffer.reset();
}

void messageWithSecondDelay(const char* msg){
  buffer.drawText(stringBuffer.start().put(msg).get(),15,8,buffer.rgb(255,0,0), &virtualDJ_5ptFontInfo);
  refreshScreen();
  delay(1000);
}

//TODO: Method to render date.
/*void renderDate(unsigned int n){
  buffer.drawText(stringBuffer.start().putDec(month()).put("-").putDec(day()).put("-").putDec(year()).get(),15,16,buffer.rgb(255,0,0), &virtualDJ_5ptFontInfo);
}*/

//TODO: Method to render background.

//TODO: Method to render orientation.

//TODO: Method to handle button presses.

//TODO: Method to render menu.

//TODO: Method to handle sleep.

//TODO: Method to render notifications.

//TODO: whateva whatev we do what we want...
