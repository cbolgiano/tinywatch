/*
MIT License

Copyright (c) 2018 Christopher Bolgiano

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "tinywatch-battery.h"  // NOLINT

extern int SCREEN_CENTER;

// Draw batter level line.
void TinyWatchBattery::drawBatteryLevel(TinyScreen display) {
  int width = 26;
  drawBatteryLevel(display, SCREEN_CENTER - (width/2)
    , 62, 2, width);
}

// Draw battery level line at location (x,y) at a specific
// height using display. Using internal voltage reference.
void TinyWatchBattery::drawBatteryLevel(TinyScreen display
  , int x, int y, int height, int width) {
  int result = 0;

  // Only checks for low battery due to hardware limitation:
  // http://forum.tinycircuits.com/index.php?topic=1599.0

  // START - Code found in Tinycircuits TinyScreen_SmartWatch Project
  SYSCTRL->VREF.reg |= SYSCTRL_VREF_BGOUTEN;
  while (ADC->STATUS.bit.SYNCBUSY == 1); // NOLINT
  ADC->SAMPCTRL.bit.SAMPLEN = 0x1;
  while (ADC->STATUS.bit.SYNCBUSY == 1); // NOLINT
  // Internal bandgap input
  ADC->INPUTCTRL.bit.MUXPOS = 0x19;
  while (ADC->STATUS.bit.SYNCBUSY == 1); // NOLINT
  // Enable ADC
  ADC->CTRLA.bit.ENABLE = 0x01;
  // Start conversion
  while (ADC->STATUS.bit.SYNCBUSY == 1); // NOLINT
  ADC->SWTRIG.bit.START = 1;
  // Clear the Data Ready flag
  ADC->INTFLAG.bit.RESRDY = 1;
  // Start conversion again, since The first
  // conversion after the reference is changed must not be used.
  while (ADC->STATUS.bit.SYNCBUSY == 1); // NOLINT
  ADC->SWTRIG.bit.START = 1;
  // Store the value
  // Waiting for conversion to complete
  while ( ADC->INTFLAG.bit.RESRDY == 0 ); // NOLINT
  uint32_t valueRead = ADC->RESULT.reg;
  while (ADC->STATUS.bit.SYNCBUSY == 1); // NOLINT
  // Disable ADC
  ADC->CTRLA.bit.ENABLE = 0x00;
  while (ADC->STATUS.bit.SYNCBUSY == 1); // NOLINT
  SYSCTRL->VREF.reg &= ~SYSCTRL_VREF_BGOUTEN;

  result = (((1100L * 1024L) / valueRead) + 5L) / 10L;
  // END - Code found in Tinycircuits TinyScreen_SmartWatch Project

  //Draw battery display.
  display.drawRect(x, y, 30
    , height, TSRectangleFilled
    , (result > 325 ? TS_8b_Green : TS_8b_Red));
}
