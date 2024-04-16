#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create the PWM driver instance
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Servo parameters
const int s1 = 1; //R
const int s2 = 2; //R
const int s3 = 3; //R
const int s4 = 4; //R
const int s8 = 8; //L
const int s9 = 9; //L
const int s10 = 10; //L
const int s11 = 11; //L
const int minPulse = 150;
const int maxPulse = 600;

void setup() {
  Serial.begin(9600);
  Serial.println("PCA9685 Servo Test");
  pwm.begin();
  pwm.setPWMFreq(60);
  delay(10);
   moveServo(s1,90);
   moveServo(s2,90);
   moveServo(s3,90);
   moveServo(s4,80);
   moveServo(s8, 90);
   moveServo(s9, 90);
   moveServo(s10, 0);
   moveServo(s11, 0);
   delay(1000);
  // moveServo(s9, 0);
  // delay(500);
  // moveServo(s10, 40);
  // delay(500);
  // moveServo(s8, 70);
  // delay(200);
  // moveServo(s8, 90);
  // moveServo(s11, 50);
}
  int x, y;
  int oldPosX = 90 ;
  int oldPosY1 = 90 ;
  int oldPosY4 = 80 ;
  int i = 1;
  int t = 50;
  int threshold = 25;

void loop() {
  
  // communication with python to track human
  if(Serial.available() > 0)
  {
    if(Serial.read() == 'X')
    {
      x = Serial.parseInt();
      if (x > threshold) {
        moveServo(s3, oldPosX - i);
        oldPosX -= i;
        // delay(t);
      }
      if (x < -threshold) {
        moveServo(s3, oldPosX + i);
        oldPosX += i;
        //  delay(t);
      }

      if(Serial.read() == 'Y')
      {
        y = Serial.parseInt();
        if (y > threshold) {
        moveServo(s4, oldPosY4 - i);
        // s2.write(oldPosY1 - 0.5*i);
        oldPosY4 -= i;
        // oldPosY1 -= i;
        //  delay(t);
      }
      if (y < -threshold) {
        moveServo(s4, oldPosY4 + i);
        // s4.write(oldPosY4 + 0.5*i);
        oldPosY4 += i;
        // oldPosY4 += i;
        //  delay(t);
      }

      if ((x > -threshold and x < threshold) and ((y > -threshold and y < threshold))) { 
        delay(1500);
        Serial.print("snap");
        delay(18000);
        moveServo(s8, 90);
        moveServo(s9, 90);
        moveServo(s10, 0);
        moveServo(s11, 0);
        delay(1000);
        for (int i = 90; i>0; i--) {
          moveServo(s9, i);
          delay(40);
        }
        for (int i = 0; i<55; i++) {
          moveServo(s10, i);
          delay(40);
        }
        delay(500);
          moveServo(s11, 90);
        for (int i = 90; i>60; i--) {
          moveServo(s8, i);
          delay(40);
        }
        delay(1000);
        moveServo(s11,0);
        delay(1000);
 
        for (int i = 50; i<90; i++) {
          moveServo(s10, i);
          delay(40);
        }
        for (int i =0; i<90; i++) {
          moveServo(s9, i);
          delay(40);
        }
        delay(2000);

        moveServo(s11, 90);

        delay(2000);

        moveServo(s8, 90);
        moveServo(s9, 90);
        moveServo(s10, 0);
        moveServo(s11, 0);
        //S

      }
      }
    } 
    
    while(Serial.available() > 0)
    {
      Serial.read();
    }
  }

}

void moveServo(int servo, int pulse) {
  int pulseValue = map(pulse, 0, 180, minPulse, maxPulse);
  pwm.setPWM(servo, 0, pulseValue);
}
