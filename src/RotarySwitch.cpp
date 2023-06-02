#include <Arduino.h>
#include "RotarySwitch.h"

#define DEBUG 1   // ==>  this activate the Serial and Debug prints
#include "Debug.h"

void RotarySwitch::begin() {
    pinMode(this->analogPin, INPUT);
    this->prevState = Status::NOP;
}

bool isAbout(int v, int target) {
    return abs(v-target)<10;
}

void RotarySwitch::handle() {
    // Wait for a stable value
    int value;
    do {
        value = analogRead(this->analogPin);
        delay(4);
    } while (analogRead(this->analogPin) != value);

    if (isAbout(value, 0))
        this->curState = Status::NOP;
    else if (isAbout(value, 168))
        this->curState = Status::JOG_XYA;
    else if (isAbout(value, 339))
        this->curState = Status::JOG_XYZ;
    else if (isAbout(value, 510))
        this->curState = Status::MPG_X;
    else if (isAbout(value, 681))
        this->curState = Status::MPG_Y;
    else if (isAbout(value, 852))
        this->curState = Status::MPG_Z;
    else if (isAbout(value, 1023))
        this->curState = Status::MPG_A;
    else this->curState = Status::NOP;

   //  Serial.println(String("RotarySwitch::handle(): value=")+value+" State=" + this->curState);
}

String RotarySwitch::getstatusInfo() {
    return String("RotarySwitch: ") + this->curState;
}

bool RotarySwitch::haschanged() {
    if (this->curState != this->prevState) {
        this->prevState = this->curState;
        return true ;
    } else {
        return false;
    }
}