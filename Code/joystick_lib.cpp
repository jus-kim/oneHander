/**
 * \copyright  Copyright 2024 juskim. All rights reserved.
 *             The code for this project follow the Apache 2.0 license and details 
 *             are provided in the LICENSE file located in the root folder of this 
 *             project. Details of SOUP used in this project can also be found in 
 *             the SOUP file located in the root folder.
 * 
 * @file       joystick_lib.cpp
 * @author     juskim (GitHub: jus-kim, YouTube: @juskim)
 * @brief      Generic joystick library.
 *
 * @internal
 * This is an internal implementation command.
 * @endinternal
 */


#include "joystick_lib.h"


#define RAD_TO_DEG 57.2958


joystick_lib::joystick_lib(void)
{
  pinMode(profile.joystick_pin_click, INPUT_PULLUP);
}

int joystick_lib::get_xy_adc(int &adc_x, int &adc_y)
{
  adc_x = analogRead(JOYSTICK_PIN_X);
  adc_y = analogRead(JOYSTICK_PIN_Y);

  return 0;
}

int joystick_lib::get_xy_percent(int &percent_x, int &percent_y)
{
  int adc_x, adc_y;

  get_xy_adc(adc_x, adc_y);

  percent_x = (int)(((float)adc_x / adc_max) * 200) - 99.0;
  percent_y = (int)(((float)adc_y / adc_max) * 200) - 101.0;

  if (percent_x <= -99) {
    percent_x = -100;
  } else if (percent_x >= 99) {
    percent_x = 100;
  }
  if (percent_y <= -99) {
    percent_y = -100;
  } else if (percent_y >= 99) {
    percent_y = 100;
  }

  return 0;
}

//
//  A+W  W  W+D
//     \ | /
//   A -   - D
//     / | \
//  A+S  S  S+D
//
int joystick_lib::get_direction_keys(int percent_x, int percent_y, joystick_keys_s &joystick_keys)
{
  int radius_squared;

  joystick_keys.key_state_up = false;     // Forward
  joystick_keys.key_state_left = false;   // Left
  joystick_keys.key_state_down = false;   // Backward
  joystick_keys.key_state_right = false;  // Right
  joystick_keys.key_state_walk = false;   // Walking

  // Check if outside of rest zone
  radius_squared = sq(percent_x) + sq(percent_y);
  if (radius_squared >= rest_radius_max_squared)
  {
    // Check if in walking zone
    if (radius_squared <= walking_radius_max_squared) {
      joystick_keys.key_state_walk = true;
    }
  }
  else
  {
    // User is not using the joystick; return
    return 0;
  }

  // Get direction angle and determine key(s) pressed
  float angle_rad = atan2(percent_y, percent_x);
  float angle_deg = angle_rad * RAD_TO_DEG;  // NOTE: I really don't want to deal with rads... :)
  if ((angle_deg <= KEY_DEG_RIGHT + (KEY_DEG_LIMITS + KEY_DEG_OVERLAP)) && (angle_deg >= KEY_DEG_RIGHT - (KEY_DEG_LIMITS + KEY_DEG_OVERLAP))) {
    joystick_keys.key_state_right = true;
  }
  if ((angle_deg <= KEY_DEG_UP + (KEY_DEG_LIMITS + KEY_DEG_OVERLAP)) && (angle_deg >= KEY_DEG_UP - (KEY_DEG_LIMITS + KEY_DEG_OVERLAP))) {
    joystick_keys.key_state_up = true;
  }
  if ((angle_deg <= -KEY_DEG_LEFT + (KEY_DEG_LIMITS + KEY_DEG_OVERLAP)) || (angle_deg >= KEY_DEG_LEFT - (KEY_DEG_LIMITS + KEY_DEG_OVERLAP))) {
    joystick_keys.key_state_left = true;
  }
  if ((angle_deg <= KEY_DEG_DOWN + (KEY_DEG_LIMITS + KEY_DEG_OVERLAP)) && (angle_deg >= KEY_DEG_DOWN - (KEY_DEG_LIMITS + KEY_DEG_OVERLAP))) {
    joystick_keys.key_state_down = true;
  }

  return 0;
}

int joystick_lib::get_click(bool &click)
{
  click = digitalRead(profile.joystick_pin_click);
  click = !click;  // Need to do opposite since pulled-high at resting

  return 0;
}

int joystick_lib::press_keys(bool click, joystick_keys_s joystick_keys)
{
#if JOYSTYICK_AUTO_WALK_ENABLED == 1
  // Press special key if within walking zone
  if (joystick_keys.key_state_walk == true) {
    Keyboard.press(joystick_keys.key_map_walk);
  }
  else {
    Keyboard.release(joystick_keys.key_map_walk);
  }
#endif

  // Press/release joystick direction keys
  if (joystick_keys.key_state_up == true) {
    Keyboard.press(joystick_keys.key_map_up);
  }
  else {
    Keyboard.release(joystick_keys.key_map_up);
  }
  if (joystick_keys.key_state_left == true) {
    Keyboard.press(joystick_keys.key_map_left);
  }
  else {
    Keyboard.release(joystick_keys.key_map_left);
  }
  if (joystick_keys.key_state_down == true) {
    Keyboard.press(joystick_keys.key_map_down);
  }
  else {
    Keyboard.release(joystick_keys.key_map_down);
  }
  if (joystick_keys.key_state_right == true) {
    Keyboard.press(joystick_keys.key_map_right);
  }
  else {
    Keyboard.release(joystick_keys.key_map_right);
  }

  // Press/release joystick click key
  if (click == true) {
    Keyboard.press(joystick_keys.key_map_click);
  } else {
    Keyboard.release(joystick_keys.key_map_click);
  }
}

int joystick_lib::run_tasks(void)
{
  int percent_x, percent_y;
  bool click;
  joystick_keys_s joystick_keys;

  get_xy_percent(percent_x, percent_y);
  get_direction_keys(percent_x, percent_y, joystick_keys);
  get_click(click);
  press_keys(click, joystick_keys);

  /*Serial.print(joystick_keys.key_state_up);
  Serial.print(joystick_keys.key_state_left);
  Serial.print(joystick_keys.key_state_down);
  Serial.print(joystick_keys.key_state_right);
  Serial.println(click);*/
}
