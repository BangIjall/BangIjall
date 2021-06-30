#include<SoftwareSerial.h>
SoftwareSerial sim(3,2);

int led = 13;
String pesan;

void setup() {
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
  if(Serial.available()){
    sim.write(Serial.read());
  }
  while(sim.available()){
    pesan = sim.readStringUntil('\n');
    //pesan = sim.read();
    Serial.println(pesan);
    if(pesan=="On\r"){
      digitalWrite(led,HIGH);
      eksekusi(1);
      Serial.println("LED nyala");
    }
    if(pesan=="Off\r"){
      digitalWrite(led,LOW);
      eksekusi(0);
      Serial.println("LED mati");
    }
  }

}

void eksekusi(bool tipe){
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"082124256955\"\r");
  delay(1000);
  if(tipe==1){
    sim.println("LED Nyala");
  }else{
    sim.println("LED Mati");
  }
  delay(100);
  sim.println((char)26);
  delay(1000);
}
