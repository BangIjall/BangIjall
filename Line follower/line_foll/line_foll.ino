float PV; // PV(Present Value) = process value atau nilai aktual pembacaan
int pwmkanan;
int pwmkiri;
int MINPWM = 0;
int MAXPWM = 100;//maksimal 255
int MV;// Modificated Value merupakan nilai kalkulasi untuk mengoreksi error(hasil dari PID)
float P;
float I;
float D;
float Kp;
float Ki;
float Kd;
float Ts;
float error;
float lasterror;
float ratei;
float rated;
#define SP 0 // SP = set point atau nilai acuan
#include <Wire.h>
#include <EEPROM.h>
#define kendaliLed1 12
#define kendaliLed2 13
#define kendaliTombol 2
#define motorkanan 9
#define motorkanangnd 10
#define motorkiri 5
#define motorkirignd 6
unsigned int sensor[6], nilaiMin[6], nilaiMax[6], nilaiRef[6];
int i, x=0;
boolean biner[6];

void setup() {
pinMode (motorkanan, OUTPUT);
pinMode (motorkanangnd, OUTPUT);
pinMode (motorkiri, OUTPUT);
pinMode (motorkirignd, OUTPUT);
pinMode (kendaliLed1, OUTPUT);
pinMode (kendaliLed2, OUTPUT);
pinMode (kendaliTombol, INPUT);
digitalWrite(kendaliTombol, HIGH);
Serial.begin(115200);
dataSensor();
}

void loop() {
analogWrite (motorkanangnd,0);
analogWrite (motorkirignd,0);
KendaliBacasensor ();
tampilDatasensor();
KendaliTampilsensor ();
if (digitalRead(kendaliTombol)==LOW)
  {
    analogWrite (motorkanan,0);
    analogWrite (motorkiri,0);
    while (digitalRead(kendaliTombol)==LOW){
    }
  kalibrasi();
  }
 
 //PID, SP = 0
     if ((biner[0]==1) &&(biner[1]==1) &&(biner[2]==1) &&(biner[3]==1) &&(biner[4]==1) &&(biner[5]==0)   ) PV = -5;
else if ((biner[0]==1) &&(biner[1]==1) &&(biner[2]==1) &&(biner[3]==0) &&(biner[4]==0) &&(biner[5]==0)   ) PV = -4;
else if ((biner[0]==1) &&(biner[1]==1) &&(biner[2]==1) &&(biner[3]==1) &&(biner[4]==0) &&(biner[5]==0)   ) PV = -4;
else if ((biner[0]==1) &&(biner[1]==1) &&(biner[2]==1) &&(biner[3]==1) &&(biner[4]==0) &&(biner[5]==1)   ) PV = -3;
else if ((biner[0]==1) &&(biner[1]==1) &&(biner[2]==0) &&(biner[3]==0) &&(biner[4]==0) &&(biner[5]==1)   ) PV = -2;
else if ((biner[0]==1) &&(biner[1]==1) &&(biner[2]==1) &&(biner[3]==0) &&(biner[4]==0) &&(biner[5]==1)   ) PV = -2;
else if ((biner[0]==1) &&(biner[1]==1) &&(biner[2]==1) &&(biner[3]==0) &&(biner[4]==1) &&(biner[5]==1)   ) PV = -1;

else if ((biner[0]==1) &&(biner[1]==1) &&(biner[2]==0) &&(biner[3]==0) &&(biner[4]==1) &&(biner[5]==1)   ) PV = 0; // SP

else if ((biner[0]==1) &&(biner[1]==1) &&(biner[2]==0) &&(biner[3]==1) &&(biner[4]==1) &&(biner[5]==1)   ) PV = 1;
else if ((biner[0]==1) &&(biner[1]==0) &&(biner[2]==0) &&(biner[3]==0) &&(biner[4]==1) &&(biner[5]==1)   ) PV = 2;
else if ((biner[0]==1) &&(biner[1]==0) &&(biner[2]==0) &&(biner[3]==1) &&(biner[4]==1) &&(biner[5]==1)   ) PV = 2;
else if ((biner[0]==1) &&(biner[1]==0) &&(biner[2]==1) &&(biner[3]==1) &&(biner[4]==1) &&(biner[5]==1)   ) PV = 3;
else if ((biner[0]==0) &&(biner[1]==0) &&(biner[2]==0) &&(biner[3]==1) &&(biner[4]==1) &&(biner[5]==1)   ) PV = 4;
else if ((biner[0]==0) &&(biner[1]==0) &&(biner[2]==1) &&(biner[3]==1) &&(biner[4]==1) &&(biner[5]==1)   ) PV = 4;
else if ((biner[0]==0) &&(biner[1]==1) &&(biner[2]==1) &&(biner[3]==1) &&(biner[4]==1) &&(biner[5]==1)   ) PV = 5;
else if ((biner[0]==1) &&(biner[1]==1) &&(biner[2]==1) &&(biner[3]==1) &&(biner[4]==1) &&(biner[5]==1)   ) PV = 6;

    Kp = (MAXPWM/3);
    Ki = 0.002;
    Kd = 2.5;
    Ts = 0.0001; //time sampling
    error = SP - PV;
    P = Kp * error;             //PROPORSIONAL
    rated = error - lasterror;
    D = Kd / Ts * rated;        //DERIVATIF
    ratei = error + lasterror;
    I = Ki * ratei * Ts ;        //INTEGRAL
    lasterror = error;
    
    MV = P; // kendali yang digunakan proporsional
//   MV = P + D; // kendali yang digunakan proporsional derivatif
//    MV = P + I + D; // kendali yang digunakan proporsional integral derivatif
  
    if (MV == 0)
    {
      pwmkiri = MAXPWM;
      pwmkanan = MAXPWM;
    }
  
    else if (MV > 0) //alihkan ke kanan
    {
      pwmkiri = MAXPWM ;
      pwmkanan = MAXPWM - MV;
      if (pwmkiri <MINPWM) pwmkiri = MINPWM;
      if (pwmkiri >MAXPWM) pwmkiri = MAXPWM;
    }
  
    else if (MV < 0) //alihkan ke kiri
    {
      pwmkiri = MAXPWM + MV;
      pwmkanan = MAXPWM  ;
      if (pwmkanan <MINPWM) pwmkanan = MINPWM;
      if (pwmkanan >MAXPWM) pwmkanan = MAXPWM;
    }
      if (pwmkiri <= 0)pwmkiri = 0;//nilai pwm tidak boleh min jika min atau lebih dari 255 maka perhitungannya beda balik lagi ke 0 baca di google buat prinsip nilai timer
      if (pwmkanan <= 0)pwmkanan = 0;
analogWrite (motorkanan,pwmkanan);
analogWrite (motorkiri,pwmkiri);
Serial.print("   ");
Serial.print("ERROR =  ");
Serial.print(error);
Serial.print("   ");
Serial.print("P =  ");
Serial.print(P);
Serial.print("   ");
Serial.print("D =  ");
Serial.print(D);
Serial.print("   ");
Serial.print("I =  ");
Serial.print(I);
Serial.print("   ");
Serial.print("MV =  ");
Serial.print(MV);
Serial.print("     ");
Serial.print("pwmkanan =  ");
Serial.print(pwmkanan);
Serial.print("     ");
Serial.print("pwmkiri =  ");
Serial.println(pwmkiri);
}
