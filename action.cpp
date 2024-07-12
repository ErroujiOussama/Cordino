#include "Arduino.h"
#include "action.h"
#include <Keyboard.h>


Keyboard.begin();

void jump(){
  Keyboard.press(spacebar);
  delay(500); //you can adjust this value
  Keyboard.releaseAll();
}                     
