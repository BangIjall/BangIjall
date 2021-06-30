  #include <Servo.h>
Servo ServoCapit;
Servo ServoSikut;
Servo ServoLengan;
int PinSensor = A0; // Sensor (LDR) pada Pin Nomor A0
int PinLedMerah =3; // Led Warna Merah pada Pin Nomor 3
int PinLedHijau=4; // Led Warna Hijau pada Pin Nomor 4
int PinLedBiru=5; // Led Warna Biru pada Pin Nomor 5
int PinKonveyor=8; // Relay pada Pin Nomor 8
int Hasil,HasilMerah,HasilHijau,HasilBiru,sensorState;
int k=3;  // Toleransi Warna

void setup() {
// Menetapkan Pin Led Merah, Hijau, Biru sebagai OUTPUT:
  pinMode(PinLedMerah,OUTPUT);
  pinMode(PinLedHijau,OUTPUT);
  pinMode(PinLedBiru,OUTPUT); 
  pinMode(PinKonveyor,OUTPUT);
  digitalWrite(PinLedMerah,LOW);
  digitalWrite(PinLedHijau,LOW);
  digitalWrite(PinLedBiru,LOW);
  digitalWrite(PinKonveyor,LOW);
  ServoCapit.attach(9); // Menempatkan Servo Capit pada Pin Nomor 9
  ServoSikut.attach(10); // Menempatkan Servo Sikut pada Pin Nomor 10
  ServoLengan.attach(11); // Menempatkan Servo1 Lengan pada Pin Nomor 11 
  ServoCapit.write(15); // Menetapkan Putaran Awal Servo Capit pada Sudut 45 derajat      
  ServoSikut.write(30); // Menetapkan Putaran Awal Servo Sikut pada Sudut 120 derajat
  ServoLengan.write(5); // Menetapkan Putaran Awal Servo Lengan pada Sudut 0 derajat
  delay(100);      
  Serial.begin(9600);
  delay(1000);
}

void loop() {
   digitalWrite(PinLedMerah,HIGH); // Menyalakan Led Merah
   delay(150); // Jeda 150 milidetik agar LDR bisa Membaca Warna Merah dengan Stabil
// Membaca Data Sensor (LDR) :
   Hasil= analogRead(PinSensor);
   HasilMerah=map(Hasil,0,1023,0,255);
   Serial.print(HasilMerah);
   digitalWrite(PinLedMerah,LOW);   
   delay(150);

   digitalWrite(PinLedHijau,HIGH); // Menyalakan Led Hijau
   delay(150); // Jeda 150 milidetik agar LDR bisa Membaca Warna Hijau dengan Stabil
// Membaca Data Sensor (LDR) :
   Hasil= analogRead(PinSensor);
   HasilHijau=map(Hasil,0,1023,0,255); 
   Serial.print(" ");
   Serial.print(HasilHijau);
   digitalWrite(PinLedHijau,LOW);   
   delay(150);

   digitalWrite(PinLedBiru,HIGH); // Menyalakan Led Biru
   delay(150); // Jeda 150 milidetik agar LDR bisa Membaca Warna Biru dengan Stabil
// Membaca Data Sensor (LDR) :
   Hasil= analogRead(PinSensor);
   HasilBiru=map(Hasil,0,1023,0,255); 
   Serial.print(" ");
   Serial.println(HasilBiru);
   digitalWrite(PinLedBiru,LOW); 
   delay(150);

// Membandingkan Warna Hasil Peneraan Sensor dengan Hasil Kalibrasi :
 
  if(abs(HasilMerah-245)<k && abs(HasilHijau-235)<k && abs(HasilBiru-233)<k){
    Serial.println("WARNA MERAH\n");

    digitalWrite(PinKonveyor,HIGH);
    delay(1500);    
    ServoCapit.write(45); // Capit membuka
    delay(1000);
    digitalWrite(PinKonveyor, LOW);
    delay(500);    
    ServoSikut.write(40); // Sikut menurunkan capit menuju benda
    delay(1000);
    ServoCapit.write(15); // Capit menutup
    delay(1000);
    ServoSikut.write(8); // Sikut menaikan capit yg bawa benda  
    delay(1000);
    ServoLengan. write(120); // Lengan membawa benda ke tempat Warna Merah
    delay(1000);
    ServoSikut.write(30); // Sikut menurunkan capit pembawa benda menuju tempat benda  
    delay(1000); 
    ServoCapit.write(45); // Capit melepas benda
    delay(1000);
    ServoSikut.write(8); // Sikut mengangkat capit kosong
    delay(1000);
    ServoCapit.write(15); // Capit menutup (posisi istirahat)
    delay(1000);
    ServoLengan.write(5); // Lengan menuju posisi istirahat
    } else

   if(abs(HasilMerah-241)<k && abs(HasilHijau-243)<k && abs(HasilBiru-241)<k){
    Serial.println("WARNA BIRU\n");

    digitalWrite(PinKonveyor,HIGH);
    delay(1500);
    ServoCapit.write(45); // Capit membuka
    delay(1000);
    digitalWrite(PinKonveyor, LOW);
    delay(500);    
    ServoSikut.write(40); // Sikut menurunkan capit menuju benda
    delay(1000);
    ServoCapit.write(15); // Capit menutup
    delay(1000);
    ServoSikut.write(8); // Sikut menaikan capit yg bawa benda  
    delay(1000);
    ServoLengan.write(150); // Lengan membawa benda ke tempat Warna Biru
    delay(1000);
    ServoSikut.write(30); // Sikut menurunkan capit pembawa benda menuju tempat benda  
    delay(1000); 
    ServoCapit.write(45); // Capit melepas benda
    delay(1000);
    ServoSikut.write(8); // Sikut mengangkat capit kosong
    delay(1000);
    ServoCapit.write(15); // Capit menutup (posisi istirahat)
    delay(1000);
    ServoLengan.write(5); // Lengan menuju posisi istirahat
    
    }else

 if(abs(HasilMerah-238)<k && abs(HasilHijau-241)<k && abs(HasilBiru-238)<k){
    Serial.println("WARNA HIJAU\n");

    digitalWrite(PinKonveyor,HIGH);
    delay(1500);    
    ServoCapit.write(45); // Capit membuka
    delay(1000);
    digitalWrite(PinKonveyor, LOW);
    delay(500);    
    ServoSikut.write(40 ); // Sikut menurunkan capit menuju benda
    delay(1000);
    ServoCapit.write(15); // Capit menutup
    delay(1000);
    ServoSikut.write(8); // Sikut menaikan capit yg bawa benda  
    delay(1000);
    ServoLengan.write(180); // Lengan membawa benda ke tempat Warna Hijau
    delay(1000);
    ServoSikut.write(30); // Sikut menurunkan capit pembawa benda menuju tempat benda  
    delay(1000); 
    ServoCapit.write(45); // Capit melepas benda
    delay(1000);
    ServoSikut.write(8); // Sikut mengangkat capit kosong
    delay(1000);
    ServoCapit.write(15); // Capit menutup (posisi istirahat)
    delay(1000);
    ServoLengan.write(5 ); // Lengan menuju posisi istirahat
    } else

    Serial.println("Warna Tidak Dikenal\n");    
   
  delay (2000);
}
