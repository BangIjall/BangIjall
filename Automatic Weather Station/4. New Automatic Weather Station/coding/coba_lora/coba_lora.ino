#include "send_data.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(32, 33);

float curah;
float radiasi;
float suhu;
float kelembaban;
float tekanan;

float vtotal = 100;                 //Deklarasi perhitungan desimal
float volume = 50;                   //Deklarasi nilai volume

char myStr[50];
byte outStr[255];
byte recvStatus = 0;
int port, channel, freq;
bool newmessage = false;
String arrData[7];
int index = 0;

void setup() {
  // Setup loraid access
  Serial.begin(115200);                   //meneampilakan pada serial monitor
  mySerial.begin(4800);
  loraSetup();
}

void loop() {

}

void sendLoraData() {
  if (millis() - previousMillis > interval) {
    previousMillis = millis();
    kirimData(vtotal, volume);                                //data yang dikirim dengan lora
    delay(1300);                                              //dalam 1 detik mengirim 1 data
  }
}

void terimaData() {
  mySerial.println("ya");
  String data = "";
  while (mySerial.available()) {
    data += char(mySerial.read());
  }
  data.trim();

  index = 0;
  for (int i = 0; i <= data.length(); i++) {
    char delimiter = '#';
    if (data[i] != delimiter) {
      arrData[index] += data[i];
    }
    else {
      index++;
    }

    if (index == 6) {
//      curah = arrData[0];
//      radiasi = arrData[1];
//      suhu = arrData[2];
//      kelembaban = arrData[3];
//      tekanan = arrData[4];

      Serial.println(arrData[0]);
      Serial.println(arrData[1]);
      Serial.println(arrData[2]);
      Serial.println(arrData[3]);
      Serial.println(arrData[4]);
      Serial.println(" ");
    }
  }
}
