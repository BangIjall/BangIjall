#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
#include "call.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
CallGSM call;
SMSGSM arduino;
char number[20];
byte stat = 0;
int value = 0;
int pin = 1;
char value_str[5];
int analogPin = A0;
float suhu = 00;
int suhu1 = 00;
String data;


void setup() {
  Serial.begin(9600);
  pinMode(pin, INPUT);
  lcd.begin();
  lcd.backlight();
  lcd.print("Starting Device");
  Serial.println("GSM Shield testing.");
  if (gsm.begin(9600))
    Serial.println("\nstatus=READY");
  else Serial.println("\nstatus=IDLE");
  lcd.clear();
  lcd.print("     READY");
  delay(1000);
  lcd.clear();
};

void loop() {
  temperature();
  stat = call.CallStatusWithAuth(number, 0, 0);
  if (stat == CALL_INCOM_VOICE_AUTH || suhu >= 100)
  {
    call.HangUp();
    delay(2000);
    value = digitalRead(1);
    itoa(value, value_str, 10);
    arduino.SendSMS("087821756061", data.c_str());
  }
  delay(1000);
};

void temperature() {
  suhu1 = analogRead(analogPin);
  suhu = suhu1 / 2.0479;
  Serial.println(suhu);
  lcd.setCursor(0,0);
  lcd.print("Suhu : ");
  lcd.setCursor(0,7);
  lcd.print(suhu);
  data = suhu;
}
