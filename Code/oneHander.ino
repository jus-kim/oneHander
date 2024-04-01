
#include <Arduino.h>
#include "joystick_lib.h"
#include "keyboard_lib.h"


joystick_lib joystick;
keyboard_lib keyboard; 


void setup()
{
  Serial.begin(9600);

  //pinMode(KEY_THUMB_PIN_0, INPUT_PULLUP);
}

void loop()
{
  joystick.run_tasks();
  keyboard.run_tasks();

  //bool push = !digitalRead(KEY_THUMB_PIN_0);
  //Serial.println(push);
}
