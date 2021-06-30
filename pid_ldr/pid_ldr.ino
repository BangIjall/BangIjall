#include <Arduino.h>
  int error,prev_error,prev_speed,sum_error;
  int setpoint = 50;
  double kp = 0.2;
  double ki = 0;
  double kd = 0;
void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(6,OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  int ldr = map(analogRead(A0),0,1023,0,255);
  error = setpoint-ldr;
  int pwm = error*kp + sum_error*ki + (error-prev_error)*kd;
  prev_error = error;
  sum_error += error;
  analogWrite(6,10);
  Serial.println(ldr);
  // put your main code here, to run repeatedly:

}
