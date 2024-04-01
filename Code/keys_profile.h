/**
 * \copyright  Copyright 2024 juskim. All rights reserved.
 *             The code for this project follow the Apache 2.0 license and details 
 *             are provided in the LICENSE file located in the root folder of this 
 *             project. Details of SOUP used in this project can also be found in 
 *             the SOUP file located in the root folder.
 * 
 * @file       keys_profile.h
 * @author     juskim (GitHub: jus-kim, YouTube: @juskim)
 * @brief      Keyboard profile one-handed gaming controller.
 */

// NOTE: Check out below link for the list of all special key character values
// https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/

#ifndef __KEYS_PROFILE_H
#define __KEYS_PROFILE_H

#include <Arduino.h>
#include <Keyboard.h>


// Total number of key pins (including joystick click)
#define TOTAL_KEY_PINS        8

// Key values for the joystick direction
#define JOYSTICK_KEY_UP       'w'
#define JOYSTICK_KEY_LEFT     'a'
#define JOYSTICK_KEY_DOWN     's'
#define JOYSTICK_KEY_RIGHT    'd'
#define JOYSTICK_KEY_WALK     KEY_LEFT_SHIFT
#define JOYSTICK_KEY_CLICK    ' '
// Key values for the thumb keys
#define KEY_THUMB_0           'r'
#define KEY_THUMB_1           '4'
#define KEY_THUMB_2           KEY_LEFT_CTRL
// Key values for the index finger keys
#define KEY_INDEX_0           'c'
#define KEY_INDEX_1           'q'
// Key values for the middle finger keys
#define KEY_MIDDLE_0          'e'
#define KEY_MIDDLE_1          'x'
// Key values for the menu key
#define KEY_MENU_0            'b'//KEY_ESC

// GPIO/ADC pins for the joystick
#define JOYSTICK_PIN_X        A2
#define JOYSTICK_PIN_Y        A3
#define JOYSTICK_PIN_CLICK    A1
// GPIO pins for the thumb keys
#define KEY_THUMB_PIN_0       16
#define KEY_THUMB_PIN_1       14
#define KEY_THUMB_PIN_2       15
// GPIO pins for the index finger keys
#define KEY_INDEX_PIN_0       2
#define KEY_INDEX_PIN_1       3
// GPIO pins for the middle finger keys
#define KEY_MIDDLE_PIN_0      5
#define KEY_MIDDLE_PIN_1      4
// GPIO pins for the menu key
#define KEY_MENU_PIN_0        6


class keys_profile
{
  public:
    const uint8_t total_key_pins = TOTAL_KEY_PINS;
    // Joystick related variables
    const uint8_t joystick_pin_x = JOYSTICK_PIN_X;
    const uint8_t joystick_pin_y = JOYSTICK_PIN_Y;
    const uint8_t joystick_pin_click = JOYSTICK_PIN_CLICK;
    // Keyboard related variables
    const uint8_t key_pins[TOTAL_KEY_PINS] = 
      { KEY_THUMB_PIN_0, KEY_THUMB_PIN_1, KEY_THUMB_PIN_2,
        KEY_INDEX_PIN_0, KEY_INDEX_PIN_1, KEY_MIDDLE_PIN_0, KEY_MIDDLE_PIN_1,
        KEY_MENU_PIN_0 };
};


#endif // __KEYS_PROFILE_H
