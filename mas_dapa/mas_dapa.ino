#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define kipas      6
#define DHTPIN     4
#define tepuk      2
#define DHTTYPE    DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int data = 1;
int sumuk = 1;
int modenyaApa = 0;
unsigned long lastTime;
unsigned long lastWaktu;
int t;
int h;
String mode [2] = {"Auto  ", "Manual"};
String nyala [2] = {"ON ", "OFF"};

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin();
  lcd.backlight();
  pinMode(kipas, OUTPUT);
  pinMode(tepuk, INPUT);
  digitalWrite(kipas, sumuk);
  data=0;
  lastWaktu = millis();
  h = dht.readHumidity();
  t = dht.readTemperature();
}

void loop() {
  tampil();

  if(t >= 28) {
    sumuk = 0;
  }
  
  if(t < 28)  {
    sumuk = 1;
  }

  digitalWrite(kipas, sumuk);

  if((digitalRead(tepuk)) == 0) {
    modenyaApa = 1;
    lcd.clear();
    tampil();
    sumuk =! sumuk;
    digitalWrite(kipas, sumuk);
    delay(2000);
    lastTime = millis();
    Serial.println(lastTime);
    Serial.println(millis());
    Serial.println("");
    while((millis() - lastTime) <= 30000) {
      tampil();
      if((digitalRead(tepuk)) == 0) {
        sumuk =! sumuk;
        digitalWrite(kipas, sumuk);
        tampil();
        delay(2000);        
      }        
    }
    modenyaApa = 0;
  }
}

void tampil() {
  if((millis()-lastWaktu) > 2000) {
    h = dht.readHumidity();
    t = dht.readTemperature();    
  }  
  lastWaktu = millis();
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));

  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(t);
  lcd.print("C ");
  lcd.setCursor(8,0);
  lcd.print("H:");
  lcd.print(h);
  lcd.print("%");
  
  lcd.setCursor(0,1);
  lcd.print(mode[modenyaApa]);
  lcd.setCursor(7,1);
  lcd.print("Kipas:");
  lcd.print(nyala[sumuk]);
}
