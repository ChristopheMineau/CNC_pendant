
#include "RotarySwitch.h"
#include <Keyboard.h>
#include <AbleButtons.h>
#include "JogButtons.h"
#include "MpgWheel.h"

#define DEBUG 1   // ==>  this activate the Serial and Debug prints
#include "Debug.h"

#define UP_BUTTON_PIN 4
#define DOWN_BUTTON_PIN 5
#define LEFT_BUTTON_PIN 6
#define RIGHT_BUTTON_PIN 7
#define Z_UP_BUTTON_PIN 8
#define Z_DOWN_BUTTON_PIN 9
#define START_BUTTON_PIN 10
#define STEP_BUTTON_PIN 14
#define ESTOP_BUTTON_PIN 15
#define SLOW_BUTTON_PIN 16
#define A_ENCODER_PIN 2
#define B_ENCODER_PIN 3
#define ENCODER_STEPS_PER_CLICK 2
#define ROTARY_SWITCH_PIN A0


/* Note : use https://www.test-clavier.fr/ to test Keyboard actions (Azerty KB) */

AbleClickButton up_button(UP_BUTTON_PIN, up_button_action); 
AbleClickButton down_button(DOWN_BUTTON_PIN, down_button_action);
AbleClickButton left_button(LEFT_BUTTON_PIN, left_button_action);
AbleClickButton right_button(RIGHT_BUTTON_PIN, right_button_action);
AbleClickButton z_up_button(Z_UP_BUTTON_PIN, z_up_button_action);
AbleClickButton z_down_button(Z_DOWN_BUTTON_PIN, z_down_button_action);
AbleClickButton slow_button(SLOW_BUTTON_PIN, slow_button_action);

AbleClickButton *btns[] = {
  &up_button,
  &down_button,  
  &left_button,
  &right_button,
  &z_up_button,
  &z_down_button,
  &slow_button,
};
AbleClickButtonList btnList(btns);
RotarySwitch rotarySwitch(ROTARY_SWITCH_PIN);
MPGWheel mpgWheel(A_ENCODER_PIN, B_ENCODER_PIN, ENCODER_STEPS_PER_CLICK, rotarySwitch);

void setup() {
  #if DEBUG
   Serial.begin(115200);
   DEBUGMSG("CNC Pendant starting");
  #endif
  
  rotarySwitch.begin();
  btnList.begin();
  mpgWheel.begin();

}

void loop() {
  rotarySwitch.handle();
  btnList.handle();
  mpgWheel.handle();

 
  if(rotarySwitch.haschanged()){
    DEBUGMSG(rotarySwitch.getstatusInfo());
  }

 // delay(2000);
}