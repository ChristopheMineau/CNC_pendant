#include <Arduino.h>
#include "MpgWheel.h"
#include <Keyboard.h>
#define DEBUG 1   // ==>  this activate the Serial and Debug prints
#include "Debug.h"

// Static members need a definition
uint8_t MPGWheel::pinA;
uint8_t MPGWheel::pinB;
uint8_t MPGWheel::divisor;

int MPGWheel::previousCounter;
volatile int MPGWheel::counter;
volatile int MPGWheel::pulseCounter;

void MPGWheel::begin() {
    attachInterrupt(digitalPinToInterrupt(pinA), wheelISR, CHANGE); 
}

void MPGWheel::wheelISR() {
    uint8_t A = digitalRead(MPGWheel::pinA); 
    uint8_t B = digitalRead(MPGWheel::pinB);

  if(B != A) {
    MPGWheel::pulseCounter++;
  }
  else {
    MPGWheel::pulseCounter--;
  }
  MPGWheel::counter = pulseCounter / divisor;
}

void MPGWheel::handle(){
    int delta = counter - previousCounter;
    if (haschanged()) {
        DEBUGMSG(getstatusInfo());
        switch (rotarySwitch.curState) {
            case RotarySwitch::MPG_A:
                moveMPG(delta, KEY_END, KEY_HOME);
                break;
            case RotarySwitch::MPG_X:
                moveMPG(delta, KEY_RIGHT_ARROW, KEY_LEFT_ARROW);
                break;
            case RotarySwitch::MPG_Y:
                moveMPG(delta, KEY_UP_ARROW, KEY_DOWN_ARROW);
                break;
            case RotarySwitch::MPG_Z:
                moveMPG(delta, KEY_PAGE_UP, KEY_PAGE_DOWN);
                break;
            default: ;
        }
    }

}

void MPGWheel::moveMPG(int delta, uint8_t key_plus, uint8_t key_less){
  DEBUGMSG(String("moveMPG ")+delta);
  Keyboard.begin();
  Keyboard.press(KEY_LEFT_CTRL);
  delay(10);
  if (delta >=0) {
        for (int i=0; i<delta; i++) {
            Keyboard.press(key_plus);
         //   DEBUGMSG(String("keyPlus ")+ key_plus);
            delay(10);
            Keyboard.release(key_plus);
        }
  } else {
        for (int i=0; i>delta; i--) {
            Keyboard.press(key_less);
          //  DEBUGMSG(String("keyLess ")+key_less);
            delay(10);
            Keyboard.release(key_less);
        }
  }
  Keyboard.release(KEY_LEFT_CTRL);
}

void MPGWheel::resetCounter(){
    counter = 0;
    pulseCounter = 0;
}

String MPGWheel::getstatusInfo(){
    return String("MpgWheel: ") + counter;
}

bool MPGWheel::haschanged(){
    if (counter != previousCounter) {
        previousCounter = counter;
        return true ;
    } else {
        return false;
    }
}
