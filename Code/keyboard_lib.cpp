/**
 * \copyright  Copyright 2024 juskim. All rights reserved.
 *             The code for this project follow the Apache 2.0 license and details 
 *             are provided in the LICENSE file located in the root folder of this 
 *             project. Details of SOUP used in this project can also be found in 
 *             the SOUP file located in the root folder.
 * 
 * @file       keyboard_lib.cpp
 * @author     juskim (GitHub: jus-kim, YouTube: @juskim)
 * @brief      Generic keyboard library.
 *
 * @internal
 * This is an internal implementation command.
 * @endinternal
 */


#include "keyboard_lib.h"


keyboard_lib::keyboard_lib(void)
{
  // Initialize keys near the thumb/joystick
  for (uint8_t i = 0; i < profile.total_key_pins; i++) {
    pinMode(profile.key_pins[i], INPUT_PULLUP);
  }
}

int keyboard_lib::get_keys(keys_s &keys)
{
  // Get all the thumb key values
  for (uint8_t i = 0; i < profile.total_key_pins; i++) {
    keys.key_state[i] = !digitalRead(profile.key_pins[i]);
  }

  return 0;
}

int keyboard_lib::press_keys(keys_s keys)
{
  // Press/release all the thumb key values
  for (uint8_t i = 0; i < profile.total_key_pins; i++)
  {
    if (keys.key_state[i] == true) {
      Keyboard.press(keys.key_map[i]);
    }
    else {
      Keyboard.release(keys.key_map[i]);
    }
  }

  return 0;
}

int keyboard_lib::run_tasks(void)
{
  keys_s keys;

  get_keys(keys);
  press_keys(keys);

  /*Serial.print(keys.key_state[0]);
  Serial.print(keys.key_state[1]);
  Serial.println(keys.key_state[2]);*/

  return 0;
}
