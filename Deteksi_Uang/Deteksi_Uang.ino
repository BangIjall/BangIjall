#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   32
#define S0              8
#define S1              7
#define S2              6
#define S3              5
#define OutputSensor    4
#define OLED_RESET      4

SoftwareSerial mySerial(10, 11);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int f_red             = 0;
int f_green           = 0;
int f_blue            = 0;
int k                 = 10;

void setup()
{
  Serial.begin(9600);
  mySerial.begin (9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  mp3_set_serial (mySerial);
  delay(1);
  mp3_set_volume (80);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OutputSensor, INPUT);
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Tugas Akhir");

  display.setTextColor(WHITE);
  display.println("Alat pembaca uang");

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("UNDIP");

  display.display();

  delay(2000);
}

void loop() {
  baca();

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("    Letakkan uang");

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.print("    pada tempatnya");

  display.display();

  delay(2000);

  if (abs(f_red - 470) < k && abs(f_green - 511) < k && abs(f_blue - 465) < k) {
    Serial.println("UANG 1000");
    
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Letakkan uang");
    
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Nominal :");

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("Rp1000");

    display.display();

    mp3_play (1);
    delay(6000);
  }

  if (abs(f_red - 450) < k && abs(f_green - 476) < k && abs(f_blue - 412) < k) {
    Serial.println("UANG 2000");
    
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Letakkan uang");

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Nominal :");

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("Rp2.000");

    display.display();

    mp3_play (2);
    delay(6000);
  }

  if (abs(f_red - 347) < k && abs(f_green - 422) < k && abs(f_blue - 398) < k) {
    Serial.println("UANG 5000");
    
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Letakkan uang");
    
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Nominal :");

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("Rp5.000");

    display.display();

    mp3_play (3);
    delay(6000);
  }

  if (abs(f_red - 470) < k && abs(f_green - 480) < k && abs(f_blue - 315) < k) {
    Serial.println("UANG 10000");
    
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Letakkan uang");
    
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Nominal :");

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("Rp10.000");

    display.display();

    mp3_play (4);
    delay(6000);
  }

  if (abs(f_red - 436) < k && abs(f_green - 388) < k && abs(f_blue - 334) < k) {
    Serial.println("UANG 20000");
    
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Letakkan uang");
    
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Nominal :");

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("Rp20.000");

    display.display();

    mp3_play (5);
    delay(6000);
  }

  if (abs(f_red - 563) < k && abs(f_green - 460) < k && abs(f_blue - 325) < k) {
    Serial.println("UANG 50000");
    
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Letakkan uang");
    
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Nominal :");

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("Rp50.000");

    display.display();

    mp3_play (6);
    delay(6000);
  }

  if (abs(f_red - 390) < k && abs(f_green - 453) < k && abs(f_blue - 374) < k) {
    Serial.println("UANG 75000");
    
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Letakkan uang");
    
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Nominal :");

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("Rp75.000");

    display.display();

    mp3_play (7);
    delay(6000);
  }

  if (abs(f_red - 365) < k && abs(f_green - 431) < k && abs(f_blue - 350) < k) {
    Serial.println("UANG 100000");
    
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Letakkan uang");
    
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Nominal :");

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("Rp100.000");

    display.display();

    mp3_play (8);
    delay(6000);
  }
}

void baca() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  f_red = pulseIn(OutputSensor, LOW);
  Serial.print("R = ");
  Serial.println(f_red);
  delay(1000);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  f_green = pulseIn(OutputSensor, LOW);
  Serial.print("G = ");
  Serial.println(f_green);
  delay(1000);

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  f_blue = pulseIn(OutputSensor, LOW);
  Serial.print("B = ");
  Serial.println(f_blue);
  delay(1000);
}
