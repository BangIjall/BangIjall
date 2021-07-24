#define BLYNK_USE_DIRECT_CONNECT

// Imports
#include <Wire.h>
#include <QMC5883LCompass.h>
#include <SoftwareSerial.h>
#include <BlynkSimpleSerialBLE.h>
#include <TinyGPS++.h>
#include "Definition.h"

// GPS
TinyGPSPlus gps;

// Master Enable
bool enabled = false;

WidgetTerminal terminal(V3);

// Serial components
SoftwareSerial bluetoothSerial(BLUETOOTH_TX_PIN, BLUETOOTH_RX_PIN);
SoftwareSerial ss(TXPin, RXPin);

//#define BLYNK_PRINT Serial

/* Compass */
QMC5883LCompass compass;

GeoLoc checkGPS() {
  bool newdata = false;
  unsigned long start = millis();
  while (millis() - start < GPS_UPDATE_INTERVAL) {
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

// Get and process GPS data
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

// Feed data as it becomes available
bool feedgps() {
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated())
      return true;
  }
  return false;
}

// Killswitch Hook
BLYNK_WRITE(V1) {
  enabled = !enabled;

  //Stop the wheels
  stop();
  
  terminal.print(" Enable= ");
  terminal.println(enabled);
  terminal.println(" ");
  terminal.flush();
}

// GPS Streaming Hook
BLYNK_WRITE(V2) {
  GpsParam gps(param);

  terminal.println("Received remote GPS: ");
  terminal.print("Latitude hp= ");
  terminal.println(gps.getLat(), 7);
  terminal.print(" Longitude hp= ");
  terminal.println(gps.getLon(), 7);
  terminal.println(" ");
  terminal.flush();
  
  GeoLoc phoneLoc;
  phoneLoc.lat = gps.getLat();
  phoneLoc.lon = gps.getLon();

  driveTo(phoneLoc, GPS_STREAM_TIMEOUT);
}

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

float geoBearing(struct GeoLoc &a, struct GeoLoc &b) {
  float y = sin(b.lon - a.lon) * cos(b.lat);
  float x = cos(a.lat) * sin(b.lat) - sin(a.lat) * cos(b.lat) * cos(b.lon - a.lon);
  return atan2(y, x) * RADTODEG;
}

float geoDistance(struct GeoLoc &a, struct GeoLoc &b) {
  const float R = 6371000; // km
  float p1 = a.lat * DEGTORAD;
  float p2 = b.lat * DEGTORAD;
  float dp = (b.lat - a.lat) * DEGTORAD;
  float dl = (b.lon - a.lon) * DEGTORAD;

  float x = sin(dp / 2) * sin(dp / 2) + cos(p1) * cos(p2) * sin(dl / 2) * sin(dl / 2);
  float y = 2 * atan2(sqrt(x), sqrt(1 - x));

  return R * y;
}

float geoHeading() {
  int x, y, z;

  // Read compass values
  compass.read();

  // Return XYZ readings
  x = compass.getX();
  y = compass.getY();
  z = compass.getZ();

  float heading = atan2(y, x);

  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  float declinationAngle = 0.22;
  heading += declinationAngle;

  // Correct for when signs are reversed.
  if (heading < 0)
    heading += 2 * PI;

  // Check for wrap due to addition of declination.
  if (heading > 2 * PI)
    heading -= 2 * PI;

  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180 / M_PI;

  // Map to -180 - 180
  while (headingDegrees < -180) headingDegrees += 360;
  while (headingDegrees >  180) headingDegrees -= 360;

  return headingDegrees;
}

void setSpeedMotorA(int speed) {
  digitalWrite(MOTOR_A_IN_1_PIN, LOW);
  digitalWrite(MOTOR_A_IN_2_PIN, HIGH);

  // set speed to 200 out of possible range 0~255
  analogWrite(MOTOR_A_EN_PIN, speed + MOTOR_A_OFFSET);
}

void setSpeedMotorB(int speed) {
  digitalWrite(MOTOR_B_IN_1_PIN, LOW);
  digitalWrite(MOTOR_B_IN_2_PIN, HIGH);

  // set speed to 200 out of possible range 0~255
  analogWrite(MOTOR_B_EN_PIN, speed + MOTOR_B_OFFSET);
}

void setSpeed(int speed)
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  setSpeedMotorA(speed);

  // turn on motor B
  setSpeedMotorB(speed);
}

void stop() {
  // now turn off motors
  digitalWrite(MOTOR_A_IN_1_PIN, LOW);
  digitalWrite(MOTOR_A_IN_2_PIN, LOW);
  digitalWrite(MOTOR_B_IN_1_PIN, LOW);
  digitalWrite(MOTOR_B_IN_2_PIN, LOW);
}

void drive(int distance, float turn) {
  int fullSpeed = 230;
  int stopSpeed = 0;

  // drive to location
  int s = fullSpeed;
  if ( distance < 8 ) {
    int wouldBeSpeed = s - stopSpeed;
    wouldBeSpeed *= distance / 8.0f;
    s = stopSpeed + wouldBeSpeed;
  }

  int autoThrottle = constrain(s, stopSpeed, fullSpeed);
  autoThrottle = 230;

  float t = turn;
  while (t < -180) t += 360;
  while (t >  180) t -= 360;

  terminal.print("turn: ");
  terminal.println(t);
  terminal.print("original: ");
  terminal.println(turn);

  float t_modifier = (180.0 - abs(t)) / 180.0;
  float autoSteerA = 1;
  float autoSteerB = 1;

  if (t < 0) {
    autoSteerB = t_modifier;
  } else if (t > 0) {
    autoSteerA = t_modifier;
  }

  terminal.print("steerA: "); terminal.println(autoSteerA);
  terminal.print("steerB: "); terminal.println(autoSteerB);

  int speedA = (int) (((float) autoThrottle) * autoSteerA);
  int speedB = (int) (((float) autoThrottle) * autoSteerB);

  terminal.print("speedA: "); terminal.println(speedA);
  terminal.print("speedB: "); terminal.println(speedB);

  setSpeedMotorA(speedA);
  setSpeedMotorB(speedB);
  
  terminal.println(" ");
  terminal.flush();
}

void driveTo(struct GeoLoc &loc, int timeout) {
  ss.listen();
  GeoLoc coolerLoc = checkGPS();
  bluetoothSerial.listen();

  if (coolerLoc.lat != 0 && coolerLoc.lon != 0 && enabled) {
    float d = 0;
    //Start move loop here
    do {
      ss.listen();
      coolerLoc = checkGPS();
      bluetoothSerial.listen();

      d = geoDistance(coolerLoc, loc);
      float t = geoBearing(coolerLoc, loc) - geoHeading();

      terminal.print("Distance: ");
      terminal.println(geoDistance(coolerLoc, loc));

      terminal.print("Bearing: ");
      terminal.println(geoBearing(coolerLoc, loc));

      terminal.print("heading: ");
      terminal.println(geoHeading());
      terminal.println(" ");
      terminal.flush();

      drive(d, t);
      timeout -= 1;
    } while (d > 3.0 && enabled && timeout > 0);

    stop();
  }
}

void setup()
{
  // Compass
  compass.init();

  // Motor pins
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
}

// Testing
void testDriveNorth() {
  float heading = geoHeading();
  int testDist = 10;
  Serial.println(heading);

  while (!(heading < 5 && heading > -5)) {
    drive(testDist, heading);
    heading = geoHeading();
    Serial.println(heading);
    delay(500);
  }

  stop();
}

void loop()
{
  Blynk.run();
}
