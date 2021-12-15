#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <PZEM004Tv30.h>
#include <LiquidCrystal_I2C.h>

const int pzem2 = D5;
const int pzem1 = D6;
const int buzzer = D3;
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

PZEM004Tv30 pzem(pzem1, pzem2);
LiquidCrystal_I2C lcd(0x27, 20, 4);

char auth[] = "1XwlgdtCztXJSIeNWT7TVHfbZTL-B_R_";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "OPPO A3s";
char pass[] = "modal dikit dong";

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  //digitalWrite(D7, V6);
  listrik();
  Blynk.virtualWrite(V0, voltage);
  Blynk.virtualWrite(V1, current);
  Blynk.virtualWrite(V2, power);
  Blynk.virtualWrite(V3, frequency);
  Blynk.virtualWrite(V4, energy);
  Blynk.virtualWrite(V5, biaya);
  Serial.print(digitalRead(D7));
}

void setup()
{
  // Debug console  
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
  pinMode(D7, OUTPUT);
  pinMode(D3, OUTPUT);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}

void listrik() {
  voltage = pzem.voltage();
  if ( !isnan(voltage) ) {
    Serial.print("Voltage: "); 
    Serial.print(voltage); 
    Serial.println("V");
    lcd.setCursor(0, 0);
    lcd.print("V: ");
    lcd.setCursor(3, 0);
    lcd.print(voltage);
    lcd.setCursor(10, 0);
    lcd.print("volt");
  } else {
    voltage=0;
    Serial.println("Error reading voltage");
    lcd.setCursor(0, 0);
    lcd.print("V: ");
    lcd.setCursor(3, 0);
    lcd.print(voltage);
    lcd.setCursor(10, 0);
    lcd.print("volt");
  }

  current = pzem.current();
  if ( !isnan(current) ) {
    Serial.print("Current: "); 
    Serial.print(current); 
    Serial.println("A");    
    lcd.setCursor(0, 1);
    lcd.print("I: ");
    lcd.setCursor(3, 1);
    lcd.print(current);
    lcd.setCursor(10, 1);
    lcd.print("Ampere");
  } else {
    current = 0;
    Serial.println("Error reading current");    
    lcd.setCursor(0, 1);
    lcd.print("I: ");
    lcd.setCursor(3, 1);
    lcd.print(current);
    lcd.setCursor(10, 1);
    lcd.print("Ampere");
  }

  power = pzem.power();
  if ( !isnan(power) ) {
    Serial.print("Power: ");
    Serial.print(power); 
    Serial.println("W");
    lcd.setCursor(0, 2);
    lcd.print("P: ");
    lcd.setCursor(3, 2);
    lcd.print(power);
    lcd.setCursor(10, 2);
    lcd.print("Watt");
  } else {
    power = 0;
    Serial.println("Error reading power");
    Serial.print("Power: ");
    Serial.print(power); 
    Serial.println("W");
    lcd.setCursor(0, 2);
    lcd.print("P: ");
    lcd.setCursor(3, 2);
    lcd.print("0");
    lcd.setCursor(10, 2);
    lcd.print("Watt");
  }

  energy = pzem.energy();
  if ( !isnan(energy) ) {
    Serial.print("Energy: "); Serial.print(energy, 3); Serial.println("kWh");
  } else {
    energy = 0;
    Serial.println("Error reading energy");
  }

  frequency = pzem.frequency();
  if ( !isnan(frequency) ) {
    Serial.print("Frequency: "); Serial.print(frequency, 1); Serial.println("Hz");
  } else {
    frequency = 0;
    Serial.println("Error reading frequency");
  }

  pf = pzem.pf();
  if ( !isnan(pf) ) {
    Serial.print("PF: "); Serial.println(pf);
  } else {
    pf = 0;
    Serial.println("Error reading power factor");
  }

  if ( !isnan(power) ) {
    dana = (energy * (harga / (3600 / detik)));
    regane = biaya + dana;
    Serial.print("biaya: Rp."); Serial.println(biaya);
    lcd.setCursor(0, 3);
    lcd.print("Biaya: Rp.");
    lcd.setCursor(10, 3);
    lcd.print(biaya);
  } else {
    Serial.print("biaya: Rp."); 
    Serial.println(biaya);
    lcd.setCursor(0, 3);
    lcd.print("Biaya: Rp.");
    lcd.setCursor(10, 3);
    lcd.print(biaya);
  }
  biaya = regane;

  Serial.println();

  if (power >= VAmax) {
    digitalWrite(buzzer, HIGH);
  }

  if (power < VAmax) {
    digitalWrite(buzzer, LOW);
  }
}
