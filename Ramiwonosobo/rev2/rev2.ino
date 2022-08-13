//...................................Pins.....................................//
// TTGO T-Call pins
#define MODEM_RST            5
#define MODEM_PWKEY          4
#define MODEM_POWER_ON       23
#define MODEM_TX             27
#define MODEM_RX             26
#define I2C_SDA              21
#define I2C_SCL              22
#define RELAY                33
#define RELAY2               14
#define TEGANGAN1            34
#define TEGANGAN2            35
#define TEGANGAN3            32
// sensor I2C pins
#define I2C_SDA_2            18
#define I2C_SCL_2            19

#define SerialMon            Serial
#define SerialAT             Serial1

//................................Web & GPRS...................................//
//const char apn[]      = "Telkomsel GPRS";
//const char gprsUser[] = "WAP";
//const char gprsPass[] = "WAP123";

const char apn[]      = "Indosatgprs";
const char gprsUser[] = "indosat";
const char gprsPass[] = "indosat";

const char simPIN[]   = "";

// Server details
const char server[] = "indigief.com";
const char resource[] = "/post-data.php";
const char resource2[] = "/get-data.php?api_key=tPmAT5Ab3j7F9";
const int  port = 80;
String apiKeyValue = "tPmAT5Ab3j7F9";

//............................PZEM004T & TEGANGAN DC...........................//
//#include <SoftwareSerial.h>
//
//#define PZEM_DEFAULT_ADDR     0xF8
//#define UPDATE_TIME           200
//#define READ_TIMEOUT          100
//#define CMD_RIR               0X04
//
//SoftwareSerial pzem(32, 33);

float teganganPanel;
float teganganSCC;
float teganganBeban;
//float arusBeban;
//float voltage();
//float current();
//uint8_t _addr;
//struct {
//  float voltage;
//  float current;
//  float power;
//  float energy;
//  float frequeny;
//  float pf;
//  uint16_t alarms;
//}  _currentValues;
//uint64_t _lastRead;
//void init(uint8_t addr);
//bool updateValues();
//uint16_t recieve(uint8_t *resp, uint16_t len);
//bool sendCmd8(uint8_t cmd, uint16_t rAddr, uint16_t val, bool check = false, uint16_t slave_addr = 0xFFFF);
//void setCRC(uint8_t *buf, uint16_t len);
//bool checkCRC(const uint8_t *buf, uint16_t len);
//uint16_t CRC16(const uint8_t *data, uint16_t len);
//uint8_t addr = PZEM_DEFAULT_ADDR;

//.....................................SIM800l................................//
#define TINY_GSM_MODEM_SIM800
#define TINY_GSM_RX_BUFFER   1024

#include <Wire.h>
#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>

#define IP5306_ADDR          0x75
#define IP5306_REG_SYS_CTL0  0x00

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

TinyGsmClient client(modem);
HttpClient    http(client, server, port);

//.....................................BH1750.................................//
#include "BH1750.h"

BH1750 bh1750;

float light_level;

//......................................INA219................................//
#include <Adafruit_INA219.h>

TwoWire I2CPower = TwoWire(0);
TwoWire I2CSensor = TwoWire(1);
//TwoWire I2CCahaya = TwoWire(2);

Adafruit_INA219 ina219_a;
Adafruit_INA219 ina219_b;

float arusSolar;
float arusCadangan;

#define uS_TO_S_FACTOR 1000000UL
#define TIME_TO_SLEEP  200
#define waktu          10000
#define treshold       1000
unsigned long lastTime;

#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads(0X48);
float ads_bit_Voltage;
float   ADC_16BIT_MAX = 65365.00;
//float adc0, adc1, adc2, adc3;

//.....................................LCD I2C.................................//
//#include <LCD_TTGO.h>
//
//LCD_TTGO lcd(0x27, 20, 4);

bool setPowerBoostKeepOn(int en) {
  I2CPower.beginTransmission(IP5306_ADDR);
  I2CPower.write(IP5306_REG_SYS_CTL0);
  if (en) {
    I2CPower.write(0x37);
  } else {
    I2CPower.write(0x35);
  }
  return I2CPower.endTransmission() == 0;
}

void setup() {
  SerialMon.begin(115200);

  lastTime = millis();

  // Start I2C
  I2CPower.begin(I2C_SDA, I2C_SCL, 400000);
  I2CSensor.begin(I2C_SDA_2, I2C_SCL_2, 400000);
  //  I2CCahaya.begin(I2C_SDA_3, I2C_SCL_3, 400000);
  //  lcd.begin(0, 1);
  //  lcd.backlight();
  //  lcd.print("    Tugas Akhir");

  // aktivasi power
  bool isOk = setPowerBoostKeepOn(1);
  SerialMon.println(String("IP5306 KeepOn ") + (isOk ? "OK" : "FAIL"));

  // Set pin
  pinMode(RELAY, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);
  digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);
  digitalWrite(MODEM_POWER_ON, HIGH);
  digitalWrite(RELAY, HIGH);
  digitalWrite(RELAY2, HIGH);

  // Set GSM module komunikasi
  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);
  SerialMon.println("Initializing modem...");
  modem.restart();
  // use modem.init()

  if (strlen(simPIN) && modem.getSimStatus() != 3 ) {
    modem.simUnlock(simPIN);
  }
  //
  //  // set pzem004t
  ////  pzem.begin(9600);
  ////  init(addr);
  //
  //  // set bh1750
  bh1750.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23, &I2CPower);

  ads.setGain(GAIN_TWOTHIRDS);
  ads.begin();
  float ads_InputRange = 6.144f;
  ads_bit_Voltage = (ads_InputRange * 2) / (ADC_16BIT_MAX - 1);
  //  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
}

