 #include <Servo.h>
Servo ServoMerah;
Servo ServoHijau;
int PinSensor = A0; // Sensor (LDR) pada Pin Nomor A0
int PinLedMerah =3; // Led Warna Merah pada Pin Nomor 3
int PinLedHijau=4; // Led Warna Hijau pada Pin Nomor 4
int PinLedBiru=5; // Led Warna Biru pada Pin Nomor 5
int PinKonveyor=8;
int Hasil,HasilMerah,HasilHijau,HasilBiru;
int k=2;  // Toleransi Warna

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
  ServoMerah.attach(6); // Menempatkan Servo Merah pada Pin Nomor 6
  ServoHijau.attach(7); // Menempatkan Servo Hijau pada Pin Nomor 7
  ServoMerah.write(0); // Menetapkan Putaran Awal Servo Capit pada Sudut 0 derajat      
  ServoHijau.write(0); // Menetapkan Putaran Awal Servo Sikut pada Sudut 0 derajat
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

  if(abs(HasilMerah-249)<k && abs(HasilHijau-249)<k && abs(HasilBiru-249)<k){
    Serial.println("WARNA MERAH\n");

    ServoMerah.write(90); // Servo membelokkan conveyor
    digitalWrite(PinKonveyor,HIGH);
    delay(3000);
    ServoMerah.write(0); // Servo kembali ke posisi awal
    digitalWrite(PinKonveyor,LOW);
    delay(1000);
    
  } else

 if(abs(HasilMerah-242)<k && abs(HasilHijau-245)<k && abs(HasilBiru-244)<k){
    Serial.println("WARNA HIJAU\n");

    ServoHijau.write(90); // Servo membelokkan conveyor
    digitalWrite(PinKonveyor,HIGH);
    delay(6000);
    ServoHijau.write(0); // Servo kembali ke posisi awal
    digitalWrite(PinKonveyor,LOW);
    delay(1000);
  }else

 if(abs(HasilMerah-246)<k && abs(HasilHijau-247)<k && abs(HasilBiru-246)<k){
    Serial.println("WARNA BIRU\n");

    
    digitalWrite(PinKonveyor,HIGH);
    delay(9000);
    digitalWrite(PinKonveyor,LOW);
    delay(1000);
  }else

  Serial.println("Warna Tidak Dikenal\n");     
  delay (2000);

}
