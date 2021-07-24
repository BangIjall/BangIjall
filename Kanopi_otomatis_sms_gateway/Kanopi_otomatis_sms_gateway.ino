#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
#include <Wire.h>
#include <Servo.h>

// inialisasi servo
Servo servo1;

// inialisasi pin sensor
const int pinHujan = A0;
const int pinLdr = 5;
const int led = 6;

// inialisasi derajat buka-tutup servo
int tutup = 110;
int buka = 10;

SMSGSM arduino;
char number[20];
byte stat = 0;

// ------------------------ program default awal ------------------------ //

void setup()
{
  // setting baud rate serial monitor
  Serial.begin(9600);

  // inialisasi pin servo
  servo1.attach(9);

  // inialisasi status input/output pin
  pinMode(pinHujan, INPUT);
  pinMode(pinLdr, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  servo1.write(tutup);
  Serial.println("GSM Shield testing.");
  if (gsm.begin(9600))
    Serial.println("\nstatus=READY");
  else Serial.println("\nstatus=IDLE");
  digitalWrite(led, HIGH);
}



// -------------------------- program utama --------------------------- //

void loop()
{
  // sensor hujan akan bernilai = 0 saat ada air
  // sensor cahaya akan bernilai = 1 saat gelap
  // dan berlaku sebaliknya

  // jika kondisi hujan dan mendung
  if (((analogRead(pinHujan)) >= 200 && (digitalRead(pinLdr)) == 1) || ((analogRead(pinHujan)) >= 200 && (digitalRead(pinLdr)) == 0) || ((analogRead(pinHujan)) <= 200 && (digitalRead(pinLdr)) == 1))
  {
    nutup();
  }

  if ((analogRead(pinHujan)) <= 200 && (digitalRead(pinLdr)) == 0)
  {
    mbukak();
  }

  // delay jalannya program
  delay(300);
}

void nutup() {
  servo1.write(tutup);
  arduino.SendSMS("087828754187", "Kanopi akan menutup");
  while (1) {
    Serial.println("nutup");
    if ((analogRead(pinHujan)) <= 500 && (digitalRead(pinLdr)) == 0)
    {
      break;
    }
  }
  mbukak();
}

void mbukak() {
  servo1.write(buka);
  while (1) {
    Serial.println("buka");
    if (((analogRead(pinHujan)) >= 200 && (digitalRead(pinLdr)) == 1) || ((analogRead(pinHujan)) >= 200 && (digitalRead(pinLdr)) == 0) || ((analogRead(pinHujan)) <= 200 && (digitalRead(pinLdr)) == 1))
    {
      break;
    }
  }
  nutup();
}
