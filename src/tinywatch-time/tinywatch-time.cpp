#include "tinywatch-time.h"

//Pinouts for TinyShield BLE.
unsigned char TIME_BLE_REQ = 10;
unsigned char TIME_BLE_RDY = 2;
unsigned char TIME_BLE_RST = 9;
  
//Instantiate BLE peripheral.
BLEPeripheral timeBLEPeripheral = BLEPeripheral(TIME_BLE_REQ, TIME_BLE_RDY, TIME_BLE_RST);

//Uniquely identifies BLE peripheral, used for advertising.
BLEService timeService = BLEService("CCC0");

//Time Characteristic
BLELongCharacteristic timeCharacteristic = BLELongCharacteristic("CCC2", BLEWrite);

//Setup for time plugin.
void TinyWatchTime::twTimeSetup(){
  //Name of BLE peripheral when connecting to master.
  timeBLEPeripheral.setLocalName("tinywatch");

  //Setting advertising id from service.
  timeBLEPeripheral.setAdvertisedServiceUuid(timeService.uuid());
  //Adding attributes for BLE peripheral.
  timeBLEPeripheral.addAttribute(timeService);
  timeBLEPeripheral.addAttribute(timeCharacteristic);

  timeCharacteristic.setEventHandler(BLEWritten, setTimeHandler);

  //Start BLE service.
  timeBLEPeripheral.begin();
}

//Set time in TimeLib when value is written to timeCharacteristic.
void TinyWatchTime::setTimeHandler(BLECentral& central, BLECharacteristic& characteristic) {
  setTime(timeCharacteristic.valueBE());
}

//BLE poll for timeCharacteristic value change.
void TinyWatchTime::pollTime(){
  timeBLEPeripheral.poll();
}

//Returns a const char* that represents
//the current time.
const char* TinyWatchTime::getTimeToRender(time_t t){
  if(t && timeStatus() != timeNotSet){
    return String((hour(t) < 10 ? "0" : "")
      + String(hour(t))
      + ":"
      + (minute(t) < 10 ? "0" : "")
      + String(minute(t))
      + ":"
      + (second(t) < 10 ? "0" : "")
      + String(second(t))).c_str();
  } else{
    return "";
  }
}

//Returns a const char* that represents
//the current date.
const char* TinyWatchTime::getDateToRender(time_t t) {
  if(t && timeStatus() != timeNotSet){
    return String((month(t) < 10 ? "0" : "")
      + String(month(t))
      + "-"
      + (day(t) < 10 ? "0" : "")
      + String(day(t))
      + "-"
      + String(year(t))).c_str();
  } else{
    return "";
  }
}

//Render time using display.
void TinyWatchTime::renderTime(TinyScreen display) {
  display.setFont(liberationSans_16ptFontInfo);
  char* timeText = (char*)getTimeToRender(now());
  int width = display.getPrintWidth(timeText);
  display.setCursor((96/2) - (width/2), 16);
  display.print(timeText);
}

//Render date using display.
void TinyWatchTime::renderDate(TinyScreen display) {
  display.setFont(liberationSans_10ptFontInfo);
  char* dateText = (char*)getDateToRender(now());
  int width = display.getPrintWidth(dateText);
  display.setCursor((96/2) - (width/2), 34);
  display.print(dateText);
}
