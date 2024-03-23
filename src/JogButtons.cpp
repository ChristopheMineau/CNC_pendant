#include "JogButtons.h"
#include  "RotarySwitch.h"
#include <Keyboard.h>
#define DEBUG 1 // ==>  this activate the Serial and Debug prints
#include "Debug.h"
extern AbleClickButton slow_button;
extern AbleClickButton step_button;
extern RotarySwitch rotarySwitch;


char azerty2qwerty(char c)
{
  switch (c)
  {
    case 'a':
      return 'q';
    case 'z':
      return 'w';
    case 'q':
      return 'a';
    case 'w':
      return 'z';
    case ',':
      return 'm';
    case '?':
      return 'm';
    case 'm':
      return ':';
    case '1':
      return '!';
    case '9':
      return '(';
    case ';':
      return ',';
    // case '§':
    //   return '?';
    case '0':
      return ')';
    case ')':
      return '-';
    // case 'ù':
    //   return '\'';
    default:
      return c;
  }
}

void press_letter(char c)
{
  Keyboard.begin();
  Keyboard.press(azerty2qwerty(c));
  delay(100);
  Keyboard.releaseAll();
}

void dirKey(uint8_t k, AbleClickButton::CALLBACK_EVENT event, uint8_t id, String name) {
  String mode;
  if (slow_button.isPressed())
    mode = "SLOW";
  else
    mode = "FAST";
  DEBUGMSG(name + " : " + event +" ID : " + id + " " + mode);
  switch (event) {
    case AbleClickButton::PRESSED_EVENT:
      Keyboard.begin();
      if (!slow_button.isPressed()) {
        Keyboard.press(KEY_LEFT_SHIFT);
        delay(10);
      }
      Keyboard.press(k);
      break;
    case AbleClickButton::RELEASED_EVENT:
      Keyboard.begin();
      Keyboard.release(k);
      Keyboard.release(KEY_LEFT_SHIFT);
      break;
    default: ;
  }
}

void up_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){  
  switch(rotarySwitch.curState){
    case RotarySwitch::NOP:
      break;
    case RotarySwitch::JOG_XAZ:
      dirKey(KEY_HOME, event, id, String("KEY_HOME")); // A+ axis, TO BE PROGRAMMED Home key
      break;
    case RotarySwitch::JOG_AYZ:
    case RotarySwitch::JOG_XYZ:
    default:
      dirKey(KEY_UP_ARROW, event, id, String("UP"));
  }
}

void down_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){
    switch(rotarySwitch.curState){
    case RotarySwitch::NOP:
      break;
    case RotarySwitch::JOG_XAZ:
      dirKey(KEY_END, event, id, String("KEY_END")); // A- axis, TO BE PROGRAMMED End key
      break;
    case RotarySwitch::JOG_AYZ:
    case RotarySwitch::JOG_XYZ:
    default:
      dirKey(KEY_DOWN_ARROW, event, id, String("DOWN"));
  }
}

void left_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){  
  switch(rotarySwitch.curState){
    case RotarySwitch::NOP:
      break;
    case RotarySwitch::JOG_AYZ: 
      dirKey(KEY_END, event, id, String("KEY_END")); // A- axis, TO BE PROGRAMMED End key
      break;
    case RotarySwitch::JOG_XAZ:
    case RotarySwitch::JOG_XYZ:
    default:
      dirKey(KEY_LEFT_ARROW, event, id, String("LEFT"));
  }
}

void right_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){
  switch(rotarySwitch.curState){
    case RotarySwitch::NOP:
      break;
    case RotarySwitch::JOG_AYZ: 
      dirKey(KEY_HOME, event, id, String("KEY_HOME")); // A+ axis, TO BE PROGRAMMED Home key
      break;
    case RotarySwitch::JOG_XAZ:
    case RotarySwitch::JOG_XYZ:
    default:
      dirKey(KEY_RIGHT_ARROW, event, id, String("RIGHT"));
  }
}

void z_up_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){ 
  switch(rotarySwitch.curState){
    case RotarySwitch::NOP:
      break;
    case RotarySwitch::JOG_AYZ: 
    case RotarySwitch::JOG_XAZ:
    case RotarySwitch::JOG_XYZ:
    default:
      dirKey(KEY_PAGE_UP, event, id, String("KEY_PAGE_UP"));
  } 
}

void z_down_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){
  switch(rotarySwitch.curState){
    case RotarySwitch::NOP:
      break;
    case RotarySwitch::JOG_AYZ: 
    case RotarySwitch::JOG_XAZ:
    case RotarySwitch::JOG_XYZ:
    default:
      dirKey(KEY_PAGE_DOWN, event, id, String("KEY_PAGE_DOWN"));
  } 
}

void slow_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){  
  DEBUGMSG(String("SLOW : ") + event +" ID : " + id);
}

