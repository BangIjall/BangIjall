#include <esp_now.h>
#include <WiFi.h>

//78:21:84:7C:BD:C8 40:F5:20:06:FB:24

uint8_t broadcastAddress1[] = {0x40, 0xF5, 0x20, 0x06, 0xFB, 0x24};
uint8_t broadcastAddress2[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct test_struct {
  int humA1;
  int humA2;
  int humB1;
  int humB2;
  float temp1;
  float temp2;
  float vltg;
  int titik;
} test_struct;

typedef struct status_struct {
  int kirim;
} status_struct;

test_struct myData;

status_struct pesan;

esp_now_peer_info_t peerInfo;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("humA1: ");
  Serial.println(myData.humA1);
  Serial.print("humA2: ");
  Serial.println(myData.humA2);
  Serial.print("humB1: ");
  Serial.println(myData.humB1);
  Serial.print("humB2: ");
  Serial.println(myData.humB2);
  Serial.print("temp1: ");
  Serial.println(myData.temp1);
  Serial.print("temp2: ");
  Serial.println(myData.temp2);
  Serial.print("tegangan panel: ");
  Serial.println(myData.vltg);
  Serial.print("node: ");
  Serial.println(myData.titik);
  Serial.println();
}

int sending = 1;
int sending2 = 2;

float humidityA1, humidityA2, humidityB1, humidityB2, temperature1, temperature2;

//...................................Pins.....................................//
// TTGO T-Call pins
#define MODEM_RST            5
#define MODEM_PWKEY          4
#define MODEM_POWER_ON       23
#define MODEM_TX             27
#define MODEM_RX             26
#define I2C_SDA              21
#define I2C_SCL              22
#define RELAY                32
#define RELAY2               14
#define ARUS2                34
#define ARUS1                35
//#define TEGANGAN3            33
// sensor I2C pins
#define I2C_SDA_2            18
#define I2C_SCL_2            19

#define SerialMon            Serial
#define SerialAT             Serial1
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

//................................Web & GPRS...................................//
const char apn[]      = "XL GPRS";
const char gprsUser[] = "";
const char gprsPass[] = "";

const char simPIN[]   = "";

// Server details
const char server[] = "indigief.com";
const char resource[] = "/ramirabersa/post-datav2.php";
const char resource2[] = "/get-data.php?api_key=tPmAT5Ab3j7F9";
const int  port = 80;
String apiKeyValue = "tPmAT5Ab3j7F9";

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

String body;

//.....................................BH1750.................................//
#include "BH1750.h"

BH1750 bh1750;

float light_level;

//......................................INA219................................//
#include <Adafruit_INA219.h>

TwoWire I2CPower = TwoWire(0);
TwoWire I2CSensor = TwoWire(1);
//TwoWire I2CCahaya = TwoWire(2);

//Adafruit_INA219 ina219_a;
Adafruit_INA219 ina219_b;

float arusSolar;
float arusCadangan;
float arusBeban;
float arusbaterai;

#define uS_TO_S_FACTOR 1000000UL
#define TIME_TO_SLEEP  2
#define waktu          30000
#define treshold       1000
unsigned long lastTime;

#include "ADS1X15.h"
ADS1115 ADS(0x48);

//............................PZEM004T & TEGANGAN DC...........................//

float teganganPanel;
float teganganSCC;
float teganganBeban;

int mVperAmp = 100;           // this the 5A version of the ACS712 -use 100 for 20A Module and 66 for 30A Module
int Watt = 0;
double Voltage1 = 0;
double VRMS1 = 0;
double AmpsRMS1 = 0;
double Voltage2 = 0;
double VRMS2 = 0;
double AmpsRMS2 = 0;

float getVPP1()
{
  float result;
  int readValue;                // value read from the sensor
  int maxValue = 0;             // store max value here
  int minValue = 4095;          // store min value here ESP32 ADC resolution

  uint32_t start_time = millis();
  while ((millis() - start_time) < 1000) //sample for 1 Sec
  {
    readValue = analogRead(ARUS1);
    // see if you have a new maxValue
    if (readValue > maxValue)
    {
      // record the maximum sensor value /
      maxValue = readValue;
    }
    if (readValue < minValue)
    {
      // record the minimum sensor value /
      minValue = readValue;
    }
  }

  // Subtract min from max
  result = (maxValue - minValue) * 5.00 / 4095.00; //ESP32 ADC resolution 4096

  return result;
}

