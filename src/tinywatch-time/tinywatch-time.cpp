#include "tinywatch-time.h"

extern int SCREEN_CENTER;

//Time Characteristic
BLELongCharacteristic timeCharacteristic = BLELongCharacteristic("CCC1", BLEWrite);

//Setup for time plugin.
void TinyWatchTime::setup(BLEPeripheral& existingPeripheral){
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
  if(isTimeSet(t)){
    return String(addZeroPrefix(hour(t))
      + String(hour(t))
      + ":"
      + addZeroPrefix(minute(t))
      + String(minute(t))
      + ":"
      + addZeroPrefix(second(t))
      + String(second(t))).c_str();
  } else{
    return "";
  }
}

//Returns a const char* that represents
//the current date.
const char* TinyWatchTime::getDateToRender(time_t t) {
  if(isTimeSet(t)){
    return String(addZeroPrefix(month(t))
      + String(month(t))
      + "-"
      + addZeroPrefix(day(t))
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
  display.setCursor(SCREEN_CENTER - (width/2), 16);
  display.print(timeText);
}

//Render date using display.
void TinyWatchTime::drawDate(TinyScreen display) {
  display.setFont(liberationSans_10ptFontInfo);
  char* dateText = (char*)getDateToRender(now());
  int width = display.getPrintWidth(dateText);
  display.setCursor(SCREEN_CENTER - (width/2), 34);
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

//START - Helper functions
 
//Add "0" if needed to time.
String TinyWatchTime::addZeroPrefix(int time){
  return String(time < 10 ? "0" : "");
}

//Determine if value for time is set.
int TinyWatchTime::isTimeSet(time_t t){
  return t && timeStatus() != timeNotSet;
}

//END - Helper functions
