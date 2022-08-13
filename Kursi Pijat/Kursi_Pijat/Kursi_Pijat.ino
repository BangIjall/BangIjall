#define PBpijat   2
#define PBgetar   3
#define PBIR      4
#define plus      5
#define minus     6
#define pijat     11
#define getar     9
#define IR        10
#define ledPijat  8
#define ledGetar  12
#define ledIR     13

int pwmPijat;
int pwmGetar;
int pwmIR;
int kondisi;
int timer;
int timer2;
long prevMillis;

void setup() {
  pinMode(PBpijat, INPUT_PULLUP);
  pinMode(PBgetar, INPUT_PULLUP);
  pinMode(PBIR, INPUT_PULLUP);
  pinMode(plus, INPUT_PULLUP);
  pinMode(minus, INPUT_PULLUP);
  pinMode(ledPijat, OUTPUT);
  pinMode(ledGetar, OUTPUT);
  pinMode(ledIR, OUTPUT);
  pinMode(pijat, OUTPUT);
  pinMode(getar, OUTPUT);
  pinMode(IR, OUTPUT);
  int pwmPijat;
  int pwmGetar;
  int pwmIR;
}

void loop() {
  digitalWrite(pijat, pwmPijat);
  analogWrite(getar, pwmGetar);
  analogWrite(IR, pwmIR);

  if (pwmPijat <= 0) pwmPijat = 0;
  if (pwmPijat >= 255) pwmPijat = 255;
  if (pwmGetar <= 0) pwmGetar = 0;
  if (pwmGetar >= 150) pwmGetar = 150;
  if (pwmIR <= 0) pwmIR = 0;
  if (pwmIR >= 255) pwmIR = 255;

  if (digitalRead(PBpijat) == LOW) {
    kondisi = 0;
  }
  if (digitalRead(PBgetar) == LOW) {
    kondisi = 1;
  }
  if (digitalRead(PBIR) == LOW) {
    kondisi = 2;
  }

  switch (kondisi) {
    case 0:
      digitalWrite(ledPijat, HIGH);
      digitalWrite(ledGetar, LOW);
      digitalWrite(ledIR, LOW);

      if (digitalRead(plus) == LOW) {
        pwmPijat = 1;
        while (digitalRead(plus) == LOW) {
          digitalWrite(pijat, pwmPijat);
          analogWrite(getar, pwmGetar);
          analogWrite(IR, pwmIR);
          delay(100);
        }
      }

      if (digitalRead(minus) == LOW) {
        pwmPijat = 0;
        while (digitalRead(minus) == LOW) {
          digitalWrite(pijat, pwmPijat);
          analogWrite(getar, pwmGetar);
          analogWrite(IR, pwmIR);
          delay(100);
        }
      }
      break;

    case 1:
      digitalWrite(ledPijat, LOW);
      digitalWrite(ledGetar, HIGH);
      digitalWrite(ledIR, LOW);

      if (digitalRead(plus) == LOW) {
        while (timer <= 5 && (digitalRead(plus) == LOW)) {
          timer++;
          digitalWrite(pijat, pwmPijat);
          analogWrite(getar, pwmGetar);
          analogWrite(IR, pwmIR);
          delay(100);
        }
        timer = 0;
        while (digitalRead(plus) == LOW && pwmGetar < 149) {
          if (pwmPijat <= 0) pwmPijat = 0;
          if (pwmPijat >= 255) pwmPijat = 255;
          if (pwmGetar <= 0) pwmGetar = 0;
          if (pwmGetar >= 150) pwmGetar = 150;
          if (pwmIR <= 0) pwmIR = 0;
          if (pwmIR >= 255) pwmIR = 255;
          digitalWrite(pijat, pwmPijat);
          analogWrite(getar, pwmGetar);
          analogWrite(IR, pwmIR);
          timer2++;
          if (timer2 > 2) {
            pwmGetar = pwmGetar + 5;
            timer2 = 0;
          }
          delay(100);
        }
      }

      if (digitalRead(minus) == LOW) {
        pwmGetar = pwmGetar - 5;
        while (timer <= 5 && (digitalRead(minus) == LOW)) {
          timer++;
          digitalWrite(pijat, pwmPijat);
          analogWrite(getar, pwmGetar);
          analogWrite(IR, pwmIR);
          delay(100);
        }
        timer = 0;
        while (digitalRead(minus) == LOW && pwmGetar > 1) {
          if (pwmPijat <= 0) pwmPijat = 0;
          if (pwmPijat >= 255) pwmPijat = 255;
          if (pwmGetar <= 0) pwmGetar = 0;
          if (pwmGetar >= 150) pwmGetar = 150;
          if (pwmIR <= 0) pwmIR = 0;
          if (pwmIR >= 255) pwmIR = 255;
          digitalWrite(pijat, pwmPijat);
          analogWrite(getar, pwmGetar);
          analogWrite(IR, pwmIR);
          timer2++;
          if (timer2 > 2) {
            pwmGetar = pwmGetar - 5;
            timer2 = 0;
          }
          delay(100);
        }
      }
      break;

    case 2:
      digitalWrite(ledPijat, LOW);
      digitalWrite(ledGetar, LOW);
      digitalWrite(ledIR, HIGH);

      if (digitalRead(plus) == LOW) {
        while (timer <= 5 && (digitalRead(plus) == LOW)) {
          timer++;
          digitalWrite(pijat, pwmPijat);
          analogWrite(getar, pwmGetar);
          analogWrite(IR, pwmIR);
          delay(100);
        }
        timer = 0;
        while (digitalRead(plus) == LOW && pwmIR < 254) {
          if (pwmPijat <= 0) pwmPijat = 0;
          if (pwmPijat >= 255) pwmPijat = 255;
          if (pwmGetar <= 0) pwmGetar = 0;
          if (pwmGetar >= 150) pwmGetar = 150;
          if (pwmIR <= 0) pwmIR = 0;
          if (pwmIR >= 255) pwmIR = 255;
          digitalWrite(pijat, pwmPijat);
          analogWrite(getar, pwmGetar);
          analogWrite(IR, pwmIR);
          timer2++;
          if (timer2 > 2) {
            pwmIR = pwmIR + 5;
            timer2 = 0;
          }
          delay(100);
        }
      }

      if (digitalRead(minus) == LOW) {
        pwmIR = pwmIR - 5;
        while (timer <= 5 && (digitalRead(minus) == LOW)) {
          timer++;
          digitalWrite(pijat, pwmPijat);
          analogWrite(getar, pwmGetar);
          analogWrite(IR, pwmIR);
          delay(100);
        }
        timer = 0;
        while (digitalRead(minus) == LOW && pwmIR > 1) {
          if (pwmPijat <= 0) pwmPijat = 0;
          if (pwmPijat >= 255) pwmPijat = 255;
          if (pwmGetar <= 0) pwmGetar = 0;
          if (pwmGetar >= 150) pwmGetar = 150;
          if (pwmIR <= 0) pwmIR = 0;
          if (pwmIR >= 255) pwmIR = 255;
          digitalWrite(pijat, pwmPijat);
          analogWrite(getar, pwmGetar);
          analogWrite(IR, pwmIR);
          timer2++;
          if (timer2 > 2) {
            pwmIR = pwmIR - 5;
            timer2 = 0;
          }
          delay(100);
        }
      }
      break;
  }

  delay(100);
}
