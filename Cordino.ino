//////////INCLUDE////////////
#include "microphone.h"
#include "buzzer.h"
#include "action.h"
#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;
////////Define Pins//////////
#define Switch_State 4
#define Red_LED 5
#define Microphone_Analog A3
#define Transistor_Base 9
///////////Variables ////////
bool newState = 0;
bool oldState = 0;

void setup() {
  my_servo.write(0);
  ///////////Servo begin//////////
  Serial.begin(9600);
  ////////PIN MODE//////////////
  pinMode(Switch_State, INPUT);
  pinMode(Red_LED, OUTPUT);
  digitalWrite(Red_LED, LOW);
  pinMode(Servo_pin, OUTPUT);
  pinMode(Transistor_Base, OUTPUT);
  ////////////SERVO////////////
  my_servo.attach(Servo_pin);
  ///////////MPU_SETUP/////////
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) {
    Serial.println("check wiring!");
    delay(500);
  }
  checkSettings();
  
}

void loop() {
  
  oldState = newState;
  newState = digitalRead(Switch_State);

  ///State 1 MICROPHONE///
  if(digitalRead(Switch_State) == HIGH)
  {
    
    if (newState == 1 && newState != oldState) {
      tone(Transistor_Base, 550);
      delay(500);
      noTone(Transistor_Base);
    }
    
    if (calculate_sound(A3, 40, 250)) {
      jump();
    }
  
  }
  
  ///State 2 GYRO_ACC///
  else {
    if (newState == 0 && newState != oldState) {
      tone(Transistor_Base, 150);
      delay(500);
      noTone(Transistor_Base);
    }
    Vector normAccel = mpu.readNormalizeAccel();
    Serial.print(" Xnorm = ");
    Serial.println(normAccel.XAxis);
    if (normAccel.XAxis < 0) {
      jump();
    }
  }
}



/////checkSettings/////
void checkSettings() {
  Serial.println();

  Serial.print(" * Sleep Mode:            ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");

  Serial.print(" * Clock Source:          ");
  switch (mpu.getClockSource()) {
    case MPU6050_CLOCK_KEEP_RESET: Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO: Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO: Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO: Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ: Serial.println("Internal 8MHz oscillator"); break;
  }

  Serial.print(" * Accelerometer:         ");
  switch (mpu.getRange()) {
    case MPU6050_RANGE_16G: Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G: Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G: Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G: Serial.println("+/- 2 g"); break;
  }

  Serial.print(" * Accelerometer offsets: ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getAccelOffsetZ());

  Serial.println();
}
