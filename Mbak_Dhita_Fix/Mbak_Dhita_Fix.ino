#define BLYNK_USE_DIRECT_CONNECT

#include <Wire.h>
#include <SoftwareSerial.h>
#include <BlynkSimpleSerialBLE.h>
#include <TinyGPS++.h>

// Blynk Auth
char auth[] = "nCJYlOANFgjFzFCHyYU7MzEfGJ-3vm1f";

// GPS
#define TXPin 6
#define RXPin 3
#define GPS_UPDATE_INTERVAL 1000

// Blutut
#define BLUETOOTH_TX_PIN 10
#define BLUETOOTH_RX_PIN 11

// Motor
#define MOTOR_A_EN_PIN 5
#define MOTOR_B_EN_PIN 9
#define MOTOR_A_IN_1_PIN 7
#define MOTOR_A_IN_2_PIN 8
#define MOTOR_B_IN_1_PIN 12
#define MOTOR_B_IN_2_PIN 4

struct GeoLoc {
  float lat;
  float lon;
};

// GPS
TinyGPSPlus gps;

bool forward = false;
bool right = false;
bool left = false;

WidgetTerminal terminal(V3);

BlynkTimer timer;

// Serial components
SoftwareSerial bluetoothSerial(BLUETOOTH_TX_PIN, BLUETOOTH_RX_PIN);
SoftwareSerial ss(TXPin, RXPin);

void mauKemanaHayoo() {
  if ((forward == true) && (right == false) && (left == false)) {
    digitalWrite(MOTOR_A_IN_1_PIN, LOW);
    digitalWrite(MOTOR_A_IN_2_PIN, HIGH);
    analogWrite(MOTOR_A_EN_PIN, 180);
    
    digitalWrite(MOTOR_B_IN_1_PIN, LOW);
    digitalWrite(MOTOR_B_IN_2_PIN, HIGH);
    analogWrite(MOTOR_B_EN_PIN, 180);
  }

  if ((forward == false) && (right == true) && (left == false)) {
    digitalWrite(MOTOR_A_IN_1_PIN, LOW);
    digitalWrite(MOTOR_A_IN_2_PIN, HIGH);
    analogWrite(MOTOR_A_EN_PIN, 160);
    
    digitalWrite(MOTOR_B_IN_1_PIN, HIGH);
    digitalWrite(MOTOR_B_IN_2_PIN, LOW);
    analogWrite(MOTOR_B_EN_PIN, 160);
  }

  if ((forward == false) && (right == false) && (left == true)) {
    digitalWrite(MOTOR_A_IN_1_PIN, HIGH);
    digitalWrite(MOTOR_A_IN_2_PIN, LOW);
    analogWrite(MOTOR_A_EN_PIN, 160);
    
    digitalWrite(MOTOR_B_IN_1_PIN, LOW);
    digitalWrite(MOTOR_B_IN_2_PIN, HIGH);
    analogWrite(MOTOR_B_EN_PIN, 160);
  }

  if ((forward == false) && (right == false) && (left == false)) {
    digitalWrite(MOTOR_A_IN_1_PIN, LOW);
    digitalWrite(MOTOR_A_IN_2_PIN, LOW);
    
    digitalWrite(MOTOR_B_IN_1_PIN, LOW);
    digitalWrite(MOTOR_B_IN_2_PIN, LOW);
  }
}

// Struktur GPS nya robot
GeoLoc checkGPS() {
  bool newdata = false;
  unsigned long start = millis();
  while (millis() - start < 1000) {
    if (feedgps())
      newdata = true;
  }
  if (newdata) {
    return gpsdump();
  }

  GeoLoc coolerLoc;
  coolerLoc.lat = 0.0;
  coolerLoc.lon = 0.0;

  return coolerLoc;
}

GeoLoc gpsdump() {
  terminal.println("Reading onboard GPS: ");
  terminal.print("Latitude robot= ");
  terminal.println(gps.location.lat(), 6);
  terminal.print(" Longitude robot= ");
  terminal.println(gps.location.lng(), 6);
  terminal.println(" ");
  terminal.flush();

  GeoLoc coolerLoc;
  coolerLoc.lat = gps.location.lat();
  coolerLoc.lon = gps.location.lng();

  return coolerLoc;
}

bool feedgps() {
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated())
      return true;
  }
  return false;
}

BLYNK_WRITE(V2) {
  //mauKemanaHayoo();
  GpsParam gps(param);

  terminal.println("Received remote GPS: ");
  terminal.print("Latitude hp= ");
  terminal.println(gps.getLat(), 7);
  terminal.print(" Longitude hp= ");
  terminal.println(gps.getLon(), 7);
  terminal.println(" ");
  terminal.flush();
    ss.listen();
  GeoLoc coolerLoc = checkGPS();
  bluetoothSerial.listen();
}

BLYNK_WRITE(V4) {
  forward = !forward;
  
  terminal.print(" forward= ");
  terminal.println(forward);
  terminal.println(" ");
  terminal.flush();
}

BLYNK_WRITE(V5) {
  right = !right;
  
  terminal.print(" right= ");
  terminal.println(right);
  terminal.println(" ");
  terminal.flush();
}

BLYNK_WRITE(V6) {
  left = !left;

  terminal.print(" left= ");
  terminal.println(left);
  terminal.println(" ");
  terminal.flush();
}

//void myTimerEvent() {
//  mauKemanaHayoo();
//  
//}

void setup() {
  // Pin Motor
  pinMode(MOTOR_A_EN_PIN, OUTPUT);
  pinMode(MOTOR_B_EN_PIN, OUTPUT);
  pinMode(MOTOR_A_IN_1_PIN, OUTPUT);
  pinMode(MOTOR_A_IN_2_PIN, OUTPUT);
  pinMode(MOTOR_B_IN_1_PIN, OUTPUT);
  pinMode(MOTOR_B_IN_2_PIN, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  //Debugging via serial
  Serial.begin(9600);

  //GPS
  ss.begin(9600);

  //Bluetooth
  bluetoothSerial.begin(9600);
  Blynk.begin(bluetoothSerial, auth);
  //timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  Blynk.run();
  //timer.run();
}
