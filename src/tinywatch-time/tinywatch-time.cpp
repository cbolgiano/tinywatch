#include "tinywatch-time.h"

//Time Characteristic
BLELongCharacteristic timeCharacteristic = BLELongCharacteristic("CCC1", BLEWrite);

//Setup for time plugin.
void TinyWatchTime::setup(BLEPeripheral existingPeripheral){
  existingPeripheral.addAttribute(timeCharacteristic);

  timeCharacteristic.setEventHandler(BLEWritten, setTimeHandler);
}

//Set time in TimeLib when value is written to timeCharacteristic.
void TinyWatchTime::setTimeHandler(BLECentral& central, BLECharacteristic& characteristic) {
  setTime(timeCharacteristic.valueBE());
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
void TinyWatchTime::drawTime(TinyScreen display) {
  display.setFont(liberationSans_16ptFontInfo);
  char* timeText = (char*)getTimeToRender(now());
  int width = display.getPrintWidth(timeText);
  display.setCursor((96/2) - (width/2), 16);
  display.print(timeText);
}

//Render date using display.
void TinyWatchTime::drawDate(TinyScreen display) {
  display.setFont(liberationSans_10ptFontInfo);
  char* dateText = (char*)getDateToRender(now());
  int width = display.getPrintWidth(dateText);
  display.setCursor((96/2) - (width/2), 34);
  display.print(dateText);
}

//Render time using display, x, y, and font.
void TinyWatchTime::drawTime(TinyScreen display, int x, int y, FONT_INFO fontDescriptor) {
  display.setFont(fontDescriptor);
  char* timeText = (char*)getTimeToRender(now());
  int width = display.getPrintWidth(timeText);
  display.setCursor(x, y);
  display.print(timeText);
}

//Render date using display, x, y, and font.
void TinyWatchTime::drawDate(TinyScreen display, int x, int y, FONT_INFO fontDescriptor) {
  display.setFont(fontDescriptor);
  char* dateText = (char*)getDateToRender(now());
  int width = display.getPrintWidth(dateText);
  display.setCursor(x, y);
  display.print(dateText);
}
