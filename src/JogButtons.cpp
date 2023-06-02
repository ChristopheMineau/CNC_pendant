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
    case 'A':
      return 'Q';
    case 'Z':
      return 'W';
    case ',':
      return 'm';
    case '?':
      return 'M';
    case 'M':
      return ':';
    case '1':
      return '!';
    case '9':
      return '(';
    case ';':
      return ',';
    case '§':
      return '?';
    case '0':
      return ')';
    case ')':
      return '-';
    case 'ù':
      return '\'';
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
  dirKey(KEY_UP_ARROW, event, id, String("UP"));
}

void down_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){  
  dirKey(KEY_DOWN_ARROW, event, id, String("DOWN"));
}

void left_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){  
  dirKey(KEY_LEFT_ARROW, event, id, String("LEFT"));
}

void right_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){  
  dirKey(KEY_RIGHT_ARROW, event, id, String("RIGHT"));
}

void az_up_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){  
  switch (rotarySwitch.curState) {
    case RotarySwitch::JOG_XYA:
      dirKey(KEY_HOME, event, id, String("KEY_HOME")); // TO BE PROGRAMMED IN MACH3 "Config/HotKeys"
      break;
    case RotarySwitch::JOG_XYZ:
      dirKey(KEY_PAGE_UP, event, id, String("KEY_PAGE_UP"));
      break;
    default: ;
  }
}

void az_down_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){  
  switch (rotarySwitch.curState) {
    case RotarySwitch::JOG_XYA:
      dirKey(KEY_END, event, id, String("KEY_END"));  // TO BE PROGRAMMED IN MACH3 "Config/HotKeys"
      break;
    case RotarySwitch::JOG_XYZ:
      dirKey(KEY_PAGE_DOWN, event, id, String("KEY_PAGE_DOWN"));
      break;
    default: ;
  }
}

void eStop_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){
  static bool held;
  if (event==AbleClickButton::HELD_EVENT) {  // appui long
      DEBUGMSG(String("START : ") + event +" ID : " + id); 
      Keyboard.begin();
      Keyboard.press(KEY_LEFT_ALT);
      delay(10);
      press_letter('r'); // Warning lower case otherwise there is an additional Shift 
      held = true;
  } else if (event==AbleClickButton::RELEASED_EVENT) {  
    if (held)
      held = false;
    else {
      DEBUGMSG(String("STOP : ") + event +" ID : " + id); // simple click
      Keyboard.begin();
      Keyboard.press(KEY_LEFT_ALT);
      delay(100);
      press_letter('s');    // Warning lower case otherwise there is an additional Shift    
    }
  }
}

void slow_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){  
  DEBUGMSG(String("SLOW : ") + event +" ID : " + id);
}

void step_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){  
  DEBUGMSG(String("STEP : ") + event +" ID : " + id);
    if (event==AbleClickButton::PRESSED_EVENT) {
      Keyboard.begin();
      Keyboard.press(KEY_LEFT_ALT);
      delay(100);
      press_letter('j');  // Warning lower case otherwise there is an additional Shift
  }
}
