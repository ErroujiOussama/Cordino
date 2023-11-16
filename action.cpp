#include "Arduino.h"
#include "action.h"
#include <Servo.h>


void jump(int Servo_pin,Servo your_servo,int pin_led){
  your_servo.write(25);
  digitalWrite(pin_led,HIGH);
  delay(300); 
  your_servo.write(0);

  delay(300);  
  digitalWrite(pin_led,LOW);  
  
  

}                     