/*
  TwoWDMotor.h - Library for the management of 2 DC motors across a H bridge.
  Created by Leonardo Sammartano supported from DarioMAS, 06/03/2020.
*/

/*
Il presente software è soggetto al contratto di licenza noto come
"MIT License" riportato di seguito

The MIT License

Copyright (c) 2010-2020 Google, Inc. http://angularjs.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef TwoWDMotor_h
#define TwoWDMotor_h

#include "Arduino.h"

#define Versione "0.0.00"
#define Del "06/03/2020"

class TwoWDMotor
{
  public:
    TwoWDMotor(uint8_t DxPWM, uint8_t DxDir, uint8_t SxPWM, uint8_t SxDir);
    void Help(Stream &Output);
    void Marcia(int8_t DxSpeed, int8_t SxSpeed);

    uint8_t _DxVerso = true;
    uint8_t _SxVerso = true;
    uint16_t _PWMResolution = 255;

  private:
  uint8_t _DxPWM, _DxDir, _SxPWM, _SxDir;
};

#endif
