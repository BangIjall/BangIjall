#include<SoftwareSerial.h>
SoftwareSerial sim(3,2);

int led = 13;
String pesan;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(led,OUTPUT);
  sim.begin(9600);
  delay(100);
  sim.println("AT");
  sim.println("AT+CMGF=1");
  sim.println("AT+CNMI=1,2,0,0,0");
}

void loop() {
  delay(2000);
sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"082124256955\"\r");
  delay(1000);
    sim.println("halo sayang");
  delay(100);
  sim.println((char)26);
  delay(1000);
}