float getVPP2()
{
  float result;
  int readValue;                // value read from the sensor
  int maxValue = 0;             // store max value here
  int minValue = 4095;          // store min value here ESP32 ADC resolution

  uint32_t start_time = millis();
  while ((millis() - start_time) < 1000) //sample for 1 Sec
  {
    readValue = analogRead(ARUS2);
    // see if you have a new maxValue
    if (readValue > maxValue)
    {
      // record the maximum sensor value /
      maxValue = readValue;
    }
    if (readValue < minValue)
    {
      // record the minimum sensor value /
      minValue = readValue;
    }
  }

  // Subtract min from max
  result = (maxValue - minValue) * 5.00 / 4095.00; //ESP32 ADC resolution 4096

  return result;
}

bool statusModem = true;

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

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    SerialMon.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);

  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
  
  //  LCDSetup
  //  lcd.init();
  lcd.begin();
  lcd.backlight();
  // Start I2C
  I2CPower.begin(I2C_SDA, I2C_SCL, 400000);
    I2CSensor.begin(I2C_SDA_2, I2C_SCL_2, 400000);
  //  I2CCahaya.begin(I2C_SDA_3, I2C_SCL_3, 400000);

  // aktivasi power
  bool isOk = setPowerBoostKeepOn(1);
  SerialMon.println(String("IP5306 KeepOn ") + (isOk ? "OK" : "FAIL"));

  // Set pin
  //  pinMode(TEGANGAN3, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);
  digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);
  digitalWrite(MODEM_POWER_ON, HIGH);
  digitalWrite(RELAY, HIGH);

  // Set GSM module komunikasi
  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);
  SerialMon.println("Initializing modem...");
  modem.restart();
  // use modem.init()

  if (strlen(simPIN) && modem.getSimStatus() != 3 ) {
    modem.simUnlock(simPIN);
  }

  // set bh1750
  bh1750.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23, &I2CPower);
  delay(500);
  
  while (! ina219_b.begin(&I2CPower)) {
    Serial.println("Failed to find arus cadangan chip");
      delay(10);
  }

  ADS.begin();
  ADS.setGain(0);

//    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
}

