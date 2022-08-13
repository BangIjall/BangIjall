#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include "ThingSpeak.h"

LiquidCrystal_I2C lcd(0x27,16,2);
#define SENSOR 34

const char* ssid = "OPPO A3s";
const char* password = "modal dikit dong";

WiFiClient client;

unsigned long Channel_ID = 1616536;
const char* API_Key = "W0LAYR7Q3DCUBL9X"; 

unsigned long last_time = 0;
unsigned long Delay = 5000;

float gas;

void setup() {
  Serial.begin(115200);
  lcd.begin();
  lcd.backlight();
  
  Serial.println("Sensor MQ-7 start..");

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);

  lcd.setCursor(2,0);
  lcd.print("Welcome To");
  lcd.setCursor(2,1);
  lcd.print("Tugas Akhir");
  delay(3000);
  lcd.clear();

  lcd.setCursor(1,0);
  lcd.print("Detector Smoke");
  lcd.setCursor(0,1);
  lcd.print("Sen MQ-7 start..");
  delay(2000);
  lcd.clear();

  // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED)
    {
      Serial.print("Connecting...");

      lcd.setCursor(1,0);
      lcd.print("Connecting...");
      
      while(WiFi.status() != WL_CONNECTED)
      {
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }
    
    lcd.setCursor(0,0);
    lcd.print("Sensor Reading..         ");
    delay(3000);
    lcd.clear();
}

void loop() 
{
  if ((millis() - last_time) > Delay) 
  {
        // read the value from the sensor:
    gas = analogRead(SENSOR);
    Serial.print("Value: ");
    Serial.print(gas);
    Serial.println(" ppm");
    
    lcd.setCursor(0,0);
    lcd.print("Value :       ");
    lcd.setCursor(0,1);
    lcd.print(gas);
    lcd.print(" ppm      ");
    
    ThingSpeak.setField(1, gas);
    int Data = ThingSpeak.writeFields(Channel_ID, API_Key);
    if(Data == 200)
    {
      Serial.println("Send data successfully!");
    }
    else
    {
      Serial.println("Problem sending data. HTTP error code " + String(Data));
    }
    last_time = millis();
  }
}
