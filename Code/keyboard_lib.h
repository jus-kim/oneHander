/**
 * \copyright  Copyright 2024 juskim. All rights reserved.
 *             The code for this project follow the Apache 2.0 license and details 
 *             are provided in the LICENSE file located in the root folder of this 
 *             project. Details of SOUP used in this project can also be found in 
 *             the SOUP file located in the root folder.
 * 
 * @file       keyboard_lib.h
 * @author     juskim (GitHub: jus-kim, YouTube: @juskim)
 * @brief      Generic keyboard library.
 */

#ifndef __KEYBOARD_LIB_H
#define __KEYBOARD_LIB_H

#include <Arduino.h>
#include <Keyboard.h>
//#include "keys_profile.h"
#include "keys_profile_fortnite.h"


typedef struct {
  bool key_state[TOTAL_KEY_PINS];
  uint8_t key_map[TOTAL_KEY_PINS] = 
    { KEY_THUMB_0, KEY_THUMB_1, KEY_THUMB_2,
      KEY_INDEX_0, KEY_INDEX_1, KEY_MIDDLE_0, KEY_MIDDLE_1,
      KEY_MENU_0 };
} keys_s;


/**
 * @class keyboard_lib
 * @brief Brief description of MyClass.
 *
 * Detailed description of MyClass.
 * More information about the class, its purpose, and usage.
 */
class keyboard_lib
{
  public:
    /**
    * @brief Initializes the GPIO for the keyboard library class.
    */
    keyboard_lib(void);

    int run_tasks(void);

  private:
    keys_profile profile;

    int get_keys(keys_s &keys);

    int press_keys(keys_s keys);
};


#endif // __KEYBOARD_LIB_H