void loop() {
  //ambil data sensor
  // arus dc
  //  if (! ina219_a.begin(&I2CSensor)) {
  //    Serial.println("Failed to find arus solar chip");
  //    while (1) {
  //      delay(10);
  //    }
  //  }
  //  arusBeban = ina219_a.getCurrent_mA();
  //  delay(2000);

  
  //node 1
  pesan.kirim = sending; 
  esp_err_t result = esp_now_send(broadcastAddress1, (uint8_t *) &pesan, sizeof(pesan));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  delay(10000);

  if (myData.titik == 1) {
    humidityA1 = myData.humA1;
    humidityA2 = myData.humA2;
    humidityB1 = myData.humB1;
    humidityB2 = myData.humB2;
    temperature1 = myData.temp1;
    temperature2 = myData.temp2;
  }

  //node 2
  pesan.kirim = sending2; 
  esp_err_t result2 = esp_now_send(broadcastAddress2, (uint8_t *) &pesan, sizeof(pesan));
   
  if (result2 == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  delay(10000);

  if (myData.titik == 2) {
    teganganPanel = myData.vltg;
  }
  
  arusBeban = ina219_b.getCurrent_mA();
  delay(1000);

  Voltage2 = getVPP2();
  VRMS2 = (Voltage2 / 2.0) * 0.707; //root 2 is 0.707
  arusSolar = ((VRMS2 * 1000) / mVperAmp) - 0.3; //0.3 is the error I got for my sensor
  SerialMon.print("Arus Beban :");
  SerialMon.println(arusSolar);

  Voltage1 = getVPP1();
  VRMS1 = (Voltage1 / 2.0) * 0.707; //root 2 is 0.707
  arusbaterai = ((VRMS1 * 1000) / mVperAmp) - 0.3; //0.3 is the error I got for my sensor
  SerialMon.print("Arus Beban :");
  SerialMon.println(arusBeban);

  //lux meter
  if (bh1750.measurementReady()) {
    light_level = bh1750.readLightLevel();
  }

  delay(1000);

  int16_t adc2, adc1, adc0;
  float f = ADS.toVoltage(1);

  adc0 = ADS.readADC(0);
  adc1 = ADS.readADC(1);
  adc2 = ADS.readADC(2);

  //tegangan dc
  teganganSCC   = (adc0 * f) * 20.36170212765957;
  teganganBeban = (adc1 * f) * 20.36170212765957;
//  teganganPanel = (adc2 * f) * 20.36170212765957;
//  teganganSCC   = 1000;
//  teganganBeban = 1000;
//  teganganPanel = 1000;
  //  teganganBeban = (ads.readADC_SingleEnded(0) * ads_bit_Voltage) * 20.36170212765957;

  //      Tresshold
  if (light_level <= treshold) digitalWrite(RELAY2, LOW);
  else digitalWrite(RELAY2, HIGH);

  SerialMon.print("teganganBeban=");
  SerialMon.println(teganganBeban);
  SerialMon.print("teganganBaterai=");
  SerialMon.println(teganganSCC);
  SerialMon.print("teganganPanel=");
  SerialMon.println(teganganPanel);
  SerialMon.print("Arus=");
  SerialMon.println(arusCadangan);

  lcd.setCursor(0, 0);
  lcd.print("CP:");
  lcd.print(light_level, 1);
  lcd.print("lx   ");
  lcd.setCursor(0, 1);
  lcd.print("TP:");
  lcd.print(teganganPanel, 1);
  lcd.print("V   ");
  lcd.setCursor(0, 2);
  lcd.print("AP:");
  lcd.print(arusSolar, 1);
  lcd.print("mA   ");
  lcd.setCursor(0, 3);
  lcd.print("TB:");
  lcd.print(teganganSCC, 1);
  lcd.print("V   ");
  lcd.setCursor(11, 0);
  lcd.print("AB:");
  lcd.print(arusCadangan, 1);
  lcd.print("mA  ");
  lcd.setCursor(11, 1);
  lcd.print("TBB:");
  lcd.print(teganganBeban, 1);
  lcd.print("V");

  delay(500);

  if (!statusModem) {
    SerialMon.println("Initializing modem...");
    modem.restart();
    // use modem.init()

    if (strlen(simPIN) && modem.getSimStatus() != 3 ) {
      modem.simUnlock(simPIN);
    }
    statusModem = true;
  }

  SerialMon.print("Connecting to APN: ");
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    SerialMon.println(" fail");
    statusModem = false;
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

      int tegbaterai = 1000;
      int suhu = 30;
      int kelembaban = 40 ;
      int aruss = 900;
      // HTTP POST request
      SerialMon.println("Performing HTTP POST request...");
      String httpRequestData = "api_key=" + apiKeyValue + "&Tegangan1=" + float(teganganPanel)
                               + "&Arus1=" + float(arusSolar) +  "&Tegangan2=" + float(tegbaterai)
                               + "&Tegangan3=" + float(teganganSCC) + "&Arus2=" + float(arusCadangan)
                               + "&Arus3=" + float(arusbaterai) + "&Tegangan4=" + float(teganganBeban)
                               + "&Arus4=" + float(arusBeban) + "&IntensitasCahaya=" + float(light_level)
                               + "&Suhu1=" + float(temperature1) + "&Suhu2=" + float(temperature2) + "&Kelembaban1=" + float(humidityA1)
                               + "&Kelembaban2=" + float(humidityA2) + "&Kelembaban3=" + float(humidityB1) 
                                + "&Kelembaban4=" + float(humidityB2) + "";
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
        while (client.connected() && millis() - timeout < 30000L) {
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
      while (status != -3 && http.headerAvailable()) {
        String headerName  = http.readHeaderName();
        String headerValue = http.readHeaderValue();
        SerialMon.println("    " + headerName + " : " + headerValue);
      }

      if (status != -3) body = http.responseBody();
      SerialMon.print("Kondisi Beban :");
      SerialMon.println(body);

      http.stop();


      if (body == "1") {
        digitalWrite(RELAY, HIGH);
        SerialMon.print("relay buka");
        lcd.setCursor(11, 2);
        lcd.print("KBB=");
        lcd.print("OFF");
      }

      if (body == "0") {
        digitalWrite(RELAY, LOW);
        SerialMon.print("relay tutup");
        lcd.setCursor(11, 2);
        lcd.print("KBB=");
        lcd.print("ON");
      }

      SerialMon.println(F("Server disconnected"));
      modem.gprsDisconnect();
      SerialMon.println(F("GPRS disconnected"));
    }
  }

//    esp_deep_sleep_start();

}
