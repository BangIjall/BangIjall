#include <Wire.h>
#include "RTClib.h"
#include "DHT.h"
#include <SFE_BMP180.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_INA219.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define DHTPIN        2
#define pin_interrupt 3

#define DHTTYPE DHT21
DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial linkSerial(11, 12); // RX, TX

SFE_BMP180 pressure;
char status;
double P, T;

Adafruit_INA219 ina219;                      /*  Adafruit_INA219 ina219_B(0x45); tambahkan alamat dan variable jika menggunakan lebih dari 1 Modul INA219*/
float currentSampleRead   = 0;               /* Untuk tempat data mengambil sampel */
unsigned long currentLastSample   = 0;       /* Untuk tempat data pengaktifan pengambilan sampel */
float currentSampleSum    = 0;               /* Untuk tempat data nilai jumlah data */
float currentMean ;                          /* Untuk tempat data rata rata arus */
float konstanta = 0.159   ;                  // konstanta untuk konversi arus ke radiasi
float Irradiation = 0.00;

RTC_DS3231 rtc;
DateTime now;
String jam, menit, detik;
float curah, curahHariIni;
float tip = 0.2;

float hum, temp;

void setup() {
  Serial.begin(9600);

  //dht.begin();

  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    Serial.println("BMP180 init fail\n\n");
    while (1); // Pause forever.
  }
  //ina219.begin();

  pinMode(pin_interrupt, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin_interrupt), hitungCurah, FALLING);

  //  if (!rtc.begin()) {
  //    Serial.println("Couldn't find RTC");
  //    while (1)
  //      ;
  //  }

  linkSerial.begin(4800);

}

void loop() {
  Serial.println(curah);
  delay(2000);
}
