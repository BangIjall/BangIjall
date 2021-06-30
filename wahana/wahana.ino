int IN_1 = 2;
int IN_2 = 6;
int kondisi[2]; //2 kondisi
int tombol[4]={A0,A1,A2,A3}; //4 tombol
int n;
void setup() {

 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 digitalWrite(IN_1,HIGH);
 digitalWrite(IN_2,HIGH);
 for (n=0; n<4; n++) {
    pinMode(tombol[n], INPUT_PULLUP);
 }
 if(digitalRead(tombol[2])==HIGH) {  
   while(1) {
     naik(); 
     if(digitalRead(tombol[2])==LOW) {
       goto C;
     }
   }
 }
 C:
 diam();
}

void loop() {

  if(digitalRead(tombol[0])==LOW /*&&digitalRead(tombol[3])==LOW*/) {
    delay(5000);
    while(1) {
      naik(); 
      if(digitalRead(tombol[2])==LOW) {
        goto A;
      }
    }
    A:
    diam();
  }

  if(digitalRead(tombol[1])==LOW && digitalRead(tombol[2])==LOW) {
    while(1) {
      turun(); 
      if(digitalRead(tombol[3])==LOW) {
        goto B;
      }
    }
    B:
    diam();
  }

}

void naik() {
 digitalWrite(IN_1, HIGH);
 digitalWrite(IN_2, LOW);
}

void turun() {
 digitalWrite(IN_1, LOW);
 digitalWrite(IN_2, HIGH);
}

void diam() {
 digitalWrite(IN_1, HIGH);
 digitalWrite(IN_2, HIGH);
}
