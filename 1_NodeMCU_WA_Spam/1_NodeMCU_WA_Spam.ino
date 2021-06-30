#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

#define SSID "HYAK"
#define PASS "qwertyuiop"

SoftwareSerial data(D1, D2);
WiFiClientSecure client;
HTTPClient http;

const String host = "https://eu64.chat-api.com/instance202142/sendMessage?token=bo4iyk2x75df3wow";
const String phone = "6282136119312";

void setup()
{
  Serial.begin(115200);
  delay(10000);
  Serial.println("START");
  data.begin(115200);
  Serial.println("Connecting to WiFi..");
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected, IP : " + WiFi.localIP().toString());
}

void loop()
{
  /*
    Menerima data dari software Serial
  */
  if (data.available()>0)
  {
    String dataArduino = data.readStringUntil(13);
    String cmd;
    if(dataArduino == "a"){
      cmd = "KEBOCORAN DI TABUNG GAS";
    }
    if(dataArduino == "b"){
      cmd = "KEBOCORAN DI SOLENOID VALVE";
    }
    if(dataArduino == "c"){
      cmd = "KEBOCORAN DI KOMPOR";
    }
    String message = "{\"phone\":\"" + phone + "\",\"body\":\""+cmd+"\"}";
    Serial.println("data : "+cmd);
    /*
      Inisialisasi koneksi ke whatsapp API
    */
    client.setInsecure();
    client.connect(host, 443);
    http.begin(client, host);
    http.addHeader("Content-Type", "application/json");
    int response_code = http.POST(message);
    if (response_code == HTTP_CODE_OK)
    {
      Serial.println(http.getString());
    }
    http.end();
  }
  delay(1);
}
