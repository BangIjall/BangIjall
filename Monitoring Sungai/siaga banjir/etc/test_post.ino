#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define RX_NODE D1
#define TX_NODE D2
#define SSID "Al -Firdaus"
#define PASS "12345678"
#define URL "https://tugas-akhir-3aca8-default-rtdb.firebaseio.com/data3.json"

HTTPClient http;
  float daya = 19;
  float tegangan= 220;
  float arus = 0.1;
void setup()
{
  Serial.begin(9600);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nSTARTED");
}

void loop()
{
  WiFiClientSecure client;
  client.setInsecure(); //the magic line, use with caution
  client.connect(URL, 443);
  http.begin(client, (String)URL);
  http.addHeader("content-type", "application/json");
  int response = http.POST("{\"daya\":"+(String)daya+"}");
  delay(5000);
}
