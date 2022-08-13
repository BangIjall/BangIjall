#define INA     4
#define INB     5
#define EN      6
#define HOME    12
#define STOPPER 3
#define TRIGGER  2
#define L1      8
#define L2      9
#define L3      10
#define MC      11
#define FORWARD    A3
#define REVERSE   A4
#define AUTO    A1
#define POT     A0

int pwm = 0;

void setup() {
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(MC, OUTPUT);
  pinMode(HOME, INPUT_PULLUP);
  pinMode(STOPPER, INPUT_PULLUP);
  pinMode(TRIGGER, INPUT_PULLUP);
  pinMode(AUTO, INPUT_PULLUP);
  pinMode(FORWARD, INPUT_PULLUP);
  pinMode(REVERSE, INPUT_PULLUP);

  digitalWrite(MC, HIGH);
  stop();

  Serial.begin(9600);

}

void loop() {
  pwm = analogRead(POT);
  pwm = map(pwm, 0, 1023, 0, 255);

  if (digitalRead(FORWARD) == LOW) ccw(pwm);
  else if (digitalRead(REVERSE) == LOW) cw(pwm);
  else stop();

  if (digitalRead(AUTO) == LOW) {
    digitalWrite(MC, LOW);
    while (digitalRead(STOPPER) == HIGH) {
      pwm = analogRead(POT);
      pwm = map(pwm, 0, 1023, 0, 255);
      if (digitalRead(TRIGGER) == LOW) ccw(pwm);
      else stop();
    }
    stop();
    digitalWrite(MC, HIGH);
    while (digitalRead(STOPPER) == HIGH) {
      cw(255);
    }
    stop();
  }
}

void stop() {
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);
  analogWrite(EN, 0);
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(L3, LOW);
  Serial.println("stop");
}

void cw(int speed) {
  digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);
  analogWrite(EN, speed);
  digitalWrite(L2, HIGH);
  digitalWrite(L1, LOW);
  digitalWrite(L3, LOW);
  Serial.println("REVERSE");
}

void ccw(int speed) {
  digitalWrite(INB, LOW);
  digitalWrite(INA, HIGH);
  analogWrite(EN, speed);
  digitalWrite(L3, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(L1, LOW);
  Serial.println("FORWARD");
}
