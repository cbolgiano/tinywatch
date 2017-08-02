#include <TinyScreen.h>
#include <SPI.h>
#include <tinywatch-time.h>

const int SCREEN_HEIGHT = 48;
const int SCREEN_WIDTH = 96;
const int SCREEN_CENTER = SCREEN_WIDTH/2;
const int MSG_X_START = SCREEN_WIDTH + 1;
const int FONT_SIZE_OFFSET = 5;

//Determines which version of TinyScreen we are using.
TinyScreen display = TinyScreen(TinyScreenPlus);
char* msg = "";
int msgX = MSG_X_START;
//Temp sleep
char isSleep = 0;

void setup() {
  //TinyScreen display setup.
  display.begin();
  display.setFlip(true);
  display.setBrightness(10);

  //START time plugin.
  TinyWatchTime::setup();
  //END time plugin.
}

void loop() {
  //START time plugin.
  TinyWatchTime::poll();
  TinyWatchTime::drawTime(display);
  TinyWatchTime::drawDate(display);
  //END time plugin.
  
  //TODO: Make plugin to render background.

  //TODO: Make plugin to to render orientation.

  //TODO: Make plugin to handle button presses.

  //TODO: Make plugin to render menu.

  //TODO: Make plugin to handle sleep.

  //TODO: Make plugin to render notifications.

  //TODO: whateva whatev we do what we want...

  //TODO: Make notification plugin and remove this.
  renderMessage();

  //TODO: Make sleep plugin and remove this.
  isSleep ? display.off() : display.on();
  if (display.getButtons(TSButtonUpperLeft)
    && display.getButtons(TSButtonUpperRight)) {
    isSleep = isSleep ? 0 : 1;
    delay(250);
  }
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
