#include <Arduino.h>
#define L1 1
#define L2 0
#define L3 A5
#define L4 A3
#define L5 A4
#define L6 A2
#define L7 A1
#define L8 A0
#define M1_A 5
#define M1_B 3
#define PWM1 7
#define M2_A 6
#define M2_B 4
#define PWM2 2

int selector[8]={0b00111000,0b00100000,0b00011000,0b00101000,0b00010000,0b00110000,0b00001000,0b00000000};
int kiri,kanan;
float error,sum_error,prev_error;
float kp = 0.38;
float ki = 0;
float kd = 0;
struct sensReading
{
  unsigned int reading;
  unsigned int state;
}s1,s2,s3,s4,s5,s6,s7,s8;
unsigned int sensor[8];
void LED(){
  if(s1.reading<500){s1.state=1;digitalWrite(L1,LOW);}else{s1.state=0;digitalWrite(L1,HIGH);}
  if(s2.reading<500){s2.state=1;digitalWrite(L2,LOW);}else{s2.state=0;digitalWrite(L2,HIGH);}
  if(s3.reading<500){s3.state=1;digitalWrite(L3,LOW);}else{s3.state=0;digitalWrite(L3,HIGH);}
  if(s4.reading<500){s4.state=1;digitalWrite(L4,LOW);}else{s4.state=0;digitalWrite(L4,HIGH);}
  if(s5.reading<500){s5.state=1;digitalWrite(L5,LOW);}else{s5.state=0;digitalWrite(L5,HIGH);}
  if(s6.reading<500){s6.state=1;digitalWrite(L6,LOW);}else{s6.state=0;digitalWrite(L6,HIGH);}
  if(s7.reading<500){s7.state=1;digitalWrite(L7,LOW);}else{s7.state=0;digitalWrite(L7,HIGH);}
  if(s8.reading<500){s8.state=1;digitalWrite(L8,LOW);}else{s8.state=0;digitalWrite(L8,HIGH);}
  kiri  = s1.state+s2.state+s3.state+s4.state;
  kanan = s5.state+s6.state+s7.state+s8.state;
}

void PID() {
  error = kiri-kanan;
  int pwm = error*kp + sum_error*ki + (error-prev_error)*kd;
  prev_error = error;
  sum_error += error;
  // put your main code here, to run repeatedly:
}

void motor(int pwm)
{

}



void motor1(int pwm)
{
  if(pwm>0){
    digitalWrite(M1_A,HIGH);
    digitalWrite(M1_B,LOW);
    analogWrite(PWM1,pwm);
  }
  else if(pwm<0)
  {
    pwm=pwm*-1;
    digitalWrite(M1_A,LOW);
    digitalWrite(M1_B,HIGH);
    analogWrite(PWM1,pwm);
  }
  else
  {
    digitalWrite(M1_A,HIGH);
    digitalWrite(M1_B,LOW);
    analogWrite(PWM1,255);
  }
}
void motor2(int pwm)
{
  if(pwm>0){
    digitalWrite(M2_A,HIGH);
    digitalWrite(M2_B,LOW);
    analogWrite(PWM2,pwm);
  }
  else if(pwm<0)
  {
    pwm=pwm*-1;
    digitalWrite(M2_A,LOW);
    digitalWrite(M2_B,HIGH);
    analogWrite(PWM2,pwm);
  }
  else
  {
    digitalWrite(M2_A,HIGH);
    digitalWrite(M2_B,LOW);
    analogWrite(PWM2,255);
  }
}
void jalan(int pwm)
{
  motor1(pwm);
  motor2(pwm);
}
void speed_kiri(int pwm)
{
  pwm =1000;
  digitalWrite(PWM1,HIGH);
  delayMicroseconds(pwm);
  digitalWrite(PWM1,LOW);
  delayMicroseconds(1000-pwm);
}
void speed_kanan(int pwm)
{
  pwm = 500;
  digitalWrite(PWM2,HIGH);
  delayMicroseconds(pwm);
  digitalWrite(PWM2,LOW);
  delayMicroseconds(1000-pwm);
}
void setup() {
  
  pinMode(A6,INPUT);
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(L3,OUTPUT);
  pinMode(L4,OUTPUT);
  pinMode(L5,OUTPUT);
  pinMode(L6,OUTPUT);
  pinMode(L7,OUTPUT);
  pinMode(L8,OUTPUT);
  pinMode(M1_A,OUTPUT);
  pinMode(M1_B,OUTPUT);
  pinMode(M2_A,OUTPUT);
  pinMode(M2_B,OUTPUT);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);
  DDRB=0x38;
  
  Serial.begin(9600);
  // Serial.begin(19200);
  // put your setup code here, to run once:

}

void loop() {
  for(int i=0;i<8;i++)
  {
    PORTB=selector[i];
    int val = analogRead(A6);
    sensor[i]=val;
  s1.reading = sensor[0];
  s2.reading = sensor[2];
  s3.reading = sensor[6];
  s4.reading = sensor[3];
  s5.reading = sensor[4];
  s6.reading = sensor[5];
  s7.reading = sensor[7];
  s8.reading = sensor[1];
    Serial.print(i);
    Serial.print(" : ");
    Serial.print(sensor[i]);
    Serial.print(" / ");
  }

  LED();
  delay(1);
  Serial.println("  ");
  }
