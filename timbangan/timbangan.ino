#include "Arduino.h"
#include <HX711.h>

void calibrate();

const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;


HX711 scale;

void setup() {
  Serial.begin(9600);

  Serial.println("Loading");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN, 128);


//  uncomment fungsi di bawah untuk mencari nilai kalibrasi
//  calibrate();

//  uncomment fungsi di bawah untuk memasukkan nilai kalibrasi
  scale.set_scale();
  scale.tare();
  scale.set_scale(9.80);

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);

  Serial.println("Readings:");
}

void loop() {
  Serial.print("data 1:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| rata rata (20 data) :\t");
  Serial.println(scale.get_units(20), 1);

  scale.power_down();             
  delay(2000);
  scale.power_up();
}

void calibrate() {
  scale.set_scale();
  scale.tare();

  Serial.println("Letakkan benda yg diketahui beratnya lalu masukkan berat pada serial monitor dan tekan <Enter>");
  int userInput = -123;
  String inputString = "";
  while (userInput == -123) {
    while (Serial.available() > 0) {
      int inputChar = Serial.read();
      if (isDigit(inputChar)) {
        inputString += (char)inputChar;
      }
      if (inputChar == '\n') {
        userInput = inputString.toInt();
      }
    }
  }

  float calReading = scale.get_units(10);

  Serial.print("Setting the cal to ");
  Serial.println(calReading / userInput); //nilai kalibrasi

  scale.set_scale(calReading / userInput);
}