void loop() {
  adc0 = ads.readADC_SingleEnded(0) * ads_bit_Voltage;
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);
  SerialMon.print("AIN0: "); Serial.println(adc0);
  SerialMon.print("AIN1: "); Serial.println(adc1);
  SerialMon.print("AIN2: "); Serial.println(adc2);
  SerialMon.print("AIN3: "); Serial.println(adc3);
  SerialMon.println(" ");
  SerialMon.print("Connecting to APN: ");
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    SerialMon.println(" fail");
  }
  else {
    SerialMon.println(" OK");

    SerialMon.print("Connecting to ");
    SerialMon.print(server);
    if (!client.connect(server, port)) {
      SerialMon.println(" fail");
    }
    else {
      SerialMon.println(" OK");

      //ambil data sensor
      // arus dc
      if (! ina219_a.begin(&I2CSensor)) {
        Serial.println("Failed to find arus solar chip");
        while (1) {
          delay(10);
        }
      }
      arusSolar = ina219_a.getCurrent_mA();
      delay(2000);

      if (! ina219_b.begin(&I2CPower)) {
        Serial.println("Failed to find arus cadangan chip");
        while (1) {
          delay(10);
        }
      }
      arusCadangan = ina219_b.getCurrent_mA();
      //      arusCadangan = 0;
      //      arusSolar = 0;

      //tegangan dc
      teganganPanel = (analogRead(TEGANGAN1)) * (63.89361702127658 / 4095.00);
      teganganSCC = (analogRead(TEGANGAN2)) * (63.89361702127658 / 4095.00);
      teganganBeban = ads.readADC_SingleEnded(0) * ads_bit_Voltage;

      //tegangan dan arus ac
      //      teganganBeban = voltage();
      //      if (isnan(teganganBeban)) {
      //        Serial.println("Failed to find tegangan beban chip");
      //        while (1) {
      //          delay(10);
      //        }
      //      }

      //      arusBeban = current();
      //      if (isnan(arusBeban)) {
      //        Serial.println("Failed to find arus beban chip");
      //        while (1) {
      //          delay(10);
      //        }
      //      }

      //lux meter
      if (bh1750.measurementReady()) {
        light_level = bh1750.readLightLevel();
      }

      //      light_level = 1000;
      if (light_level <= treshold) digitalWrite(RELAY2, LOW);
      else digitalWrite(RELAY, HIGH);

      // HTTP POST request
      SerialMon.println("Performing HTTP POST request...");
      String httpRequestData = "api_key=" + apiKeyValue + "&TEGANGANPANEL=" + String(teganganPanel)
                               + "&ARUSPANEL=" + String(arusSolar) + "&TEGANGANCADANGAN=" + String(teganganSCC)
                               + "&ARUSCADANGAN=" + String(arusCadangan) + "&TEGANGANBEBAN=" + String(teganganBeban)
                               + "&ARUSBEBAN=" + String(0) + "&CAHAYA=" + String(light_level) + "";
      SerialMon.println(httpRequestData);

      if (millis() - lastTime > waktu) {

        client.print(String("POST ") + resource + " HTTP/1.1\r\n");
        client.print(String("Host: ") + server + "\r\n");
        client.println("Connection: close");
        client.println("Content-Type: application/x-www-form-urlencoded");
        client.print("Content-Length: ");
        client.println(httpRequestData.length());
        client.println();
        client.println(httpRequestData);
        lastTime = millis();

        unsigned long timeout = millis();
        while (client.connected() && millis() - timeout < 10000L) {
          while (client.available()) {
            char c = client.read();
            SerialMon.print(c);
            timeout = millis();
          }
        }
      }
      SerialMon.println();

      client.stop();

      SerialMon.print(F("Performing HTTP GET request... "));
      int err = http.get(resource2);
      if (err != 0) {
        SerialMon.println(F("failed to connect"));
        delay(10000);
        return;
      }

      int status = http.responseStatusCode();
      SerialMon.print(F("Response status code: "));
      SerialMon.println(status);
      if (!status) {
        delay(10000);
        return;
      }

      SerialMon.println(F("Response Headers:"));
      while (http.headerAvailable()) {
        String headerName  = http.readHeaderName();
        String headerValue = http.readHeaderValue();
        SerialMon.println("    " + headerName + " : " + headerValue);
      }

      String body = http.responseBody();
      SerialMon.print("Kondisi Beban :");
      SerialMon.println(body);

      http.stop();

      if (body == "1") {
        digitalWrite(RELAY, HIGH);
        SerialMon.print("relay buka");
      }

      if (body == "0") {
        digitalWrite(RELAY, LOW);
        SerialMon.print("relay tutup");
      }

      SerialMon.println(F("Server disconnected"));
      modem.gprsDisconnect();
      SerialMon.println(F("GPRS disconnected"));
    }
  }
  //  esp_deep_sleep_start();
}
