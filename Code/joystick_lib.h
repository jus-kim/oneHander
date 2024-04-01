/**
 * \copyright  Copyright 2024 juskim. All rights reserved.
 *             The code for this project follow the Apache 2.0 license and details 
 *             are provided in the LICENSE file located in the root folder of this 
 *             project. Details of SOUP used in this project can also be found in 
 *             the SOUP file located in the root folder.
 * 
 * @file       joystick_lib.h
 * @author     juskim (GitHub: jus-kim, YouTube: @juskim)
 * @brief      Generic joystick library.
 */

#ifndef __JOYSTICK_LIB_H
#define __JOYSTICK_LIB_H

#include <Arduino.h>
#include <Keyboard.h>
//#include "keys_profile.h"
#include "keys_profile_fortnite.h"


// GPIO macros
#define ADC_RES_BIT        10
// Joystick resting radius limit zone
#define REST_RADIUS_MAX    3   // Circular zone below 3% radius is a resting zone (i.e., no movement)
#define WALKING_RADIUS_MAX 95   // Circular zone below 95% radius is a walking zone (i.e., add special key)
// Joystick direction angle macros
#define KEY_DEG_UP         90
#define KEY_DEG_LEFT       180
#define KEY_DEG_DOWN       -90
#define KEY_DEG_RIGHT      0
#define KEY_DEG_LIMITS     40  // Side limits per direction (e.g., KEY_DEG_D +/- KEY_DEG_LIMITS limits the 'D' direction range)
#define KEY_DEG_OVERLAP    20  // Side overlap between directions to allow double presses like W+A for forward+left movement


typedef struct {
  bool key_state_up;
  bool key_state_left;
  bool key_state_down;
  bool key_state_right;
  bool key_state_walk;
  uint8_t key_map_up = JOYSTICK_KEY_UP;
  uint8_t key_map_left = JOYSTICK_KEY_LEFT;
  uint8_t key_map_down = JOYSTICK_KEY_DOWN;
  uint8_t key_map_right = JOYSTICK_KEY_RIGHT;
  uint8_t key_map_walk = JOYSTICK_KEY_WALK;
  uint8_t key_map_click = JOYSTICK_KEY_CLICK;
} joystick_keys_s;


/**
 * @class joystick_lib
 * @brief Brief description of MyClass.
 *
 * Detailed description of MyClass.
 * More information about the class, its purpose, and usage.
 */
class joystick_lib
{
  public:
    /**
    * @brief Initializes the GPIO for the joystick library class.
    */
    joystick_lib(void);

    int run_tasks(void);

  private:
    keys_profile profile;
    const float adc_max = (float)(pow(2, ADC_RES_BIT)) - 1.0;
    const int rest_radius_max_squared = pow(REST_RADIUS_MAX, 2);
    const int walking_radius_max_squared = pow(WALKING_RADIUS_MAX, 2);
    
    /**
    * @brief Converts x and y axes joystick ADC values to percentages, ranging from
    *        -100 to 100. Used mainly for serial output and testing purposes.
    *
    * @param[out] adc_x ADC value of the joystick x-axis from 0 to 2^ADC_RES_BIT.
    * @param[out] adc_y ADC value of the joystick y-axis from 0 to 2^ADC_RES_BIT.
    *
    * @retval 0 On success.
    * @retval -errno Other negative errno in case of failure.
    */
    int get_xy_adc(int &adc_x, int &adc_y);

    /**
    * @brief Converts x and y axes joystick ADC values to percentages, ranging from
    *        -100 to 100. Used mainly for serial output and testing purposes.
    *
    * @param[out] percent_x Percentage of the joystick x-axis from -100 to 100.
    * @param[out] percent_y Percentage of the joystick y-axis from -100 to 100.
    *
    * @retval 0 On success.
    * @retval -errno Other negative errno in case of failure.
    */
    int get_xy_percent(int &percent_x, int &percent_y);

    int get_direction_keys(int percent_x, int percent_y, joystick_keys_s &keys_movement);

    int get_click(bool &click);

    int press_keys(bool click, joystick_keys_s keys_movement);
};


#endif // __JOYSTICK_LIB_H
