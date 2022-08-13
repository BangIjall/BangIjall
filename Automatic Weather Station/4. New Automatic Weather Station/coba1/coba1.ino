//#include <SoftwareSerial.h>
//
//SoftwareSerial mySerial(11, 12);
//
//void setup() {
//  // put your setup code here, to run once:
//  mySerial.begin(9600);
//  Serial.begin(9600);
//
//}
//
//void loop() {
//  Serial.println(cek());
//  if (cek() == true) {
//    kirim();
//    Serial.println("sudah kirim");
//  }
//  delay(500);
//}
//
//void kirim() {
//  String dataKirim = String(17) + "#" + String(1) + "#" + String(100) + "#" + String(29) + "#" + String(16);
//  Serial.println(dataKirim);
//  mySerial.println(dataKirim);
//}
//
//bool cek() {
//  String minta = "";
//  while (mySerial.available()) {
//    minta += char(mySerial.read());
//  }
//  Serial.println(minta);
//  Serial.println("terima");
//  minta.trim();
//
//  if (minta == "ya") {
//    Serial.println("betul");
//    return true;
//  }
//
//  else {
//    Serial.println("salah");
//    return false;
//  }
//}

#include <ArduinoJson.h>
#include <SoftwareSerial.h>

// Declare the "link" serial port
// Please see SoftwareSerial library for detail
SoftwareSerial linkSerial(11, 12); // RX, TX

void setup() {
  // Initialize "debug" serial port
  // The data rate must be much higher than the "link" serial port
  Serial.begin(115200);
  while (!Serial) continue;

  // Initialize the "link" serial port
  // Use the lowest possible data rate to reduce error ratio
  linkSerial.begin(4800);
}
 
void loop() {
  // Values we want to transmit
  long timestamp = millis();
  int value = analogRead(1);

  // Print the values on the "debug" serial port
  Serial.print("timestamp = ");
  Serial.println(timestamp);
  Serial.print("value = ");
  Serial.println(value);
  Serial.println("---");

  // Create the JSON document
  StaticJsonDocument<200> doc;
  doc["timestamp"] = timestamp;
  doc["value"] = value;

  // Send the JSON document over the "link" serial port
  serializeJson(doc, linkSerial);

  // Wait
  delay(5000);
}
