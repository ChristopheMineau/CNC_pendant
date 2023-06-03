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

void functionKey(FUNCTIONS func, AbleClickButton::CALLBACK_EVENT event, String name) {
  switch (event) {
    case AbleClickButton::PRESSED_EVENT:
      DEBUGMSG("Function Key: "+name );
      switch (func) {
        case FUNCTIONS::HOME:  // CTRL H : use custom screen 1024_CNCPendant.set
          Keyboard.begin();
          Keyboard.press(KEY_LEFT_CTRL);
          delay(10);
          press_letter('h'); // Warning lower case otherwise there is an additional Shift
          break;
        case FUNCTIONS::RWD: //Ctrl W  (standard)
          Keyboard.begin();
          Keyboard.press(KEY_LEFT_CTRL);
          delay(10);
          press_letter('w'); // Warning lower case otherwise there is an additional Shift
          break;
        case FUNCTIONS::Z_INHIBIT:  // CTRL I : use custom screen 1024_CNCPendant.set
          Keyboard.begin();
          Keyboard.press(KEY_LEFT_CTRL);
          delay(10);
          press_letter('i'); // Warning lower case otherwise there is an additional Shift
          break;
        case FUNCTIONS::SPINDLE:  // F5 (standard)
          Keyboard.begin();
          Keyboard.press(KEY_F5);
          delay(10);
          Keyboard.release(KEY_F5);
          break;
        case FUNCTIONS::START:
          Keyboard.begin();
          Keyboard.press(KEY_LEFT_ALT);
          delay(10);
          press_letter('r'); // Warning lower case otherwise there is an additional Shift 
          break;
        default: ;
      }
      break;
    case AbleClickButton::RELEASED_EVENT:
    case AbleClickButton::HELD_EVENT:
    default: ;
  }
  
}

void up_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){  
  if (rotarySwitch.curState == RotarySwitch::FUNCTIONS) {
    functionKey(FUNCTIONS::HOME, event,  "Home"); 
  } else {
    dirKey(KEY_UP_ARROW, event, id, String("UP"));
  }
}

void down_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){
  if (rotarySwitch.curState == RotarySwitch::FUNCTIONS) {
    functionKey(FUNCTIONS::Z_INHIBIT, event, "Z Inhibit"); 
  } else {
    dirKey(KEY_DOWN_ARROW, event, id, String("DOWN"));
  }
}

void left_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){  
  if (rotarySwitch.curState == RotarySwitch::JOG_AYZ) {
    dirKey(KEY_HOME, event, id, String("KEY_HOME")); // A axis, TO BE PROGRAMMED IN MACH3 "Config/HotKeys"
  } else if (rotarySwitch.curState == RotarySwitch::FUNCTIONS) {
    functionKey(FUNCTIONS::RWD, event, "Rewind");
  } else {
    dirKey(KEY_LEFT_ARROW, event, id, String("LEFT"));
  }
}

void right_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){ 
  if (rotarySwitch.curState == RotarySwitch::JOG_AYZ) {
    dirKey(KEY_END, event, id, String("KEY_END")); // A axis, TO BE PROGRAMMED IN MACH3 "Config/HotKeys"
  } else if (rotarySwitch.curState == RotarySwitch::FUNCTIONS) {
    functionKey(FUNCTIONS::SPINDLE, event, "Spindle");
  } else {
    dirKey(KEY_RIGHT_ARROW, event, id, String("RIGHT"));
  }
}

void z_up_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){  
  dirKey(KEY_PAGE_UP, event, id, String("KEY_PAGE_UP"));
}

void z_down_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){  
  dirKey(KEY_PAGE_DOWN, event, id, String("KEY_PAGE_DOWN"));
}

void eStop_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){
  static bool held;
  if (event==AbleClickButton::HELD_EVENT) {  // appui long
      DEBUGMSG(String("HOLD : ") + event +" ID : " + id); 
      Keyboard.begin();
      press_letter(' '); // Warning lower case otherwise there is an additional Shift 
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

void start_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id){  
  functionKey(FUNCTIONS::START, event, "Start"); 
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
