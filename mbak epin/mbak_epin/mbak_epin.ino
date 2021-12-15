#include <SPI.h>
#include <SD.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

RTC_DS3231 rtc;
char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
String hari;
int tanggal, bulan, tahun, jam, menit, detik;

LiquidCrystal_I2C lcd(0x27,20,4); 

const int rst=9;
const int sda=10;
const int door_lock=6;
const int relay=8;
const int cs=4;
bool on=LOW;
bool off=HIGH;
String id;
const int led_hijau=2;
const int led_biru=3;
const int buzzer=5;

float sinVal;
int toneVal;

MFRC522 rfid(sda, rst);
File file;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Sistem Siap!!!");
  if (!rtc.begin()) 
  {
    Serial.println("RTC Tidak Ditemukan");
    Serial.flush();
    abort();
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));\

  pinMode(led_hijau, OUTPUT);
  pinMode(led_biru, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(door_lock, OUTPUT);
  lcd.begin(20,4);
  lcd.backlight();
  while(!Serial){
    ;
  }
  SPI.begin();
  digitalWrite(relay,off);
  digitalWrite(door_lock,off);
  delay(500);
  rfid.PCD_Init();
  lcd.init();
  
  lcd.setCursor(3,1);
  lcd.print("Sistem Siap!!!");
  delay(1000);
  lcd.clear();
  
  lcd.setCursor(0,1);
  lcd.print("Selamat");
  lcd.setCursor(0,2);
  lcd.print("Datang");
  
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) 
  {
    lcd.scrollDisplayRight();
    delay(400);
  }
  
  delay(1000);
  lcd.clear();

  DateTime now = rtc.now();
  hari    = dataHari[now.dayOfTheWeek()];
  tanggal = now.day(), DEC;
  bulan   = now.month(), DEC;
  tahun   = now.year(), DEC;
  jam     = now.hour(), DEC;
  menit   = now.minute(), DEC;
  detik   = now.second(), DEC;
  
  lcd.setCursor(4,0);
  lcd.print("TA Yosephine");
  lcd.setCursor(3,1);
  lcd.print("Tap Your Card!");
  
  lcd.setCursor(0,2);
  lcd.print("Tgl");
  lcd.setCursor(4,2);
  lcd.print(":");
  lcd.setCursor(6,2);
  lcd.print(tanggal);
  lcd.setCursor(8,2);
  lcd.print("-");
  lcd.setCursor(9,2);
  lcd.print(bulan);
  lcd.setCursor(10,2);
  lcd.print("-");
  lcd.setCursor(11,2);
  lcd.print(tahun);
  
  lcd.setCursor(0,3);
  lcd.print("Jam");
  lcd.setCursor(4,3);
  lcd.print(":");
  lcd.setCursor(6,3);
  lcd.print(jam);
  lcd.setCursor(8,3);
  lcd.print(":");
  lcd.setCursor(9,3);
  lcd.print(menit);
  lcd.setCursor(11,3);
  lcd.print(":");
  lcd.setCursor(12,3);
  lcd.print(detik);
  
  digitalWrite(led_hijau,LOW);
  digitalWrite(led_biru,LOW);
  digitalWrite(buzzer,on);
}

void loop() 
{
  lcd.backlight();
  cekRfid();
  delay(1500);

  DateTime now = rtc.now();
  hari    = dataHari[now.dayOfTheWeek()];
  tanggal = now.day(), DEC;
  bulan   = now.month(), DEC;
  tahun   = now.year(), DEC;
  jam     = now.hour(), DEC;
  menit   = now.minute(), DEC;
  detik   = now.second(), DEC;
  
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("TA Yosephine");
  lcd.setCursor(3,1);
  lcd.print("Tap Your Card!");
  
  lcd.setCursor(0,2);
  lcd.print("Tgl");
  lcd.setCursor(4,2);
  lcd.print(":");
  lcd.setCursor(6,2);
  lcd.print(tanggal);
  lcd.setCursor(8,2);
  lcd.print("-");
  lcd.setCursor(9,2);
  lcd.print(bulan);
  lcd.setCursor(10,2);
  lcd.print("-");
  lcd.setCursor(11,2);
  lcd.print(tahun);
  
  lcd.setCursor(0,3);
  lcd.print("Jam");
  lcd.setCursor(4,3);
  lcd.print(":");
  lcd.setCursor(6,3);
  lcd.print(jam);
  lcd.setCursor(8,3);
  lcd.print(":");
  lcd.setCursor(9,3);
  lcd.print(menit);
  lcd.setCursor(11,3);
  lcd.print(":");
  lcd.setCursor(12,3);
  lcd.print(detik);
}

