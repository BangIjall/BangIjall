//#include <SoftwareSerial.h>

//SoftwareSerial Serial1(22, 23);

#define pompa1 13
#define pompa2 14
#define Sv1 4
#define Sv2 5
#define Sv3 6
#define Sv4 7
#define Sv5 8
#define Sv6 9
#define Sv7 10
#define Sv8 11
#define Sv9 12

bool tomat = false;
bool otomatisss = false;
bool bayam = false;
bool lavender = false;

int index1;
int index2;
int index3;
int index4;

bool tanki = false;

//pin ultrasonik
const int echoPin = 27 ;
const int trigPin = 28 ;
long duration;
int distance;
String dataIn;
String command;

// waterflow1
int sensorInterrupt1 = 2;
float flowRate1 = 0.0;
unsigned int flowMilliLitres1 = 0;
unsigned long totalMilliLitres1 = 0;

// waterflow2
int sensorInterrupt2 = 3;
float flowRate2 = 0.0;
unsigned int flowMilliLitres2 = 0;
unsigned long totalMilliLitres2 = 0;

// waterflow3
int sensorInterrupt3 = 18;
float flowRate3 = 0.0;
unsigned int flowMilliLitres3 = 0;
unsigned long totalMilliLitres3 = 0;


//default setpoin waterflow sensor
unsigned int SetPoint = 400; //400 milileter
unsigned long oldTime = 0;
unsigned long oldTime1 = 0;
unsigned long oldTime2 = 0;
float calibrationFactor = 4.5;
volatile byte pulseCount = 0;
volatile byte pulseCount1 = 0;
volatile byte pulseCount2 = 0;

int pompa_1 = HIGH;
int pompa_2 = HIGH;
int Sv_1 = HIGH;
int Sv_2 = HIGH;
int Sv_3 = HIGH;
int Sv_4 = HIGH;
int Sv_5 = HIGH;
int Sv_6 = HIGH;
int Sv_7 = HIGH;
int Sv_8 = HIGH;
int Sv_9 = HIGH;

int sm1 = A0;
int sm2 = A1;
int sm3 = A2;
int sm4 = A3;
int sm5 = A4;
int sm6 = A5;
int sm7 = A6;
int sm8 = A7;
int sm9 = A8;

int Soil1 = 0;
int Soil2 = 0;
int Soil3 = 0;
int Soil4 = 0;
int Soil5 = 0;
int Soil6 = 0;
int Soil7 = 0;
int Soil8 = 0;
int Soil9 = 0;


