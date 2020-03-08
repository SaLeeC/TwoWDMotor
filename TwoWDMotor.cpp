/*
  TwoWDMotor.cpp - Library for the management of 2 DC motors across a H bridge.
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

#include "Arduino.h"
#include "TwoWDMotor.h"

TwoWDMotor::TwoWDMotor(uint8_t DxPWM, uint8_t DxDir, uint8_t SxPWM, uint8_t SxDir)
{
  _DxPWM = DxPWM;
  _SxPWM = SxPWM;
  _DxDir = DxDir;
  _SxDir = SxDir;
  pinMode(DxPWM, OUTPUT);
  pinMode(DxDir, OUTPUT);
  analogWrite(DxPWM, 0);
  pinMode(SxPWM, OUTPUT);
  pinMode(SxDir, OUTPUT);
  analogWrite(DxPWM, 0);
}

void TwoWDMotor::Marcia(int8_t DxSpeed, int8_t SxSpeed)
{
  //Gestisce il verso di rotazione del motore Dx (1)
  if(DxSpeed>0)// Il valore della velocità è positivo?
  {
    digitalWrite(_DxDir, _DxVerso);//Se si setta il verso di rotazione come impostato
  }
  else
  {
    if(DxSpeed<0)// Il valore della velocità è negativo
    {
    digitalWrite(_DxDir, !_DxVerso);//Se si setta il verso di rotazione invertito rispetto all'impostazione
    }
  }
  //Setta la velocità trasformando la percentuale in parametro di controllo del PWM
  digitalWrite(_DxPWM, ((_PWMResolution/100)*abs(DxSpeed)));

  //Gestisce il verso di rotazione del motore Sx (2)
  if(SxSpeed>0)// Il valore della velocità è positivo?
  {
    digitalWrite(_SxDir, _SxVerso);//Se si setta il verso di rotazione come impostato
  }
  else
  {
    if(SxSpeed<0)// Il valore della velocità è negativo
    {
    digitalWrite(_SxDir, !_SxVerso);//Se si setta il verso di rotazione invertito rispetto all'impostazione
    }
  }
  //Setta la velocità trasformando la percentuale in parametro di controllo del PWM
  digitalWrite(_SxPWM, ((_PWMResolution/100)*abs(SxSpeed)));
}

void TwoWDMotor::Impulso(uint16_t _DxImp, uint16_t _SxImp)
{
  uint8_t caso;
  unsigned long TzDx, TzSx;
  
  if(_DxImp == 0 & _SxImp == 0)
  {
    caso = 0;
  }
  else
  {
    if(_DxImp > 0 & _SxImp == 0)
    {
      caso = 1;
    }
    else
    {
      if(_DxImp == 0 & _SxImp > 0)
      {
        caso = 2;
      }
      else
      {
        if(_DxImp == _SxImp)
        {
          caso = 3;
        }
        else
        {
          caso = 4;
        }
      }
    }
  }

  switch (caso)
  {
    case 0://Nessun impulso
      break;
    case 1://Impulso sul solo canale Dx
      TzDx = millis() + _DxImp;
      digitalWrite(_DxPWM,HIGH);
      while(millis() <= TzDx)
      {
        //aspetta
      }
      digitalWrite(_DxPWM,LOW);
      break;
    case 2://Impulso sul solo canale Sx
      TzSx = millis() + _SxImp;
      digitalWrite(_SxPWM,HIGH);
      while(millis() <= TzSx)
      {
        //aspetta
      }
      digitalWrite(_SxPWM,LOW);
      break;
    case 3://Impulso uguale sui canali Dx e Sx
      TzDx = millis() + _DxImp;
      digitalWrite(_DxPWM,HIGH);
      digitalWrite(_SxPWM,HIGH);
      while(millis() <= TzDx)
      {
        //aspetta
      }
      digitalWrite(_DxPWM,LOW);
      digitalWrite(_SxPWM,LOW);
      break;
    case 4://Impulsi diversi sui due canali
      TzDx = millis() + _DxImp;
      TzSx = millis() + _SxImp;
      if (TzDx > TzSx)
      {
        while(millis() <= TzDx)
        {
          //aspetta
        }
        digitalWrite(_DxPWM,LOW);
        while(millis() <= TzSx)
        {
          //aspetta
        }
        digitalWrite(_SxPWM,LOW);
      }
      else
      {
        while(millis() <= TzSx)
        {
          //aspetta
        }
        digitalWrite(_SxPWM,LOW);
        while(millis() <= TzDx)
        {
          //aspetta
        }
        digitalWrite(_DxPWM,LOW);
      }      
      break;
    default:
      break;
  }  
}


void TwoWDMotor::Help(Stream &Output)
{
  Output.println("TwoWDMotori - Help");
  Output.print("Versione ");
  Output.print(Versione);
  Output.print(" del ");
  Output.println(Del);
  Output.println("Libreria per il controllo di mezzi con due motori in CC controllati");
  Output.println("tramite PWM e ponte H.");
  Output.println("1 pin per il PWM e 1 pin per la direzione di rotazione");
  Output.println("----------------------------------------------------------------");
  Output.println("Creazione oggetto 'motori'");
  Output.println("TwoWDMotor motori(pin PWM 1, pin Direzione 1, pin PWM 2, pin Direzione 2);");
  Output.println("----------------------------------------------------------------");
  Output.println("Parametri aggiuntivi di configurazione");
  Output.println("_DxVerso=true Senso di rotazione del motore DESTRO invariato");
  Output.println("        =false Senso di rotazione del motore DESTRO invertito");
  Output.println("        default true");
  Output.println("_SxVerso=true Senso di rotazione del motore SINISTRO invariato");
  Output.println("        =false Senso di rotazione del motore SINISTRO invertito");
  Output.println("        default true");
  Output.println("_PWMResolution=[0-65535] Risoluzione del PWM (vedi manuale della scheda)");
  Output.println("        default 255");
  Output.println("----------------------------------------------------------------");
  Output.println("motori.Marcia(Velocità 1, Velocità 2)");
  Output.println("        Il parametro Velocità va da -100 a 100 dove -100 è la");
  Output.println("        massima velocità indietro e 100 è la massima velocità in");
  Output.println("        avanti. Il verso di rotazione è influenzato dal parametro");
  Output.println("        _DxVerso per il motore 1 e _SxVerso per il 2");
  Output.println("----------------------------------------------------------------");
  Output.println("motori.Impulso(Lunghezza imp 1, Lunghezza imp 2)");
  Output.println("        Il parametro Lunghezza va da 1 a 65535 mS. 0 non da alcun");
  Output.println("        impulso a quel canale");
  Output.println("----------------------------------------------------------------");
  Output.println("motori.Help(Serial)");
  Output.println("        Questo Help");
}
