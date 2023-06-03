#pragma once

#include <Arduino.h>
#include <AbleButtons.h>

using AbleClickButton = AblePullupCallbackClickerButton;
using AbleClickButtonList = AblePullupCallbackClickerButtonList;

void up_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id);
void down_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id);
void left_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id);
void right_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id);
void z_up_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id);
void z_down_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id);
void eStop_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id);
void start_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id);
void slow_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id);
void step_button_action(AbleClickButton::CALLBACK_EVENT event, uint8_t id);

enum FUNCTIONS {
        HOME = 0,
        RWD = 1,
        Z_INHIBIT = 2,
        START = 3,
        SPINDLE = 4,
};

/*
  Aduino website notes on using a Leonardo as HID:

  The keyboard functions enable a Leonardo, Micro,
  or Due to send keystrokes to an attached computer.

  Note: Not every possible ASCII character,
  particularly the non-printing ones, can be sent with the Keyboard library.
  The library supports the use of modifier keys.
  Modifier keys change the behavior of another key when
  pressed simultaneously.
  See here for additional information on supported keys and their use.

  Keyboard.begin()
  Keyboard.end()
  Keyboard.press()
  Keyboard.print()
  Keyboard.println()
  Keyboard.release()
  Keyboard.releaseAll()
  Keyboard.write()



  Reference   Language | Libraries | Comparison | Changes

  Keyboard Modifiers

  The Keyboard.write() and Keyboard.press()
  and Keyboard.release() commands don’t work with every possible ASCII character,
  only those that correspond to a key on the keyboard.
    For example, backspace works, but many of the other
    non-printable characters produce unpredictable results.
    For capital letters (and other keys), what’s sent is shift plus the character
    (i.e. the equivalent of pressing both of those keys on the keyboard).

  A modifier key is a special key on a computer keyboard that modifies
  the normal action of another key when the two are pressed in combination.

  For more on ASCII values and the characters or functions they represent,
  see asciitable.com

  For multiple key presses use Keyboard.press()

  The Leonardo's definitions for modifier keys are listed below:

  Key  Hexadecimal value Decimal value
  KEY_LEFT_CTRL     0x80  128
  KEY_LEFT_SHIFT    0x81  129
  KEY_LEFT_ALT      0x82  130
  KEY_LEFT_GUI      0x83  131
  KEY_RIGHT_CTRL    0x84  132
  KEY_RIGHT_SHIFT   0x85  133
  KEY_RIGHT_ALT     0x86  134
  KEY_RIGHT_GUI     0x87  135
  KEY_UP_ARROW      0xDA  218
  KEY_DOWN_ARROW    0xD9  217
  KEY_LEFT_ARROW    0xD8  216
  KEY_RIGHT_ARROW   0xD7  215
  KEY_BACKSPACE     0xB2  178
  KEY_TAB           0xB3  179
  KEY_RETURN        0xB0  176
  KEY_ESC           0xB1  177
  KEY_INSERT        0xD1  209
  KEY_DELETE        0xD4  212
  KEY_PAGE_UP       0xD3  211
  KEY_PAGE_DOWN     0xD6  214
  KEY_HOME          0xD2  210
  KEY_END           0xD5  213
  KEY_CAPS_LOCK     0xC1  193
  KEY_F1            0xC2  194
  KEY_F2            0xC3  195
  KEY_F3            0xC4  196
  KEY_F4            0xC5  197
  KEY_F5            0xC6  198
  KEY_F6            0xC7  199
  KEY_F7            0xC8  200
  KEY_F8            0xC9  201
  KEY_F9            0xCA  202
  KEY_F10           0xCB  203
  KEY_F11           0xCC  204
  KEY_F12           0xCD  205

*/
void press_letter(char c);
