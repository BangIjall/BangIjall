#include "CTBot.h" 
#include <SoftwareSerial.h> 
 
CTBot myBot; 
SoftwareSerial SUART(D4, D3); 
 
String ssid  = "Al -Firdaus"    ; // REPLACE mySSID WITH YOUR WIFI SSID 
String pass  = "12345678"; // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY 
String token = "5339972180:AAHuxt8ID7Rm0gbFmQP5-4bBgzMllA6lrGM"   ; // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN 
 
String latitude, longitude, getaran; 
int index1, index2, index3, index4, index5, index6, index7; 
int kirim; 
 
void setup() { 
  // initialize the Serial 
  Serial.begin(115200); 
  SUART.begin(4800); 
  Serial.println("Starting TelegramBot..."); 
 
  myBot.wifiConnect(ssid, pass); 
 
  myBot.setTelegramToken(token); 
 
  if (myBot.testConnection()) 
    Serial.println("\ntestConnection OK"); 
  else 
    Serial.println("\ntestConnection NOK"); 
} 
 
void loop() { 
  while (SUART.available()) //a charctaer has arrived; it has been auto saved in FIFO; say 1 as 0x31 
  { 
    String x = SUART.readString(); //read arrived character from FIFO (say 1) and put into x as 0x31 
    Serial.println(x);  //send 0x31 to Serial Monitor to show 1 via UART Port 
    if (x.length() > 0) { 
 
      //           int  sinyal   = LoRa.packetRssi(); 
      //           String kuat = String(sinyal); 
 
      index1 = x.indexOf('@'); 
      index2 = x.indexOf(',', index1 + 1); 
      index3 = x.indexOf(',', index2 + 1); 
      index4 = x.indexOf(',', index3 + 1); 
      index5 = x.indexOf(',', index4 + 1); 
      index6 = x.indexOf(',', index5 + 1); 
      index7 = x.indexOf('#', index6 + 1); 
 
      latitude  = x.substring(index2 + 1, index3); 
      longitude = x.substring(index3 + 1, index4); 
      getaran   = x.substring(index4 + 1, index5); 
      kirim     = x.substring(index5 + 1, index6).toInt(); 
 
      Serial.print("latitude = "); 
      Serial.println(latitude); 
      Serial.print("longitude = "); 
      Serial.println(longitude); 
      Serial.print("getaran = "); 
      Serial.println(getaran); 
      Serial.print("kirim = "); 
      Serial.println(kirim); 
 
      if (kirim == 1) { 
        TBMessage msg; 
 
        msg.sender.id = 1198952505; 
        msg.text = "ada getaran, lokasi = " + String(latitude) + " : " + String(longitude) + " kekuatan getaran = " + String(getaran) + "Sr" ; 
 
        myBot.sendMessage(msg.sender.id, msg.text); 
      } 
      delay(500); 
    } 
  } 
}
