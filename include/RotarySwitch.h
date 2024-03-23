#pragma once
#include <Arduino.h>
class RotarySwitch {
    public:
      uint8_t analogPin;
      enum Status {
        NOP = 0,
        JOG_XYZ = 1,
        JOG_AYZ = 2,
        JOG_XAZ = 3,
        MPG_X = 4,
        MPG_Y = 5,
        MPG_Z = 6,
        MPG_A = 7
      };
      RotarySwitch::Status curState;
      RotarySwitch::Status prevState;  
      
      RotarySwitch(uint8_t pin) : analogPin(pin), curState(Status::NOP) {};
  
      void begin();
      void handle();
      String getstatusInfo();
      bool haschanged();
};
