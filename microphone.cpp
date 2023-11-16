#include "HardwareSerial.h"
#include "microphone.h"

/////////VARS///////
bool IS_PICK = false;
unsigned long START=0,END=0;



///////FUNCTIONS////
bool calculate_sound(int analog_pin,float pick_hight,float pick_delay){
  //read the value of sensor 
    float value = analogRead(analog_pin);
    if(value>=pick_hight){
      IS_PICK = true;
      START = millis();
    } 
    else {
     IS_PICK = false;
     END = millis() - START; 
    }

    if(END-START>=pick_delay && IS_PICK){
      return true;
    }
    else{
      return false;
    }
    
}