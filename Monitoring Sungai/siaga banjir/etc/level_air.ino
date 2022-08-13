#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define TRIG 12 //D5
#define ECHO 14 //D6
#define LAMP 13 //D7
#define BUZZ 15 //D8

int countTime = 0;
int countNum = 0;
int distance;
int dataSum = 0;
int sample;
const char* ssid = "Al -Firdaus";
const char* password = "12345678";

LiquidCrystal_I2C lcd(0x27, 16, 2);
FirebaseData firebaseData;

void setup() {

  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT_PULLUP);
  pinMode(LAMP, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  digitalWrite(LAMP, HIGH);
  digitalWrite(BUZZ, HIGH);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Loading...");

  WiFi.begin(ssid, password);
  //memulai menghubungkan ke wifi router
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); //status saat mengkoneksikan
  }
  Serial.println("Sukses terkoneksi wifi!");
  Serial.println("IP Address:"); //alamat ip lokal
  Serial.println(WiFi.localIP());

  Firebase.begin("https://monitoring-daya-b4a10-default-rtdb.firebaseio.com/", "Nl6BkZSuHEDtVvbJNkvztAnLubUbtCLYluHWCLoH");
}

void loop() {

  for (countNum = 0; countNum < 10; countNum++) {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG, HIGH);
    delayMicroseconds(20);

    digitalWrite(TRIG, LOW);
    sample = pulseIn(ECHO, HIGH, 26000);
    sample = sample / 58;
    dataSum = dataSum + sample;
  }

  distance = dataSum / 10;
  dataSum = 0;

  Serial.print("Distance ");
  Serial.print(distance);
  Serial.println("cm");

  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.setCursor(0, 1);
  lcd.print(distance, 1);
  lcd.print("   ");
  lcd.setCursor(6, 1);
  lcd.print(" cm  ");

  Serial.printf("data... %s\n", Firebase.setInt(firebaseData, "/data/level", distance) ? "ok" : firebaseData.errorReason().c_str());

  if (distance <= 300) {
    digitalWrite(LAMP, LOW);
    digitalWrite(BUZZ, LOW);
    Serial.printf("status... %s\n", Firebase.setString(firebaseData, "/data/status", "Siaga") ? "ok" : firebaseData.errorReason().c_str());
  }

  else {
    digitalWrite(LAMP, HIGH);
    digitalWrite(BUZZ, HIGH);
    Serial.printf("status... %s\n", Firebase.setString(firebaseData, "/data/status", "Aman") ? "ok" : firebaseData.errorReason().c_str());
  }
}