void cekRfid()
{
  if(rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
  {
    Serial.println("ID: ");
    for(int i=0; i<=3; i++)
    {
      id=id+(rfid.uid.uidByte[i]<0x10 ? "0" : "") + String(rfid.uid.uidByte[i],HEX) + (i==3 ? "" : ":");
    }
    id.toUpperCase();
  
    if(id=="B3:41:3A:3E")
    {
      digitalWrite(led_hijau,HIGH);
      delay(1500);
      digitalWrite(relay,off);
      delay(300);
      digitalWrite(door_lock,on);
      delay(3500);
      digitalWrite(led_hijau,LOW);
      delay(1500);
      digitalWrite(relay,on);
      delay(300);
      digitalWrite(door_lock,off);
      delay(3500);
    }
    
    else if(id=="6E:CF:24:1F")
    {
      digitalWrite(led_hijau,HIGH);
      delay(1500);
      digitalWrite(relay,off);
      delay(300);
      digitalWrite(door_lock,on);
      delay(3500);
      digitalWrite(led_hijau,LOW);
      delay(1500);
      digitalWrite(relay,on);
      delay(300);
      digitalWrite(door_lock,off);
      delay(3500);
    }
    
    else if(id=="02:3F:E2:A8")
    {
      digitalWrite(led_hijau,HIGH);
      delay(1500);
      digitalWrite(relay,off);
      delay(300);
      digitalWrite(door_lock,on);
      delay(3500);
      digitalWrite(led_hijau,LOW);
      delay(1500);
      digitalWrite(relay,on);
      delay(300);
      digitalWrite(door_lock,off);
      delay(3500);
    }
    
    else
    {
      for (int x=0; x<180; x++)
      {
        sinVal = (sin(x * (3.1412 / 180)));
        toneVal = 1000 + (int(sinVal * 1000));
        tone(buzzer, toneVal);
        delay(700);
        noTone(buzzer);

        digitalWrite(led_biru,HIGH);
        digitalWrite(relay,off);
        //digitalWrite(buzzer,off);
        delay(2000);
        digitalWrite(led_biru,LOW);
        digitalWrite(relay,on);
        //digitalWrite(buzzer,on);
        delay(2000);
        break;
      }
    }
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
      tampilkan();
      inputData();
  }
}

void tampilkan()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ID ");
  lcd.setCursor(4,0);
  lcd.print(":");
  lcd.setCursor(6,0);
  lcd.print(id);

  DateTime now = rtc.now();
  hari    = dataHari[now.dayOfTheWeek()];
  tanggal = now.day(), DEC;
  bulan   = now.month(), DEC;
  tahun   = now.year(), DEC;
  jam     = now.hour(), DEC;
  menit   = now.minute(), DEC;
  detik   = now.second(), DEC;

  lcd.setCursor(0,2);
  lcd.print("Hari");
  lcd.setCursor(4,2);
  lcd.print(":");
  lcd.setCursor(6,2);
  lcd.print(hari);

  lcd.setCursor(0,1);
  lcd.print("Jam");
  lcd.setCursor(4,1);
  lcd.print(":");
  lcd.setCursor(6,1);
  lcd.print(jam);
  lcd.setCursor(8,1);
  lcd.print(":");
  lcd.setCursor(9,1);
  lcd.print(menit);
  lcd.setCursor(11,1);
  lcd.print(":");
  lcd.setCursor(12,1);
  lcd.print(detik);

  lcd.setCursor(0,3);
  lcd.print("Tgl");
  lcd.setCursor(4,3);
  lcd.print(":");
  lcd.setCursor(6,3);
  lcd.print(tanggal);
  lcd.setCursor(8,3);
  lcd.print("-");
  lcd.setCursor(9,3);
  lcd.print(bulan);
  lcd.setCursor(10,3);
  lcd.print("-");
  lcd.setCursor(11,3);
  lcd.print(tahun);
  
  delay(3000);
  lcd.clear();
}

void inputData()
{
  digitalWrite(relay,on);
  SD.begin(cs);
  file = SD.open("hasil.txt", FILE_WRITE);
  if(file)
  {
    file.print(id);
    file.print("_");
    file.print(hari);
    file.print(",");
    file.print(tanggal);
    file.print("-");
    file.print(bulan);
    file.print("-");
    file.print(tahun);
    file.print("_");
    file.println(jam);
    file.print(":");
    file.println(menit);
    file.print(":");
    file.println(detik);
    Serial.println(id);
    Serial.println("Data berhasil ditambahkan!!!");
    file.close();
  }
  
  else
  {
    Serial.println("Data error, gagal menyimpan!!!");
  }
  id="";
  digitalWrite(relay,off);
}
