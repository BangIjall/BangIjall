#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#include <Servo.h>

#define LEFT    1  
#define RIGHT   A3 
#define FORWD   A4
#define REVRS   A5 
#define UP      A2
#define DOWN    12 
#define BUKA    13
#define TUTUP   A0 
#define CC      0  
#define CCW     A1 

Servo lenganAtas; 
Servo lenganBawah;
Servo putar;
Servo leher;
Servo capit;

float L1        = 10.0000;
float L2        = 12.5000;
float actStep   = 2.00;
int   angleStep = 4;

float ax        = 9.00;
float ay        = 9.00;
float az        = 9.00;
float diag, alfa, beta;
int putaran, grip;
int   A,B,C;

void setup() {
  lcd.begin();
  lcd.backlight(); 
  lenganAtas.attach(3); 
  lenganBawah.attach(5); 
  putar.attach(6); 
  leher.attach(9); 
  capit.attach(10); 
  pinMode(LEFT,INPUT_PULLUP); 
  pinMode(RIGHT,INPUT_PULLUP);
  pinMode(UP,INPUT_PULLUP); 
  pinMode(DOWN,INPUT_PULLUP);
  pinMode(FORWD,INPUT_PULLUP); 
  pinMode(REVRS,INPUT_PULLUP);
  pinMode(CC,INPUT_PULLUP); 
  pinMode(CCW,INPUT_PULLUP);
  pinMode(BUKA,INPUT_PULLUP); 
  pinMode(TUTUP,INPUT_PULLUP);
  gerak(ax, ay, az);
  lcd.print("     POLINES    ");
  lcd.setCursor(0,1);
  lcd.print("     UKM PP     ");
  delay(2000);
  lcd.clear();
  lcd.print("  ROBOT LENGAN  ");
  lcd.setCursor(0,1);
  lcd.print(" TIM RISET 2021 ");
}

void loop() {
  if (digitalRead(LEFT) == LOW){
    while(digitalRead(LEFT) == LOW){
      ax = ax - actStep;
      gerak(ax, ay, az);
      delay(200);
    }
  }
  
  if (digitalRead(RIGHT) == LOW){
    while(digitalRead(RIGHT) == LOW){
      ax = ax + actStep;
      gerak(ax, ay, az);
      delay(200);
    }
  }
  
  if (digitalRead(UP) == LOW){
    while(digitalRead(UP) == LOW){
      az = az + actStep;
      gerak(ax, ay, az);
      delay(200);
    }
  }
  
  if (digitalRead(DOWN) == LOW){
    while(digitalRead(DOWN) == LOW){
      az = az - actStep;
      gerak(ax, ay, az);
      delay(200);
    }
  }
  
  if (digitalRead(FORWD) == LOW){
    while(digitalRead(FORWD) == LOW){
      ay = ay + actStep;
      gerak(ax, ay, az);
      delay(200);
    }
  }
  
  if (digitalRead(REVRS) == LOW){
    while(digitalRead(REVRS) == LOW){
      ay = ay - actStep;
      gerak(ax, ay, az);
      delay(200);
    }
  }
  
  if (digitalRead(CC) == LOW){
    while(digitalRead(CC) == LOW){
      putaran = putaran - angleStep;
      gerak(ax, ay, az);
      delay(200);
    }
  }
  
  if (digitalRead(CCW) == LOW){
    while(digitalRead(CCW) == LOW){
      putaran = putaran + angleStep;
      gerak(ax, ay, az);
      delay(200);
    }
  }
  
  if (digitalRead(BUKA) == LOW){
    while(digitalRead(BUKA) == LOW){
      grip = grip + angleStep;
      gerak(ax, ay, az);
      delay(200);
    }
  }
  
  if (digitalRead(TUTUP) == LOW){
    while(digitalRead(TUTUP) == LOW){
      grip = grip - angleStep;
      gerak(ax, ay, az);
      delay(200);
    }
  }
}

void inverse(float X, float Y, float Z) {
  diag = sqrt((Z*Z) + (X*X) + (Y*Y));
  beta = atan(Z/(sqrt((X*X) + (Y*Y))));
  alfa = acos(((L2*L2) + (diag*diag) - (L1*L1)) / (2*L2*diag));
  
  A    = alfa + beta;
  B    = acos(((L1*L1) + (L2*L2) - (diag*diag)) / (2*L1*L2));
  C    = atan(Y/X);  
}

void gerak(float X, float Y, float Z) {
  inverse(ax, ay, az);
  
  lenganAtas.write(B); 
  lenganBawah.write(A); 
  putar.write(C); 
  leher.write(putaran); 
  capit.write(grip);
}
