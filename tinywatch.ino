#include <TimeLib.h>
#include <SPI.h>
#include <BLEPeripheral.h>
#include "BLESerial.h"
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

BLESerial BLESerial(BLE_REQ, BLE_RDY, BLE_RST);
String value = "";
int hours = 0;
int minutes = 0;
int seconds = 0;
int isTimeSet = 0;
  
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
  BLESerial.setLocalName("tinywatch");
  
  //Start BLE service.
  BLESerial.begin();
}

void loop() {
  BLECentral central = BLESerial.central();
  if(central){
    messageWithSecondDelay("connected...");
    while(central.connected()){
      read();
      renderTime();
    }
    messageWithSecondDelay("disconnected...");
  } else{    
    messageWithSecondDelay("searching...");
  }
}

void read() {
  if (BLESerial) {
    String receivedValue = "";
    int byte;
    while ((byte = BLESerial.read()) > 0){
      receivedValue += (char)byte;
    }

    if(receivedValue.length() > 0){
      if(receivedValue.substring(0, 2) == "T:"){
        parseRXForTime(receivedValue);
      } else{
        value = receivedValue;
      }
    }
    BLESerial.flush();
  }

  if(value.length() > 0){
    messageWithSecondDelay(value);
  }
}

void parseRXForTime(String receivedValue){
  for(int i = 0; i < receivedValue.length(); i++){
    if(receivedValue.substring(i, i+2) == "H:"){
      hours = receivedValue.substring(i+2, i+4).toInt();
    } else if(receivedValue.substring(i, i+2) == "m:"){
      minutes = receivedValue.substring(i+2, i+4).toInt();
    } else if(receivedValue.substring(i, i+2) == "S:"){
      seconds = receivedValue.substring(i+2, i+4).toInt();
    }
  }

  if(!isTimeSet){
    if(hours && minutes && seconds){
      setTime(hours, minutes, seconds, 0, 0, 0);
      isTimeSet = 1;
    }
  }
}

void renderTime(){
  if(isTimeSet){
    buffer.drawText(stringBuffer.start().putDec(hour()).put(":").putDec(minute()).put(":").putDec(second()).get(),96/2,96/2,buffer.rgb(255,0,0), &virtualDJ_5ptFontInfo);
    refreshScreen();
  }
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
