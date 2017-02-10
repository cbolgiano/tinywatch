#include <TimeLib.h>
#include <SPI.h>
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
//Time Characteristic
BLELongCharacteristic timeCharacteristic = BLELongCharacteristic("CCC2", BLEWrite);

void setup() {
  //TinyScreen display setup.
  display.begin();
  display.setFlip(true);
  display.setBrightness(10);
  display.setBitDepth(buffer.is16bit());
    
  bleSetup();
}

void bleSetup(){
  //Name of BLE peripheral when connecting to master.
  blePeripheral.setDeviceName("tinywatch");
  blePeripheral.setAppearance(0xC0);

  //Setting advertising id from service.
  blePeripheral.setAdvertisedServiceUuid(service.uuid());
  //Adding attributes for BLE peripheral.
  blePeripheral.addAttribute(service);
  blePeripheral.addAttribute(timeCharacteristic);

  //Bind events for connects and disconnects.
  blePeripheral.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  blePeripheral.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
  
  timeCharacteristic.setEventHandler(BLEWritten, setTimeHandler);
  
  //Start BLE service.
  blePeripheral.begin();
  messageWithSecondDelay("searching...");
}

void loop() {
  blePeripheral.poll();
  renderTime();
  refreshScreen();
}

void blePeripheralConnectHandler(BLECentral& central) {
  messageWithSecondDelay("connected...");
}

void blePeripheralDisconnectHandler(BLECentral& central) {
  messageWithSecondDelay("disconnected...");
  messageWithSecondDelay("searching...");
}

void setTimeHandler(BLECentral& central, BLECharacteristic& characteristic){
  messageWithSecondDelay("written...");
  setTime(timeCharacteristic.valueBE());
  messageWithSecondDelay("time written...");
}

void messageWithSecondDelay(String msg){
  buffer.drawText(msg.c_str(),15,8,buffer.rgb(255,0,0), &virtualDJ_5ptFontInfo);
  refreshScreen();
  delay(1000);
}

void refreshScreen(){
  buffer.flush(display);
  stringBuffer.reset();
}

//TODO: Method to render date.
void renderTime(){
  buffer.drawText(((String)hour() + ":" + (String)minute() + ":" + (String)second()).c_str(),15,8,buffer.rgb(255,0,0), &virtualDJ_5ptFontInfo);
}

//TODO: Method to render date.
/*void renderDate(){
  buffer.drawText(stringBuffer.start().putDec(month()).put("-").putDec(day()).put("-").putDec(year()).get(),15,16,buffer.rgb(255,0,0), &virtualDJ_5ptFontInfo);
}*/

//TODO: Method to render background.

//TODO: Method to render orientation.

//TODO: Method to handle button presses.

//TODO: Method to render menu.

//TODO: Method to handle sleep.

//TODO: Method to render notifications.

//TODO: whateva whatev we do what we want...
