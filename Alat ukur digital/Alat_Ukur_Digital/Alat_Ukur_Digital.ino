#include <Wire.h>
#include <VL53L0X.h>
#include <NewPing.h>
#include <LiquidCrystal_I2C.h>

#define TRIGGER_PIN  12  
#define ECHO_PIN     11  
#define MAX_DISTANCE 200 
#define tombol       10

VL53L0X sensor;
LiquidCrystal_I2C lcd(0x27, 16, 2);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

bool mode = true;
int data;

void setup() {
  Serial.begin(9600);

  pinMode(tombol, INPUT_PULLUP);
  
  Wire.begin();
  lcd.begin();

  lcd.backlight();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.startContinuous();
}

void loop() {
  if (digitalRead(tombol) == LOW) {
    delay(100);
    mode = !mode;
  }
  tampil(mode);
  delay(1500);
  lcd.clear();
}

void tampil(bool ganti) {
  if (ganti == true) {
    cm();
    print_cursor(0, 0, "Mode  : cm ");
    print_cursor(0, 1, "Panjang : ");
    print_cursor1(7, 1, data);
  }
  if (ganti == false) {
    mm();
    print_cursor(0, 0, "Mode  : mm ");
    print_cursor(0, 1, "Panjang : ");
    print_cursor1(7, 1, data);
  }
}

void cm() {
  delay(50);
  data = sonar.ping_cm();
  Serial.print("panjang: ");
  Serial.print(data); 
  Serial.println("cm");
}

void mm() {
  delay(50);
  data = sensor.readRangeContinuousMillimeters() - 30;
  Serial.print("panjang: ");
  Serial.print(data); 
  Serial.println("cm");
}

void print_cursor(int x, int y, char *txt){
  lcd.setCursor(x, y);
  lcd.print(txt);
}

void print_cursor1(int x, int y, int txt){
  lcd.setCursor(x, y);
  lcd.print(txt);
}
