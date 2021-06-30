#include <Arduino.h>
#include "main.h"
#include <Wire.h>
#include <LiquidCrystal.h>
#include <TimerOne.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
volatile bool isStart;
const char pinOutput[] = {ledSTART, ledSTOP, ledDIS, ledEN, ledON, m1ON, m2RIGHT, m2LEFT, mPWM, BUZZER,ledM2ON,ledM2OFF};

void startFunc()
{
  isStart = true;
  if (digitalRead(limitNC) == LOW) //posisi saklar normally close
  {
    digitalWrite(BUZZER, HIGH);
  }
}
void forwardFunc()
{
  if (digitalRead(M2START) == LOW)
  {
    digitalWrite(m2RIGHT, HIGH);
    digitalWrite(m2LEFT, LOW);
  }
}
void reverseFunc()
{
  if (digitalRead(M2START) == LOW)
  {
    digitalWrite(m2RIGHT, LOW);
    digitalWrite(m2LEFT, HIGH);
  }
}
void emergencyFunc()
{
  digitalWrite(m2RIGHT, LOW);
  digitalWrite(m2LEFT, LOW);
}
void stopFunc()
{
  digitalWrite(m1ON, LOW);
  isStart = false;
}
void resetFunc()
{
  digitalWrite(BUZZER, LOW);
  lcd.clear();
  isStart=false;
}
void motor()
{
  int speed = map(analogRead(PWM), 0, 1023, 0, 255);
  analogWrite(mPWM, speed);
}
void normallyOpen()
{
  Serial.println(isStart);
  if (isStart == false)
  {
    lcd.setCursor(0, 0);
    lcd.print("Ready          ");
    digitalWrite(m1ON, LOW);
    digitalWrite(ledDIS, HIGH);
    digitalWrite(ledEN, LOW);
    digitalWrite(ledSTOP, HIGH);
    digitalWrite(ledSTART, LOW);
  }
  if (isStart == true)
  {
    lcd.setCursor(0, 0);
    lcd.print("Dead slow AHD");
    digitalWrite(m1ON, HIGH);
    digitalWrite(ledON, HIGH);
    digitalWrite(ledDIS, LOW);
    digitalWrite(ledEN, LOW);
    digitalWrite(ledSTOP, LOW);
    digitalWrite(ledSTART, HIGH);
  }
}

void normallyClose()
{
  if (isStart == false)
  {
    lcd.clear();
    analogWrite(mPWM, 0);
    digitalWrite(ledDIS, LOW);
    digitalWrite(ledEN, HIGH);
    digitalWrite(ledSTOP, HIGH);
    digitalWrite(ledSTART, LOW);
  }
  if (isStart == true)
  {
    lcd.setCursor(0, 0);
    lcd.print("INTERLOCK");
    digitalWrite(m1ON, LOW);
    digitalWrite(ledDIS, LOW);
    digitalWrite(ledEN, HIGH);
    digitalWrite(ledSTOP, HIGH);
    digitalWrite(ledSTART, LOW);
  }
}
void motor2(){
  motor();
  if(digitalRead(M2START)==LOW){
    digitalWrite(ledM2OFF,HIGH);
    digitalWrite(ledM2ON,LOW);
  }
  if(digitalRead(M2START)==LOW&&digitalRead(pbFWD)==LOW){
    digitalWrite(ledM2OFF,LOW);
    digitalWrite(ledM2ON,HIGH);
    digitalWrite(m2RIGHT,HIGH);
    digitalWrite(m2LEFT,LOW);
  }
  if(digitalRead(M2START)==LOW&&digitalRead(pbREV)==LOW){
    digitalWrite(ledM2OFF,LOW);
    digitalWrite(ledM2ON,HIGH);
    digitalWrite(m2RIGHT,LOW);
    digitalWrite(m2LEFT,HIGH);
  }
  if(digitalRead(pbREV)==HIGH&&digitalRead(pbFWD)==HIGH)
  {
    digitalWrite(ledM2OFF,HIGH);
    digitalWrite(ledM2ON,LOW);
    digitalWrite(m2RIGHT,LOW);
    digitalWrite(m2LEFT,LOW);
  }
  if(digitalRead(M2START)==HIGH)
  {
    digitalWrite(ledM2OFF,LOW);
    digitalWrite(ledM2ON,LOW);
    digitalWrite(m2RIGHT,LOW);
    digitalWrite(m2LEFT,LOW);
  }
  
}
void setup()
{
  pinMode(limitNO, INPUT_PULLUP);
  pinMode(limitNC, INPUT_PULLUP);
  pinMode(pbREV, INPUT_PULLUP);
  pinMode(pbFWD, INPUT_PULLUP);
  pinMode(pbSTART, INPUT_PULLUP);
  pinMode(pbSTOP, INPUT_PULLUP);
  pinMode(pbRST, INPUT_PULLUP);
  pinMode(M2START, INPUT_PULLUP);
  pinMode(EMERGENCY, INPUT_PULLUP);
  for (int i = 0; i < 12; i++)
  {
    pinMode(pinOutput[i], OUTPUT);
  }
  attachInterrupt(digitalPinToInterrupt(pbSTART), startFunc, FALLING);
  // attachInterrupt(digitalPinToInterrupt(pbREV), reverseFunc, FALLING);
  // attachInterrupt(digitalPinToInterrupt(pbFWD), forwardFunc, FALLING);
  attachInterrupt(digitalPinToInterrupt(pbSTOP), stopFunc, FALLING);
  attachInterrupt(digitalPinToInterrupt(pbRST), resetFunc, FALLING);
  attachInterrupt(digitalPinToInterrupt(EMERGENCY), emergencyFunc, FALLING);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(motor2);
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop()
{
  if (digitalRead(limitNO) == LOW) //normally open
  {
    lcd.clear();
    isStart = false;
    for (;;)
    {
      normallyOpen();
      if (digitalRead(limitNC) == LOW)
        break;
    }
  }
  else
  {
    lcd.clear();
    if (isStart == true)
      digitalWrite(BUZZER, HIGH);
    for (;;)
    {
      normallyClose();
      if (digitalRead(limitNO) == LOW)
        break;
    }
  }
}
