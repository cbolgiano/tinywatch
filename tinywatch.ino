#include <TinyScreen.h>
#include <TimeLib.h>
#include <SPI.h>
#include <BLEPeripheral.h>
#include "lib_RenderBuffer.h"
#include "lib_StringBuffer.h"

//Determines which version of TinyScreen we are using.
TinyScreen display = TinyScreen(TinyScreenPlus);
//Buffer used for drawing.
RenderBuffer<uint16_t,20> buffer;
char isTimeSet = 0;
//Temp sleep
char isSleep = 0;


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
  blePeripheral.setLocalName("tinywatch");
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
}

void loop() {
  blePeripheral.poll();
  BLECentral central = blePeripheral.central();
  
  if(isTimeSet){
    renderBackground();
    renderTime();
    renderDate();
  } else if(!central || !central.connected()){
    buffer.drawText("Searching...",15,8,buffer.rgb(255,255,255), &liberationSans_8ptFontInfo);
  }

  //temp sleep
  isSleep ? display.off() : display.on();
  if(display.getButtons(TSButtonUpperLeft)){
    isSleep = isSleep ? 0 : 1;
    delay(250);
  }
  refreshScreen();
}

void blePeripheralConnectHandler(BLECentral& central) {
  messageWithSecondDelay("Connected...");
}

void blePeripheralDisconnectHandler(BLECentral& central) {
  messageWithSecondDelay("Disconnected...");
}

void setTimeHandler(BLECentral& central, BLECharacteristic& characteristic){
  setTime(timeCharacteristic.valueBE());
  isTimeSet = 1;
}

void messageWithSecondDelay(String msg){
  buffer.drawText(stringBuffer.start().put(msg.c_str()).get(),15,8,buffer.rgb(255,255,255), &liberationSans_8ptFontInfo);
  refreshScreen();
  delay(1000);
}

void refreshScreen(){
  buffer.flush(display);
  stringBuffer.reset();
}

void renderTime(){
  buffer.drawText(stringBuffer.start().put(hour() < 10 ? "0" : "").putDec(hour()).put(":").put(minute() < 10 ? "0" : "").putDec(minute()).put(":").put(second() < 10 ? "0" : "").putDec(second()).get(),22,16,buffer.rgb(255,255,255), &liberationSans_12ptFontInfo); 
}

void renderDate(){
  buffer.drawText(stringBuffer.start().putDec(month()).put("-").putDec(day()).put("-").putDec(year()).get(),28,34,buffer.rgb(255,255,255), &liberationSans_8ptFontInfo);
}

void renderBackground(){
  //Dawn
  if (hour() == 7)
    buffer.drawRect(0,0,96,64)->filledRect(buffer.rgb(98,90,70));
  if (hour() == 8)
    buffer.drawRect(0,0,96,64)->filledRect(buffer.rgb(95,40,20));
  if (hour() == 9)
    buffer.drawRect(0,0,96,64)->filledRect(buffer.rgb(88, 57, 30));
  if (hour() == 10)
    buffer.drawRect(0,0,96,64)->filledRect(buffer.rgb(100, 97, 100));
  if (hour() == 11)
    buffer.drawRect(0,0,96,64)->filledRect(buffer.rgb(100, 100, 100));
  //Sun
  if (hour() == 12)
    buffer.drawRect(0,0,96,64)->filledRect(buffer.rgb(100, 100, 97));
  if (hour() >= 13 && hour() < 20)
    buffer.drawRect(0,0,96,64)->filledRect(buffer.rgb(100, 100, 100));
  //Dusk
  if (hour() == 20)
    buffer.drawRect(0,0,96,64)->filledRect(buffer.rgb(97,85,56));
  //Night
  if (hour() >= 21 || hour() < 7)
    buffer.drawRect(0,0,96,64)->filledRect(buffer.rgb(0, 0, 0));
  //Ocean
  buffer.drawRect(0,48,94,16)->filledRect(buffer.rgb(28, 107, 160));
}

//TODO: Method to render orientation.

//TODO: Method to handle button presses.

//TODO: Method to render menu.

//TODO: Method to handle sleep.

//TODO: Method to render notifications.

//TODO: whateva whatev we do what we want...
