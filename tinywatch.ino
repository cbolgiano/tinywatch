#include <BGLib.h>
#include <BGLibConfig.h>

#include <SPI.h>
#include <TimeLib.h> //include the Arduino Time library
#include "lib_RenderBuffer.h"
#include "lib_StringBuffer.h"

TinyScreen display = TinyScreen(TinyScreenPlus);
RenderBuffer<uint8_t,20> buffer;

#define BLE_DEBUG false
uint8_t ble_rx_buffer[21];
uint8_t ble_rx_buffer_len = 0;
uint8_t ble_connection_state = false;
uint8_t ble_connection_displayed_state = true;

void setup() {
    display.begin();
    display.setFlip(true);
    display.setBrightness(8);
    display.setBitDepth(buffer.is16bit());

    setTime(13,19,55,6,3,2016); //values in the order hr,min,sec,day,month,year
}

void loop(void) {
  unsigned int n = millis() >> 4;

  renderTime(n);
  renderDate(n);

  buffer.flush(display);
  stringBuffer.reset();
}

void renderTime(unsigned int n){
  buffer.drawText(stringBuffer.start().putDec(hour()).put(":").putDec(minute()).put(":").putDec(second()).get(),15,8,buffer.rgb(255,0,0), &virtualDJ_5ptFontInfo);
}

void renderDate(unsigned int n){
  buffer.drawText(stringBuffer.start().putDec(month()).put("-").putDec(day()).put("-").putDec(year()).get(),15,16,buffer.rgb(255,0,0), &virtualDJ_5ptFontInfo);
}

//TODO: Method to render background.

//TODO: Method to render orientation.

//TODO: Method to handle button presses.

//TODO: Method to render menu.

//TODO: Method to handle sleep.

//TODO: Method to render notifications.

//TODO: whateva whatev we do what we want...
