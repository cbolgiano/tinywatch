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

#ifndef _TINYWATCH_BUTTON_H_ //NOLINT
#define _TINYWATCH_BUTTON_H_

#ifndef _TINYSCREEN_H_
#include <TinyScreen.h>
#endif

namespace TinyWatchButton {
  // Returns 1 if upper left button is pressed.
  int isUpperLeft(TinyScreen display);

  // Returns 1 if upper right button is pressed.
  int isUpperRight(TinyScreen display);

  // Returns 1 if lower left button is pressed.
  int isLowerLeft(TinyScreen display);

  // Returns 1 if lower right button is pressed.
  int isLowerRight(TinyScreen display);

  // Returns 1 if any button is pressed.
  int isAny(TinyScreen display);
}  // namespace TinyWatchButton

#endif  // _TINYWATCH_BUTTON_H_ NOLINT
