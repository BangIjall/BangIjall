#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN     12  
#define ECHO_PIN        10  
#define MAX_DISTANCE    200 
#define buzz            11

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal_I2C       lcd(0x27, 16, 2);
Servo                   myservo;
NewPing                 sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

float data;
char masker;

void suhu(void);
void buka(void);
void tutup(void);

void setup()
{
  myservo.attach(6);
  myservo.write(0);
  pinMode(buzz, OUTPUT);
  digitalWrite(buzz, LOW);
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  mlx.begin();
  lcd.print("     LOADING");
  delay(1000);
  lcd.clear();
}

void loop()
{
  masker = Serial.read();
  Serial.println(masker);
  awal:
  if (masker == '1')
  {
    lcd.clear();
    digitalWrite(buzz, HIGH);
    delay(1500);
    digitalWrite(buzz, LOW);
    delay(500);
    digitalWrite(buzz, HIGH);
    delay(500);
    digitalWrite(buzz, LOW);
    delay(500);
    digitalWrite(buzz, HIGH);
    delay(500);
    digitalWrite(buzz, LOW);
    delay(500);
A:
    if (sonar.ping_cm() <= 5)
    {
      lcd.clear();
      lcd.print(" Sedang Membaca ");
      lcd.setCursor(0, 1);
      lcd.print("      Suhu      ");
      delay(4000);
      suhu();
      if (data <= 37.20)
      {
        buka();
        masker = '3';
        goto awal;
      }
      else
      {
        tutup();
        masker = '3';
        goto awal;
      }
    }
    else
    {
      lcd.print(" Silahkan Ukur  ");
      lcd.setCursor(0, 1);
      lcd.print("      Suhu      ");
      goto A;
    }
  }

  if (masker == '2')
  {
    lcd.clear();
    lcd.print(" Silahkan Pakai ");
    lcd.setCursor(0, 1);
    lcd.print("     Masker     ");
  }

  if (masker == '3')
  {
    lcd.clear();
    lcd.print("Posisikan Wajah ");
    lcd.setCursor(0, 1);
    lcd.print("   Ke Kamera    ");
  }
}

void suhu()
{
  lcd.clear();
  data = mlx.readObjectTempC();
  Serial.print("*C\tObject = ");
  Serial.print(data);
  Serial.println("*C");
  Serial.println();
  lcd.print("Suhu Anda: ");
  lcd.setCursor(0, 1);
  lcd.print(data);
  delay(3000);
}

void buka()
{
  lcd.clear();
  lcd.print("Silahkan Masuk");
  myservo.write(90);
  while (1)
  {
    if (sonar.ping_cm() >= 5)
    {
      goto A1;
    }
  }
A1:
  delay(30000);
  myservo.write(0);
  lcd.clear();
}

void tutup()
{
  lcd.clear();
  digitalWrite(buzz, HIGH);
  lcd.print("   Suhu Anda    ");
  lcd.setCursor(0, 1);
  lcd.print(" Melebihi Batas ");
  delay(3000);
  digitalWrite(buzz, LOW);
  delay(10000);
  lcd.clear();
}
