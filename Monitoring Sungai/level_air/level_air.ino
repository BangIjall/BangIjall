#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define TRIG 12 //D5
#define ECHO 14 //D6
#define LAMP 13 //D7
#define BUZZ 15 //D8

int kedalaman = 370;
int countTime = 0;
int countNum = 0;
int distance;
int dataSum = 0;
int sample;
const char* ssid = "Al -Firdaus";
const char* password = "12345678";

const char* serverName = "http://siagabanjir.com/inc/post-level.php";
//const char* serverName = "http://ramiwonosobo123.000webhostapp.com/post-data.php";
String apiKeyValue = "tPmAT5Ab3j7F9";

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
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Sukses terkoneksi wifi!");
  Serial.println("IP Address:");
  Serial.println(WiFi.localIP());

  Firebase.begin("https://tasiagabanjir-default-rtdb.asia-southeast1.firebasedatabase.app/", "HiJdgTb1xuK39pvJmKpVhU5UItOJe1mtfjBWA1e8");
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
  distance = kedalaman - distance;
  
  dataSum = 0;

  Serial.print("Distance ");
  Serial.print(distance);
  Serial.println("cm");

  Serial.printf("data... %s\n", Firebase.setInt(firebaseData, "/data/level", distance) ? "ok" : firebaseData.errorReason().c_str());

  if (distance <= 150) {
    digitalWrite(LAMP, HIGH);
    digitalWrite(BUZZ, LOW);
    Serial.printf("status... %s\n", Firebase.setString(firebaseData, "/data/status", "Bahaya") ? "ok" : firebaseData.errorReason().c_str());
    lcd.setCursor(0, 1);
    lcd.print("Status : ");
    lcd.print(" Bahaya  ");
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      http.begin(client, serverName);

      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String httpRequestData = "api_key=" + apiKeyValue + "&value1=" + String(distance)
                               + "&value2=" + String("Bahaya") + "";
      Serial.print("httpRequestData: ");
      Serial.println(httpRequestData);

      int httpResponseCode = http.POST(httpRequestData);

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }

  if (distance > 150 && distance <= 280) {
    digitalWrite(LAMP, LOW);
    digitalWrite(BUZZ, HIGH);
    Serial.printf("status... %s\n", Firebase.setString(firebaseData, "/data/status", "Siaga") ? "ok" : firebaseData.errorReason().c_str());
    lcd.setCursor(0, 1);
    lcd.print("Status : ");
    lcd.print(" Siaga  ");
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      http.begin(client, serverName);

      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String httpRequestData = "api_key=" + apiKeyValue + "&value1=" + String(distance)
                               + "&value2=" + String("Siaga") + "";
      Serial.print("httpRequestData: ");
      Serial.println(httpRequestData);

      int httpResponseCode = http.POST(serverName + httpRequestData);

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }

  if (distance > 280) {
    digitalWrite(LAMP, HIGH);
    digitalWrite(BUZZ, HIGH);
    Serial.printf("status... %s\n", Firebase.setString(firebaseData, "/data/status", "Aman") ? "ok" : firebaseData.errorReason().c_str());
    lcd.setCursor(0, 1);
    lcd.print("Status : ");
    lcd.print(" Aman   ");
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      http.begin(client, serverName);

      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String httpRequestData = "api_key=" + apiKeyValue + "&value1=" + String(distance)
                               + "&value2=" + String("Aman") + "";
      Serial.print("httpRequestData: ");
      Serial.println(httpRequestData);

      int httpResponseCode = http.POST(serverName + httpRequestData);

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      unsigned long timeout = millis();
      while (client.connected() && millis() - timeout < 10000L) {
        while (client.available()) {
          char c = client.read();
          Serial.print(c);
          timeout = millis();
        }
      }
      Serial.println();
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("Level:");
  lcd.print(distance, 1);
  lcd.print("   ");
  lcd.setCursor(12, 0);
  lcd.print(" cm  ");

  delay(10000);
}
