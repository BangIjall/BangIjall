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
#define TEGANGAN1            34
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

Adafruit_INA219 ina219_a;
Adafruit_INA219 ina219_b;

float arusSolar;
float arusCadangan;
float arusBeban;

#define uS_TO_S_FACTOR 1000000UL
#define TIME_TO_SLEEP  200
#define waktu          30000
#define treshold       1000
unsigned long lastTime;

#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads(0X48);
float ads_bit_Voltage;
float   ADC_16BIT_MAX = 65365.00;

//............................PZEM004T & TEGANGAN DC...........................//

float teganganPanel;
float teganganSCC;
float teganganBeban;

int mVperAmp = 100;           // this the 5A version of the ACS712 -use 100 for 20A Module and 66 for 30A Module
int Watt = 0;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

float getVPP()
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

  ads.setGain(GAIN_ONE);
  ads.begin();
  float ads_InputRange = 6.144f;
  ads_bit_Voltage = (ads_InputRange * 2) / (ADC_16BIT_MAX - 1);

  //  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
}

void loop() {
  //ambil data sensor
  // arus dc
  if (! ina219_a.begin(&I2CSensor)) {
    Serial.println("Failed to find arus solar chip");
    while (1) {
      delay(10);
    }
  }
  arusBeban = ina219_a.getCurrent_mA();
  delay(2000);

  if (! ina219_b.begin(&I2CPower)) {
    Serial.println("Failed to find arus cadangan chip");
    while (1) {
      delay(10);
    }
  }
  arusCadangan = ina219_b.getCurrent_mA();
  delay(1000);

  Voltage = getVPP();
  VRMS = (Voltage / 2.0) * 0.707; //root 2 is 0.707
  arusBeban = ((VRMS * 1000) / mVperAmp) - 0.3; //0.3 is the error I got for my sensor
  SerialMon.print("Arus Beban :");
  SerialMon.println(arusBeban);

  //lux meter
  if (bh1750.measurementReady()) {
    light_level = bh1750.readLightLevel();
  }

  delay(1000);

  int16_t adc1, adc0;

  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);

  //tegangan dc
  teganganSCC   = (adc0 * 5.00 / 32767.00) * 20.36170212765957;
  teganganBeban = (adc1 * 5.00 / 32767.00) * 20.36170212765957;
  teganganPanel = (analogRead(TEGANGAN1)) * (75.00 / 4095.00);
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
      int arusbaterai = 1000;
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
                               + "&Suhu=" + float(suhu) + "&Kelembaban=" + float(kelembaban) +
                               "";
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

  //  esp_deep_sleep_start();

}
