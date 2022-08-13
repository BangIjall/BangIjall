#include <TinyGPS.h> 
#include <SoftwareSerial.h> 
 
TinyGPS gps; 
SoftwareSerial gpsSerial(3, 4); 
SoftwareSerial data(11, 12); 
 
int pinGetar = 2; 
int pinBuzzer = 8; 
 
float lat = 28.5458, lon = 77.1703; 
 
 
const int sampleSize = 10; 
const int xInput = A0; 
const int yInput = A1; 
const int zInput = A2; 
 
int RawMin = 0; 
int RawMax = 1023; 
 
int manitude; 
float gempa; 
 
int kirim; 
 
void setup() 
{ 
//  analogReference(EXTERNAL); 
  Serial.begin(115200); 
  gpsSerial.begin(9600); 
  data.begin(4800); 
 
  pinMode(pinGetar, INPUT_PULLUP); 
  pinMode(pinBuzzer, OUTPUT); 
  digitalWrite(pinBuzzer, LOW); 
} 
 
void loop() 
{ 
  bacaGetaran(); 
  lokasi(); 
  if ((digitalRead(pinGetar)) == LOW) { 
    digitalWrite(pinBuzzer, HIGH); 
    kirim = 1; 
    delay(3000); 
  } 
 
  else { 
    kirim = 0; 
  } 
  digitalWrite(pinBuzzer, LOW); 
 
  Serial.print('@'); 
  data.print('@'); 
  Serial.print(','); 
  data.print(','); 
  Serial.print(lat, 6); 
  data.print(lat, 6); 
  Serial.print(','); 
  data.print(','); 
  Serial.print(lon, 6);   //show on SM1 of Fig-1 what you are sending to UNO-2 
  data.print(lon, 6);   //send ASCII coded string to UNO-2 via data Port; goes 1 char at a time 
  Serial.print(','); 
  data.print(','); 
  Serial.print(manitude);   //show on SM1 of Fig-1 what you are sending to UNO-2 
  data.print(manitude); 
  Serial.print(','); 
  data.print(','); 
  Serial.print(kirim);   //show on SM1 of Fig-1 what you are sending to UNO-2 
  data.print(kirim); 
  Serial.print(','); 
  data.print(','); 
  Serial.print('#'); 
  data.print('#'); 
  Serial.println(" "); 
  data.print(" "); 
  delay(1000); 
} 
 
// Take samples and return the average 
int ReadAxis(int axisPin) 
{ 
  long reading = 0; 
  analogRead(axisPin); 
  delay(1); 
  for (int i = 0; i < sampleSize; i++) 
  { 
    reading += analogRead(axisPin); 
  } 
  return reading / sampleSize; 
} 
 
void bacaGetaran() { 
  //Read raw values 
  int xRaw = ReadAxis(xInput); 
  int yRaw = ReadAxis(yInput); 
  int zRaw = ReadAxis(zInput); 
 
  // Convert raw values to 'milli-Gs" 
  long xScaled = map(xRaw, RawMin, RawMax, -3000, 3000); 
  long yScaled = map(yRaw, RawMin, RawMax, -3000, 3000); 
  long zScaled = map(zRaw, RawMin, RawMax, -3000, 3000); 
 
  // re-scale to fractional Gs 
  float xAccel = xScaled / 1000.0; 
  float yAccel = yScaled / 1000.0; 
  float zAccel = zScaled / 1000.0; 
 
  gempa = sqrt((yAccel * yAccel) + (xAccel * xAccel)); 
 
  if (gempa < 0.017)                  manitude = 1; 
  if (gempa == 0.017)                 manitude = 2; 
  if (gempa > 0.017 && gempa < 0.14)  manitude = 3; 
  if (gempa >= 0.14 && gempa < 0.39)  manitude = 4; 
  if (gempa >= 0.39 && gempa < 0.92)  manitude = 5; 
  if (gempa >= 0.92 && gempa < 1.8)   manitude = 6; 
  if (gempa >= 1.8 && gempa < 3.4)    manitude = 7; 
  if (gempa >= 3.4 && gempa < 6.5)    manitude = 8; 
  if (gempa >= 6.5 && gempa < 12.4)   manitude = 9; 
  if (gempa >= 12.4)                  manitude = 10; 
 
//  Serial.print("X, Y, Z  :: "); 
//  Serial.print(xRaw); 
//  Serial.print(", "); 
//  Serial.print(yRaw); 
//  Serial.print(", "); 
//  Serial.print(zRaw); 
//  Serial.print(" :: "); 
//  Serial.print(xAccel, 0); 
//  Serial.print("G, "); 
//  Serial.print(yAccel, 0); 
//  Serial.print("G, "); 
//  Serial.print(zAccel, 0); 
//  Serial.println("G"); 
//  Serial.print(gempa, 2); 
//  Serial.println("Sr"); 
} 
 
void lokasi() { 
  while (gpsSerial.available()) { // check for gps data 
    if (gps.encode(gpsSerial.read())) // encode gps data 
    { 
      gps.f_get_position(&lat, &lon); // get latitude and longitude 
      // display position 
      //      Serial.print("Position: "); 
      //      Serial.print("Latitude:"); 
      //      Serial.print(lat, 6); 
      //      Serial.print(";"); 
      //      Serial.print("Longitude:"); 
      //      Serial.println(lon, 6); 
    } 
  } 
}
