int en1=7; 
int en2=2; 
int in1=5;
int in2=3;
int in3=6;
int in4=4;

void setup() {
pinMode(en1,OUTPUT);
pinMode(en2,OUTPUT);
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
Serial.begin(9600); 
}
void loop() {
/*analogWrite(en1,1000);  
digitalWrite(in1,HIGH);
digitalWrite(in2,LOW); 
analogWrite(en2,1000);  
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW); 
Serial.println("maju");
delay(5000);*/
analogWrite(en1,0);    
digitalWrite(in1,LOW); 
digitalWrite(in2,LOW); 
analogWrite(en2,255);    
digitalWrite(in3,HIGH); 
digitalWrite(in4,LOW); 
Serial.println("mati");
delay(5000);
/*analogWrite(en1,255);  
digitalWrite(in1,LOW); 
digitalWrite(in2,HIGH);   //in2 mendapat tegangan positif
//jika in1 tidak dapat tegangan dan in2 dapat tegangan,maka motor bergerak mundur
analogWrite(en2,255);     //kecepatan motor en2=255
digitalWrite(in3,LOW);    //in3 tidak dapat tegangan/negatif
digitalWrite(in4,HIGH);   //in4 mendapat tegangan positif
//jika in3 tidak dapat tegangan dan in4 dapat tegangan,maka motor bergerak mundur
Serial.println("mundur"); //menampilkan di serial monitor bahwa motor bergerak mundur
delay(5000);*/
}