void setup() {
  // pin mode dan setup awal:
  Serial.begin(115200);
  Serial1.begin(4800);
  pinMode(pompa1, OUTPUT);
  pinMode(pompa2, OUTPUT);
  pinMode(Sv1, OUTPUT);
  pinMode(Sv2, OUTPUT);
  pinMode(Sv3, OUTPUT);
  pinMode(Sv4, OUTPUT);
  pinMode(Sv5, OUTPUT);
  pinMode(Sv6, OUTPUT);
  pinMode(Sv7, OUTPUT);
  pinMode(Sv8, OUTPUT);
  pinMode(Sv9, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(pompa1, HIGH);
  digitalWrite(pompa2, HIGH);
  digitalWrite(Sv1, HIGH);
  digitalWrite(Sv2, HIGH);
  digitalWrite(Sv3, HIGH);
  digitalWrite(Sv4, HIGH);
  digitalWrite(Sv5, HIGH);
  digitalWrite(Sv6, HIGH);
  digitalWrite(Sv7, HIGH);
  digitalWrite(Sv8, HIGH);
  digitalWrite(Sv9, HIGH);


  //  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(pompa2, HIGH);

  attachInterrupt(sensorInterrupt1, pulseCounter, FALLING);
  attachInterrupt(sensorInterrupt2, pulseCounter1, FALLING);
  attachInterrupt(sensorInterrupt3, pulseCounter2, FALLING);
}

void loop() {
  Soil1 = analogRead(sm1);
  Soil2 = analogRead(sm2);
  Soil3 = analogRead(sm3);
  Soil4 = analogRead(sm4);
  Soil5 = analogRead(sm5);
  Soil6 = analogRead(sm6);
  Soil7 = analogRead(sm7);
  Soil8 = analogRead(sm8);
  Soil9 = analogRead(sm9);
  waterflow1();
  waterflow2();
  waterflow3();
  Ultrasonik();

  while (Serial1.available() > 0)
  {
    dataIn = Serial1.readString();
    if (dataIn.length() > 0) {
      index1 = dataIn.indexOf('@');
      index2 = dataIn.indexOf(',', index1 + 1);
      index3 = dataIn.indexOf(',', index2 + 1);
      index4 = dataIn.indexOf('#', index3 + 1);
    }
  }

  command = dataIn.substring(index2 + 1, index3);
  Serial.println(command);

  if (command == "11") {
    Serial.println("otomatisss");
    tomat = true;
    bayam = true;
    lavender = true;
  }
  if (command == "22") {
    tomat = ! tomat;
    Serial.println(tomat);
  }
  if (command == "33") {
    bayam = ! bayam;
    Serial.println(bayam);
  }
  if (command == "44") {
    lavender = ! lavender;
    Serial.println(lavender);
  }
  if (command == "55") {
    Serial.println("cek");
    kirimparameter();
  }
  if (command == "66") SetSv();
  if (command == "77") statusTanki();

  dataIn = "";

  if (tomat) Tomat();
  else {
    digitalWrite(Sv_1, HIGH);
    digitalWrite(Sv_2, HIGH);
    digitalWrite(Sv_3, HIGH);
  }

  if (bayam) Bayam();
  else {
    digitalWrite(Sv_4, HIGH);
    digitalWrite(Sv_5, HIGH);
    digitalWrite(Sv_6, HIGH);
  }

  if (lavender) Lavender();
  else {
    digitalWrite(Sv_7, HIGH);
    digitalWrite(Sv_8, HIGH);
    digitalWrite(Sv_9, HIGH);
  }


  delay(500);
}

void pulseCounter()
{
  pulseCount++;
}

void pulseCounter1()
{
  pulseCount1++;
}

void pulseCounter2()
{
  pulseCount2++;
}

void waterflow1()
{
  if ((millis() - oldTime) > 1000)
  {
    detachInterrupt(sensorInterrupt1);
    flowRate1 = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    oldTime = millis();
    flowMilliLitres1 = (flowRate1 / 60) * 1000;
    totalMilliLitres1 += flowMilliLitres1;
    unsigned int frac;
    pulseCount = 0;
  }
}

void attachwtr1()
{
  pulseCount = 0;
  attachInterrupt(sensorInterrupt1, pulseCounter, FALLING);
}

void waterflow2()
{
  if ((millis() - oldTime1) > 1000)
  {
    detachInterrupt(sensorInterrupt2);
    flowRate2 = ((1000.0 / (millis() - oldTime1)) * pulseCount1) / calibrationFactor;
    oldTime1 = millis();
    flowMilliLitres2 = (flowRate2 / 60) * 1000;
    totalMilliLitres2 += flowMilliLitres2;
    unsigned int frac;
    pulseCount1 = 0;
  }
}
void attachwtr2()
{
  pulseCount1 = 0;
  attachInterrupt(sensorInterrupt2, pulseCounter, FALLING);
}

void waterflow3()
{
  if ((millis() - oldTime2) > 1000)
  {
    detachInterrupt(sensorInterrupt3);
    flowRate3 = ((1000.0 / (millis() - oldTime2)) * pulseCount2) / calibrationFactor;
    oldTime2 = millis();
    flowMilliLitres3 = (flowRate3 / 60) * 1000;
    totalMilliLitres3 += flowMilliLitres3;
    unsigned int frac;
    pulseCount2 = 0;
  }
}
void attachwtr3()
{
  pulseCount = 0;
  attachInterrupt(sensorInterrupt3, pulseCounter, FALLING);
}

void Tomat() {
  Soil1 = analogRead(sm1);
  Soil2 = analogRead(sm2);
  Soil3 = analogRead(sm3);
  Serial.println("tomat  ");
  Serial.println(Soil1);
  Serial.println(Soil2);
  Serial.println(Soil3);
  Serial.println(flowMilliLitres1);
  Serial.println("");
  //  digitalWrite(LED_BUILTIN, HIGH);

  if (Soil1 > 525) {
    digitalWrite(pompa2, LOW);
    digitalWrite(Sv1, LOW);
  }

  else if (Soil2 > 525) {
    digitalWrite(pompa2, LOW);
    digitalWrite(Sv2, LOW);
  }

  else if (Soil3 > 525) {
    digitalWrite(pompa2, LOW);
    digitalWrite(Sv3, LOW);
  }
  else if (flowMilliLitres1 < 450) {
    digitalWrite(pompa2, HIGH);
    digitalWrite(Sv1, HIGH);
    digitalWrite(Sv2, HIGH);
    digitalWrite(Sv3, HIGH);
  }
  //  SetSv();
}

void Bayam() {
  Soil4 = analogRead(sm4);
  Soil5 = analogRead(sm5);
  Soil6 = analogRead(sm6);
  Serial.println("bayam  ");
  Serial.println(Soil4);
  Serial.println(Soil5);
  Serial.println(Soil6);
  Serial.println(totalMilliLitres2);
  Serial.println("");

  //  digitalWrite(LED_BUILTIN, LOW);

  if (Soil4 > 500) {
    digitalWrite(pompa2, LOW);
    digitalWrite(Sv4, LOW);
  }

  else if (Soil5 > 500) {
    digitalWrite(pompa2, LOW);
    digitalWrite(Sv5, LOW);
  }

  else if (Soil6 > 500) {
    digitalWrite(pompa2, LOW);
    digitalWrite(Sv6, LOW);
  }
  else if (totalMilliLitres2 < 400) {
    digitalWrite(pompa2, HIGH);
    digitalWrite(Sv4, HIGH);
    digitalWrite(Sv5, HIGH);
    digitalWrite(Sv6, HIGH);
  }
  //  SetSv();
}

void Lavender() {
  Soil7 = analogRead(sm7);
  Soil8 = analogRead(sm8);
  Soil9 = analogRead(sm9);
  Serial.println("tomat  ");
  Serial.println(Soil7);
  Serial.println(Soil8);
  Serial.println(Soil9);
  Serial.println(totalMilliLitres3);
  Serial.println("");

  if (Soil7 > 550) {
    digitalWrite(pompa2, LOW);
    digitalWrite(Sv7, LOW);
  }

  else if (Soil8 > 550) {
    digitalWrite(pompa2, LOW);
    digitalWrite(Sv8, LOW);
  }

  else if (Soil9 > 550) {
    digitalWrite(pompa2, LOW);
    digitalWrite(Sv9, LOW);
  }
  else if (totalMilliLitres3 < 350) {
    digitalWrite(pompa2, HIGH);
    digitalWrite(Sv7, HIGH);
    digitalWrite(Sv8, HIGH);
    digitalWrite(Sv9, HIGH);
  }
  //  SetSv();
}

void Sistem_OFF()
{
  SetSv();
}

void statusTanki() {
  Ultrasonik();

  if (tanki) {
    Serial.print('@');
    Serial1.print('@');
    Serial.print(',');
    Serial1.print(',');
    Serial.print("Tanki Penuh");
    Serial1.print("Tanki Penuh");
    Serial.print(',');
    Serial1.print(',');
    Serial.print('#');
    Serial1.print('#');
    Serial.println(" ");
    Serial1.print(" ");
  }

  else {
    Serial.print('@');
    Serial1.print('@');
    Serial.print(',');
    Serial1.print(',');
    Serial.print("Tanki Kurang");
    Serial1.print("Tanki Kurang");
    Serial.print(',');
    Serial1.print(',');
    Serial.print('#');
    Serial1.print('#');
    Serial.println(" ");
    Serial1.print(" ");
  }
}

void Ultrasonik()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  if (distance >= 25) {
    digitalWrite(pompa1, LOW);
    tanki = false;
  }
  else if (distance < 5) {
    digitalWrite(pompa1, HIGH);
    tanki = true;
  }
}

