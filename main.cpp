#include <Arduino.h>
#define IR_USE_AVR_TIMER1
#include <IRRemote.hpp>

#define IR_RECEIVE_PIN 2
#define RED 3
#define GREEN 5 
#define BLUE 6
#define REDCODESKOLA 3091726080 //CH+
#define GREENCODESKOLA 3158572800 //>||
#define BLUECODESKOLA 4127850240 //EQ
#define BACKSKOLA 4161273600 //-
#define RESETSKOLA 3927310080 //+

unsigned long codesSkola[] =
    {
        3910598400,                               // 0
        4077715200,                               // 1
        3877175040,                               // 2
        2707357440,                               // 3
        4144561920,                               // 4
        3810328320,                               // 5
        2774204160,                               // 6
        3175284480,                               // 7
        2907897600,                               // 8
        3041591040                                // 9
}; 

//Funkce pro IR vstup
void IrInput() {
  //Inicializace promennych potrebnych pro fukci
  bool next = true;
  int number = 0;
  
  while (next)
  {
    //Pokus o precteni IR senzoru
    if (IrReceiver.decode()) 
    {
      //Vypis informaci na seriovou linku a nacteni dat do promenne
      IrReceiver.printIRResultShort(&Serial);
      unsigned long code = IrReceiver.decodedIRData.decodedRawData;
      Serial.println(code, DEC);
      
      //Kontrola jestli je vstupni kod cislo
      for (size_t i = 0; i < 10; i++)
      {
        if (code == codesSkola[i]) {
          number *= 10;
          number += i;
        }
      }
      
      //Kontrola pro dalsi kody
      switch (code)
      {
        //Smazani posledni cifry
        case BACKSKOLA:
          number /= 10;
          break;
        //Reset celeho cisla pomoci ukonceni funkce
        case RESETSKOLA:
          next = false;
          break;
        //Rozsviceni jednotlivych ledek
        case REDCODESKOLA:
          analogWrite(RED, number > 255 ? 255 : number);
          break;
        case GREENCODESKOLA:
          analogWrite(GREEN, number > 255 ? 255 : number);
          break;
        case BLUECODESKOLA:
          analogWrite(BLUE, number > 255 ? 255 : number);
          break;
        default:
          break;
      }
      //Prikaz k pokracovani monitorovani IR prijimace
      IrReceiver.resume();
    } 
  }
}


void setup() {
  //Priprava pinu a zapnuti seriove linky
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //Testuje se jestli prisel nejaky IR vstup
  if (IrReceiver.available())
  {
    IrInput();
  }
}
