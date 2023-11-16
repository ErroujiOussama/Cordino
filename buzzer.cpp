#include "buzzer.h"
void buzzer(int buzzer_pin,int bips){
  int i;
  for(int i=0;i<bips;i++){
    digitalWrite(buzzer_pin,HIGH);
    delay(200);
    digitalWrite(buzzer_pin,LOW);

  }
}