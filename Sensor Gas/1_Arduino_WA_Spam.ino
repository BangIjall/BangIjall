#include <Arduino.h>
#include <SoftwareSerial.h>
#define rx_pin 8
#define tx_pin 7
SoftwareSerial data(rx_pin, tx_pin);
const float RL = 1;
const float clean_air_ratio = 10.0;
float adc, RS, Ro, RsRo, ppm, v;
float adc1, RS1, Ro1, RsRo1, ppm1, v1;
float adc2, RS2, Ro2, RsRo2, ppm2, v2;
const int SSR = 4;
const int buzzer = 3;
const int ledmerah = 5;
const int ledhijau = 6;
void kirimdata();
void setup()
{
  Serial.begin(9600);
  data.begin(115200);
  pinMode(buzzer, OUTPUT);
  pinMode(SSR, OUTPUT);
  pinMode(ledmerah, OUTPUT);
  pinMode(ledhijau, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  //sensor MQ di tabung
  int adc = analogRead(A0);
  v = adc * 5 / 1023.00;
  RS = ((5 * RL / v) - RL);
  Ro = RS / clean_air_ratio;
  delay(1000);

  //sensor MQ di SSR solenoid valve
  int adc1 = analogRead(A1);
  v1 = adc1 * 5 / 1023.00;
  RS1 = ((5 * RL / v1) - RL);
  Ro1 = RS1 / clean_air_ratio;
  delay(1000);

  //sensor MQ kompor
  int adc2 = analogRead(A2);
  v2 = adc2 * 5 / 1023.00;
  RS2 = ((5 * RL / v2) - RL);
  Ro2 = RS2 / clean_air_ratio;
  delay(1000);
}

void loop()
{
  kirimdata();
}

void kirimdata()
{
  //sensor MQ di tabung gas
  do
  {
  int adc = analogRead(A0);
  v = adc * 5 / 1023.00;
  RS = ((5 * RL / v) - RL);
  RsRo = RS / Ro;
  ppm = 1099.6 * pow((RsRo), -2.31);
  if (ppm >= 1000)
  {
    digitalWrite(buzzer, HIGH); // switch buzzer off
    digitalWrite(SSR, HIGH);
    digitalWrite(ledmerah, HIGH);
    digitalWrite(ledhijau, LOW);
    String datakirim = "a";
    Serial.println(datakirim);
    data.print(datakirim);
    data.write(13);
    delay(1000);
  }
  else
  {
    digitalWrite(buzzer, LOW); // switch buzzer on for 100ms
    digitalWrite(SSR, LOW);
    digitalWrite(ledmerah, LOW);
    digitalWrite(ledhijau, HIGH);
  }
  }
  while(ppm>=1000);

  //sensor MQ di SSR solenoid valve
  do
  {
  int adc1 = analogRead(A1);
  v1 = adc1 * 5 / 1023.00;
  RS1 = ((5 * RL / v1) - RL);
  RsRo1 = RS1 / Ro1;
  ppm1 = 1099.6 * pow((RsRo1), -2.31);

  if (ppm1 >= 1000)
  {
    digitalWrite(buzzer, HIGH); // switch buzzer off
    digitalWrite(SSR, HIGH);
    digitalWrite(ledmerah, HIGH);
    digitalWrite(ledhijau, LOW);
    String datakirim1 = "b";
    Serial.println(datakirim1);
    data.print(datakirim1);
    data.write(13);
    delay(1000);
  }
  else
  {
    digitalWrite(buzzer, LOW); // switch buzzer on for 100ms
    digitalWrite(SSR, LOW);
    digitalWrite(ledmerah, LOW);
    digitalWrite(ledhijau, HIGH);
  }
  }
   while(ppm1>=1000);

  //sensor MQ di kompor
  do
  {
  int adc2 = analogRead(A2);
  v2 = adc2 * 5 / 1023.00;
  RS2 = ((5 * RL / v2) - RL);
  RsRo2 = RS2 / Ro2;
  ppm2 = 1099.6 * pow((RsRo2), -2.31);

  if (ppm2 >= 1000)
  {
    digitalWrite(buzzer, HIGH); // switch buzzer off
    digitalWrite(SSR, HIGH);
    digitalWrite(ledmerah, HIGH);
    digitalWrite(ledhijau, LOW);
    String datakirim2 = "c";
    Serial.println(datakirim2);
    data.print(datakirim2);
    data.write(13);
    delay(1000);
  }
  else
  {
    digitalWrite(buzzer, LOW); // switch buzzer on for 100ms
    digitalWrite(SSR, LOW);
    digitalWrite(ledmerah, LOW);
    digitalWrite(ledhijau, HIGH);
  }
  }
   while(ppm2>=1000);

  //sediakan variabel data yang akan dikirm
  Serial.println("ppm0 : " + (String)ppm + ", ppm1 : " + (String)ppm1 + " ppm2 : " + (String)ppm2);
  delay(1000);
}
