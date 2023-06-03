#pragma once
#include <Arduino.h>
class RotarySwitch {
    public:
      uint8_t analogPin;
      enum Status {
        NOP = 0,
        JOG_AYZ = 1,
        FUNCTIONS = 2,
        MPG_X = 3,
        MPG_Y = 4,
        MPG_Z = 5,
        MPG_A = 6
      };
      RotarySwitch::Status curState;
      RotarySwitch::Status prevState;  
      
      RotarySwitch(uint8_t pin) : analogPin(pin), curState(Status::NOP) {};
  
      void begin();
      void handle();
      String getstatusInfo();
      bool haschanged();
};