void kirimparameter() {
  Serial.print('@');
  Serial1.print('@');
  Serial.print(',');
  Serial1.print(',');
  Serial.print(Soil1);
  Serial1.print(Soil1);
  Serial.print(',');
  Serial1.print(',');
  Serial.print(Soil2);   //show on SM1 of Fig-1 what you are sending to UNO-2
  Serial1.print(Soil2);   //send ASCII coded string to UNO-2 via data Port; goes 1 char at a time
  Serial.print(',');
  Serial1.print(',');
  Serial.print(Soil3);   //show on SM1 of Fig-1 what you are sending to UNO-2
  Serial1.print(Soil3);
  Serial.print(',');
  Serial1.print(',');
  Serial.print(Soil4);   //show on SM1 of Fig-1 what you are sending to UNO-2
  Serial1.print(Soil4);
  Serial.print(',');
  Serial1.print(',');
  Serial.print(Soil5);   //show on SM1 of Fig-1 what you are sending to UNO-2
  Serial1.print(Soil5);
  Serial.print(',');
  Serial1.print(',');
  Serial.print(Soil6);   //show on SM1 of Fig-1 what you are sending to UNO-2
  Serial1.print(Soil6);
  Serial.print(',');
  Serial1.print(',');
  Serial.print(Soil7);   //show on SM1 of Fig-1 what you are sending to UNO-2
  Serial1.print(Soil7);
  Serial.print(',');
  Serial1.print(',');
  Serial.print(Soil8);   //show on SM1 of Fig-1 what you are sending to UNO-2
  Serial1.print(Soil8);
  Serial.print(',');
  Serial1.print(',');
  Serial.print(Soil9);   //show on SM1 of Fig-1 what you are sending to UNO-2
  Serial1.print(Soil9);
  Serial.print(',');
  Serial1.print(',');
  Serial.print(flowMilliLitres1);   //show on SM1 of Fig-1 what you are sending to UNO-2
  Serial1.print(flowMilliLitres1);
  Serial.print(',');
  Serial1.print(',');
  Serial.print(totalMilliLitres2);   //show on SM1 of Fig-1 what you are sending to UNO-2
  Serial1.print(totalMilliLitres2);
  Serial.print(',');
  Serial1.print(',');
  Serial.print(totalMilliLitres3);   //show on SM1 of Fig-1 what you are sending to UNO-2
  Serial1.print(totalMilliLitres3);
  Serial.print(',');
  Serial1.print(',');
  Serial.print(distance);   //show on SM1 of Fig-1 what you are sending to UNO-2
  Serial1.print(distance);
  Serial.print(',');
  Serial1.print(',');
  Serial.print('#');
  Serial1.print('#');
  Serial.println(" ");
  Serial1.print(" ");

}

void SetSv()
{
  tomat = false;
  bayam = false;
  lavender = false;
  digitalWrite(pompa2, HIGH);
  digitalWrite(Sv1, HIGH);
  digitalWrite(Sv2, HIGH);
  digitalWrite(Sv3, HIGH);
  digitalWrite(Sv4, HIGH);
  digitalWrite(Sv5, HIGH);
  digitalWrite(Sv6, HIGH);
  digitalWrite(Sv7, HIGH);
  digitalWrite(Sv8, HIGH);
  digitalWrite(Sv9, HIGH);
}
