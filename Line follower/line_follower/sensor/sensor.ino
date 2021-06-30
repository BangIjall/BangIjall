#define L1 1
#define L2 0
#define L3 A5
#define L4 A3
#define L5 A4
#define L6 A2
#define L7 A1
#define L8 A0
int en1=7; 
int en2=2; 
int in1=5;
int in2=3;
int in3=6;
int in4=4;

#define Z A6
int selector[8]={0b00111000,0b00100000,0b00011000,0b00101000,0b00010000,0b00110000,0b00001000,0b00000000};
int i;
int sensor[8];
struct sensReading
{
  unsigned int baca;
  unsigned int state;
}s1,s2,s3,s4,s5,s6,s7,s8;

void setup() {
  pinMode(A6,INPUT);
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(L3,OUTPUT);
  pinMode(L4,OUTPUT);
  pinMode(L5,OUTPUT);
  pinMode(L6,OUTPUT);
  pinMode(L7,OUTPUT);
  pinMode(L8,OUTPUT);
  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  DDRB=0x38;
  Serial.begin(9600); 
}
 
void LED(){
  if(s1.baca<500){s1.state=1;digitalWrite(L1,LOW);}else{s1.state=0;digitalWrite(L1,HIGH);}
  if(s2.baca<500){s2.state=1;digitalWrite(L2,LOW);}else{s2.state=0;digitalWrite(L2,HIGH);}
  if(s3.baca<500){s3.state=1;digitalWrite(L3,LOW);}else{s3.state=0;digitalWrite(L3,HIGH);}
  if(s4.baca<500){s4.state=1;digitalWrite(L4,LOW);}else{s4.state=0;digitalWrite(L4,HIGH);}
  if(s5.baca<500){s5.state=1;digitalWrite(L5,LOW);}else{s5.state=0;digitalWrite(L5,HIGH);}
  if(s6.baca<500){s6.state=1;digitalWrite(L6,LOW);}else{s6.state=0;digitalWrite(L6,HIGH);}
  if(s7.baca<00){s7.state=1;digitalWrite(L7,LOW);}else{s7.state=0;digitalWrite(L7,HIGH);}
  if(s8.baca<500){s8.state=1;digitalWrite(L8,LOW);}else{s8.state=0;digitalWrite(L8,HIGH);}
}

void maju(int kiri, int kanan) {
  analogWrite(en1,kiri);  
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW); 
  analogWrite(en2,kanan);  
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void belok_kanan(int kiri, int kanan) {
  analogWrite(en1,kiri);  
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW); 
  analogWrite(en2,kanan);  
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

void belok_kiri(int kiri, int kanan) {
  analogWrite(en1,kiri);  
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW); 
  analogWrite(en2,kanan);  
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);

}
void nikung_kiri(int kiri, int kanan) {
  analogWrite(en1,kiri);  
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH); 
  analogWrite(en2,kanan);  
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void nikung_kanan(int kiri, int kanan) {
  analogWrite(en1,kiri);  
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH); 
  analogWrite(en2,kanan);  
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void loop() {
  for (byte i=0; i<8; i++) {
    PORTB = selector[i];
    int val = analogRead(Z);
    sensor[i]=val;
  }
  s1.baca = sensor[0];
  s2.baca = sensor[2];
  s3.baca = sensor[6];
  s4.baca = sensor[3];
  s5.baca = sensor[4];
  s6.baca = sensor[5];
  s7.baca = sensor[7];
  s8.baca = sensor[1];   
  Serial.print("1 : ");
  Serial.print(sensor[0]);
  Serial.print(" | ");
  Serial.print("2 : ");
  Serial.print(sensor[2]);
  Serial.print(" | ");
  Serial.print("3 : ");
  Serial.print(sensor[6]);
  Serial.print(" | ");
  Serial.print("4 : ");
  Serial.print(sensor[3]);
  Serial.print(" | ");
  Serial.print("5 : ");
  Serial.print(sensor[4]);
  Serial.print(" | ");
  Serial.print("6 : ");
  Serial.print(sensor[5]);
  Serial.print(" | ");
  Serial.print("7 : ");
  Serial.print(sensor[7]);
  Serial.print(" | ");
  Serial.print("8 : ");
  Serial.print(sensor[1]);
  Serial.print(" | ");
  Serial.println("");
  LED();
  if(s2.baca>500) {
    nikung_kiri(255,255);
  }else
  if(s3.baca>500) {
    belok_kiri(0,255);
  }else
  /*if(s1.baca>500 && s2.baca>500 && s6.baca<500) {
    nikung_kiri(255,255);
  }else*/
  if(s6.baca>500) {
    belok_kanan(255,0);
  }else
  if(s7.baca>500) {
    nikung_kanan(255,255);
  }else
  /*if(s8.baca>500 && s7.baca>500 && s3.baca<500) {
    nikung_kanan(255,255);
  }else */
  if(s4.baca>500)
  {
    maju(255,255);
  }
  if(s5.baca>500)
  {
    maju(255,255);
  }
  delay(1);
}
