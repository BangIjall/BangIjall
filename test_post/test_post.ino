#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define RX_NODE D1
#define TX_NODE D2
#define SSID "OPPO A3s"
#define PASS "modal dikit dong"
#define URL "https://monday-13c16-default-rtdb.firebaseio.com/data.json"

SoftwareSerial ard(RX_NODE, TX_NODE);
HTTPClient http;
int no_pasien;
void setup()
{
  Serial.begin(9600);
  ard.begin(9600);
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
  float daya = 25;
  float tegangan= 220;
  float arus = 0.1;
  WiFiClientSecure client;
  client.setInsecure(); //the magic line, use with caution
  client.connect(URL, 443);
  http.begin(client, (String)URL);
  http.addHeader("content-type", "application/json");
  int response = http.POST("{\"daya\":"+(String)daya+", \"tegangan\":"+(String)tegangan+", \"arus\":"+(String)arus+"}");
  delay(5000);
}
