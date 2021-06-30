int en1=2;
int en2=7;
int in1=4;
int in2=6;
int in3=5;
int in4=3;
void setup()
{
  pinMode(en1,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(en2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
}
void maju(int ki, int ka)
{
  analogWrite(en1,ki);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(en2,ka);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void mundur(int ki, int ka)
{
  analogWrite(en1,ki);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(en2,ka);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void loop()
{
  maju(100,100);
  delay(2000);
  mundur(100,100);
  delay(2000);
}
