#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <PZEM004Tv30.h>
#include <LiquidCrystal_I2C.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
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
