#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
int tgl;
int i,n,m;
String bulan[12] = {
  "Januari",
  "Februari",
  "Maret",
  "April",
  "Mei",
  "Juni",
  "Juli",
  "Agustus",
  "September",
  "Oktober",
  "November",
  "Desember"
};
int data;
int var;
int x,y;
int num1=0,num2=0, num3=0;
LiquidCrystal_I2C lcd(0x27,16,2);

//---------------------------deklarasi pin-----------------------------//
int proximity = 8;
int tombol[8] = {
  0,  //atas
  1,  //bawah
  2,  //kanan
  3,  //kiri
  4,  //menu
  5,  //pause
  6,  //mulai
  7   //reset
};

int Ac= 37;
int Bc= 39;
int Cc= 41;
int Dc= 43;
int Ec= 45;
int Fc= 47;
int Gc= 49;

int Ab= 23;
int Bb= 25;
int Cb= 27;
int Db= 29;
int Eb= 31;
int Fb= 33;
int Gb= 35;
 
int Aa=  34;
int Ba=  32;
int Ca=  30;
int Da=  28;
int Ea=  26;
int Fa=  24;
int Ga=  22;

void setup()
{
  Serial.begin(115200);
  tgl = EEPROM.read(0);
  i = EEPROM.read(1);
  m = EEPROM.read(2);
  data = EEPROM.read(3);
  num1 = data/100;
  num2 = (data/10)-(num1*10);
  num3 = data-((num2*10)+(num1*100));
  pinMode(proximity, INPUT);
  for(x=0; x<8; x++) {
    pinMode(tombol[x], INPUT_PULLUP);
  }
  
  pinMode(Aa, OUTPUT);
  pinMode(Ba, OUTPUT);
  pinMode(Ca, OUTPUT);
  pinMode(Da, OUTPUT);
  pinMode(Ea, OUTPUT);
  pinMode(Fa, OUTPUT);
  pinMode(Ga, OUTPUT);

  pinMode(Ab, OUTPUT);
  pinMode(Bb, OUTPUT);
  pinMode(Cb, OUTPUT);
  pinMode(Db, OUTPUT);
  pinMode(Eb, OUTPUT);
  pinMode(Fb, OUTPUT);
  pinMode(Gb, OUTPUT);

  pinMode(Ac, OUTPUT);
  pinMode(Bc, OUTPUT);
  pinMode(Cc, OUTPUT);
  pinMode(Dc, OUTPUT);
  pinMode(Ec, OUTPUT);
  pinMode(Fc, OUTPUT);
  pinMode(Gc, OUTPUT);
  
  lcd.init();
  lcd.backlight();
}


void loop()
{
  if((digitalRead(tombol[4])) == LOW) {
  lcd.clear();
    menu();
  }
  k:
  tampilan();
  count();
  display_ratusan(num1);
  display_puluhan(num2);
  display_satuan(num3);
  Serial.print(num1);
  Serial.print("   ");
  Serial.print(num2);
  Serial.print("   ");
  Serial.print(num3);
  Serial.print("   ");
  Serial.println(data);
}

void count() {
  if ((digitalRead(proximity)) == LOW) {
    data = data+1;
    num1 = data/100;
    num2 = (data/10)-(num1*10);
    num3 = data-((num2*10)+(num1*100));
  }
    while(1) {
      if((digitalRead(proximity)) == HIGH) {
        goto u;
      }
    }
  u:
  data=data;
  if((digitalRead(tombol[7])) == LOW) {
    data=0;
    num1=0;
    num2=0;
    num3=0;
    lcd.clear();
//    lcd.setCursor(14,1);
//    lcd.print(" ");
  }
  if((digitalRead(tombol[5])) == LOW) {
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("pause");
    while(1) {
      if((digitalRead(tombol[6])) == LOW) {
        lcd.clear();
        lcd.setCursor(5,0);
        lcd.print("play");
        goto u;
      }
    }
  }
  else {
    data=data;
  }
  EEPROM.write(3, data);
}
