int num = 0;
void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(2), resetNum, FALLING);

}

void loop() {

  Serial.print(bitRead(num, 0));
  Serial.print(bitRead(num, 1));
  Serial.print(bitRead(num, 2));
  Serial.println(bitRead(num, 3));

  delay(1000);

  num = num + 1;
  if (num == 10)
  {
    num = 0;
  }
}

void resetNum() {

  num = 0;

  digitalWrite(4, bitRead(num, 0));
  digitalWrite(5, bitRead(num, 1));
  digitalWrite(6, bitRead(num, 2));
  digitalWrite(7, bitRead(num, 3));
}
