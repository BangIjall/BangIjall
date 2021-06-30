#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <PZEM004Tv30.h>
#include <LiquidCrystal_I2C.h>
#define SSID "HMAS2"
#define PASS "nurmasari"
#define URL "https://mondayku.site/api/pantau"

const int pzem2 = D5;
const int pzem1 = D6;
const int buzz = D3;

HTTPClient http;
PZEM004Tv30 pzem(pzem1, pzem2);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float harga = 1444;
float VAmax = 450;
int detik = 5;
float voltage;
float current;
float power;
float energy;
float frequency;
float pf;
float dana;
float biaya = 0;
float regane;

void setup()
{
  pinMode(buzz, OUTPUT);
  digitalWrite(buzz, LOW);
  Serial.begin(115200);
  lcd.begin();
  lcd.backlight();
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
  lcd.clear();
  listrik();
  post();
  if (power >= VAmax) {
    while (1) {
      njeglek();
      listrik();
      if (power < VAmax) goto A;
    }
  }
A:
  delay((1000 * detik));
}

void listrik() {
  voltage = pzem.voltage();
  if ( !isnan(voltage) ) {
    Serial.print("Voltage: "); Serial.print(voltage); Serial.println("V");
  } else {
    Serial.println("Error reading voltage");
  }

  current = pzem.current();
  if ( !isnan(current) ) {
    Serial.print("Current: "); Serial.print(current); Serial.println("A");
  } else {
    Serial.println("Error reading current");
  }

  power = pzem.power();
  if ( !isnan(power) ) {
    Serial.print("Power: ");
    Serial.print(power); 
    Serial.println("W");
    lcd.setCursor(0, 0);
    lcd.print("P: ");
    lcd.setCursor(3, 0);
    lcd.print(power);
    lcd.setCursor(10, 0);
    lcd.print("Watt");
  } else {
    Serial.println("Error reading power");
    lcd.setCursor(0, 0);
    lcd.print("eror");
  }

  energy = pzem.energy();
  if ( !isnan(energy) ) {
    Serial.print("Energy: "); Serial.print(energy, 3); Serial.println("kWh");
  } else {
    Serial.println("Error reading energy");
  }

  frequency = pzem.frequency();
  if ( !isnan(frequency) ) {
    Serial.print("Frequency: "); Serial.print(frequency, 1); Serial.println("Hz");
  } else {
    Serial.println("Error reading frequency");
  }

  pf = pzem.pf();
  if ( !isnan(pf) ) {
    Serial.print("PF: "); Serial.println(pf);
  } else {
    Serial.println("Error reading power factor");
  }

  if ( !isnan(power) ) {
    dana = (energy * (harga / (3600 / detik)));
    regane = biaya + dana;
    Serial.print("biaya: Rp."); Serial.println(biaya);
    lcd.setCursor(0, 1);
    lcd.print("Biaya: Rp.");
    lcd.setCursor(10, 1);
    lcd.print(biaya);
  } else {
    Serial.println("Error reading biaya");
    lcd.setCursor(0, 1);
    lcd.print("eror");
  }
  biaya = regane;

  Serial.println();
}

void post() {
  //POST Data API to Database
  http.begin(String(URL));
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int response = http.POST("tegangan=" + (String)voltage + "&arus=" + current + "&daya=" + (String)energy + "&biaya=" + (String)biaya);

  Serial.println("Code Response : " + (String)response);
  http.end();
  //End http request
}

void njeglek() {
  digitalWrite(buzz, HIGH);
  delay(500);
  digitalWrite(buzz, LOW);
  delay(500);
}
