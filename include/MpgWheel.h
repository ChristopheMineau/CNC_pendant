#pragma once
#include <Arduino.h>
#include "RotarySwitch.h"

class MPGWheel {
    // Can be instanciated only once !
    public:
      static uint8_t pinA;
      static uint8_t pinB;
      static uint8_t divisor;

      static volatile int pulseCounter;
      static  int previousCounter;
      static volatile int counter;
      
      MPGWheel(uint8_t a, uint8_t b, uint8_t d, RotarySwitch &s): rotarySwitch(s) {
        pinA = a;
        pinB = b;
        divisor = d;
        pulseCounter = 0;
        counter = 0;
        previousCounter = 0;
      };
      void begin();
      void handle();
      void resetCounter();
      String getstatusInfo();
      bool haschanged();

    private:
        static void wheelISR();  // an ISR can only be a static method
        RotarySwitch &rotarySwitch;
        void moveMPG(int delta, uint8_t key_plus, uint8_t key_less);
};
    