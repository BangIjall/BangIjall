//Wifi
#include <ESP8266WiFi.h>
#define WIFI_SSID "Kosan Mamah Ghea"
#define WIFI_PASSWORD "2020 Ganti Password "
//Firebase
#include <FirebaseArduino.h>
#define FIREBASE_HOST "testesp8266-e92c2-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "e2xYrGEI1EMXQLolv3Tiq6iju9NGE6UIo4tVhy1x"
//DHT11
#include "DHT.h"
#define DHTPIN D3
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
int suhu, kelembaban;

//lampu
int dataLampu;
#define relay D5

void setup() {
  Serial.begin(9600);

  //DHT11
  dht.begin();

  //Relay
  pinMode(relay, OUTPUT);

  //Konek ke WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  //Ke Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  delay(2000);

  kelembaban = dht.readHumidity();
  suhu = dht.readTemperature();
  if (isnan(kelembaban) || isnan(suhu)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print("  Kelembaban: ");
  Serial.println(kelembaban);

  Firebase.setInt("suhu", suhu);
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }

  Firebase.setInt("kelembaban", kelembaban);
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }

  dataLampu = Firebase.getInt("lampu");
  Serial.print("Lampu: ");
  Serial.println(dataLampu);
  digitalWrite(relay, dataLampu);
}
