//#include <SoftwareSerial.h>
//
//SoftwareSerial mySerial(32, 33);
//
//int indexx = 0;
//String arrData[7];
//
//void setup() {
//  // put your setup code here, to run once:
//  mySerial.begin(9600);
//  Serial.begin(9600);
//}
//
//void loop() {
//  terimaData();
//  delay(5000);
//}
//
//void terimaData() {
//  mySerial.println("ya");
//  Serial.println("sudah ya");
//  String data = "";
////  delay(200);
//  while (mySerial.available() > 0) {
//    data += char(mySerial.read());
//
//    Serial.println(data);
//  }
//  data.trim();
//
//  indexx = 0;
//  for (int i = 0; i <= data.length(); i++) {
//    char delimiter = '#';
//    if (data[i] != delimiter) {
//      arrData[indexx] += data[i];
//    }
//    else {
//      indexx++;
//    }
//
//    Serial.println(indexx);
//
//    if (indexx == 4) {
//      //      curah = arrData[0];
//      //      radiasi = arrData[1];
//      //      suhu = arrData[2];
//      //      kelembaban = arrData[3];
//      //      tekanan = arrData[4];
//
//      Serial.println(arrData[0]);
//      Serial.println(arrData[1]);
//      Serial.println(arrData[2]);
//      Serial.println(arrData[3]);
//      Serial.println(arrData[4]);
//      Serial.println(" ");
//    }
//  }
//}

#include <ArduinoJson.h>
#include <SoftwareSerial.h>

// Declare the "link" serial port
// Please see SoftwareSerial library for detail
SoftwareSerial linkSerial(32, 33); // RX, TX

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
  // Check if the other Arduino is transmitting
  if (linkSerial.available())
  {
    // Allocate the JSON document
    // This one must be bigger than for the sender because it must store the strings
    StaticJsonDocument<300> doc;

    // Read the JSON document from the "link" serial port
    DeserializationError err = deserializeJson(doc, linkSerial);

    if (err == DeserializationError::Ok) {
      // Print the values
      // (we must use as<T>() to resolve the ambiguity)
      Serial.print("timestamp = ");
      Serial.println(doc["timestamp"].as<long>());
      Serial.print("value = ");
      Serial.println(doc["value"].as<int>());
    }
    
    else {
      // Print error to the "debug" serial port
      Serial.print("deserializeJson() returned ");
      Serial.println(err.c_str());

      // Flush all bytes in the "link" serial port buffer
      while (linkSerial.available() > 0)
        linkSerial.read();
    }
  }
}
