#include <TinyScreen.h>
#include <TimeLib.h>
#include <SPI.h>
#include <BLEPeripheral.h>
#include "lib_RenderBuffer.h"
#include "lib_StringBuffer.h"

//Pinouts for TinyShield BLE.
#define BLE_REQ 10
#define BLE_RDY 2
#define BLE_RST 9

const int SCREEN_HEIGHT = 48;
const int SCREEN_WIDTH = 96;
const int MSG_X_START = SCREEN_WIDTH + 1;
const int FONT_SIZE_OFFSET = 5;
//Determines which version of TinyScreen we are using.
TinyScreen display = TinyScreen(TinyScreenPlus);
//Buffer used for drawing.
RenderBuffer<uint16_t, 20> buffer;
char* msg = "";
int rBackground = 0;
int gBackground = 0;
int bBackground = 0;
int msgX = MSG_X_START;
char isTimeSet = 0;
//Temp sleep
char isSleep = 0;

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

void bleSetup() {
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

  if (isTimeSet) {
    renderBackground();
    renderTime();
    renderDate();
  } else if (!central || !central.connected()) {
    buffer.drawText("Searching...", 15, 8, buffer.rgb(255, 255, 255), &liberationSans_8ptFontInfo);
  }
  renderMessage();

  //temp sleep
  isSleep ? display.off() : display.on();
  if (display.getButtons(TSButtonUpperLeft)
    && display.getButtons(TSButtonUpperRight)) {
    isSleep = isSleep ? 0 : 1;
    delay(250);
  }

  refreshScreen();
}

void blePeripheralConnectHandler(BLECentral& central) {
  msg = "Connected...";
  msgX = MSG_X_START;
}

void blePeripheralDisconnectHandler(BLECentral& central) {
  msg = "Disconnected...";
  msgX = MSG_X_START;
}

void setTimeHandler(BLECentral& central, BLECharacteristic& characteristic) {
  setTime(timeCharacteristic.valueBE());
  isTimeSet = 1;
}

int centerX(){
  return SCREEN_WIDTH/2;
}

void refreshScreen() {
  buffer.flush(display);
  stringBuffer.reset();
}

void renderTime() {
  char* timeString = stringBuffer.start().put(hour() < 10 ? "0" : "").putDec(hour()).put(":").put(minute() < 10 ? "0" : "").putDec(minute()).put(":").put(second() < 10 ? "0" : "").putDec(second()).get();
  buffer.drawText(timeString, centerX() - 36, 16, buffer.rgb(255, 255, 255), &liberationSans_16ptFontInfo);
}

void renderDate() {
  char* dateString = stringBuffer.start().put(month() < 10 ? "0" : "").putDec(month()).put("-").put(day() < 10 ? "0" : "").putDec(day()).put("-").put(year() < 10 ? "0" : "").putDec(year()).get();
  buffer.drawText(dateString, centerX() - 33, 34, buffer.rgb(255, 255, 255), &liberationSans_10ptFontInfo);
}

void renderBackground() {
  buffer.drawRect(0, 0, 96, 64)->filledRect(buffer.rgb(rBackground, gBackground, bBackground));
}

void renderMessage(){
  int msgLength = strlen(msg) * FONT_SIZE_OFFSET;
  if(msg != "" && msgX > -msgLength){
    buffer.drawText(msg, msgX, 48, buffer.rgb(255, 255, 255), &liberationSans_8ptFontInfo);
    msgX--;
  } else{
    msg = "";
    msgX = MSG_X_START;
  }
}

//TODO: Method to render orientation.

//TODO: Method to handle button presses.

//TODO: Method to render menu.

//TODO: Method to handle sleep.

//TODO: Method to render notifications.

//TODO: whateva whatev we do what we want...
