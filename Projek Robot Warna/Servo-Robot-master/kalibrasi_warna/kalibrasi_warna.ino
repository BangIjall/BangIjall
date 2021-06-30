int PinSensor = A0; // Sensor (LDR) pada Pin Nomor A0
int PinLedMerah =3; // Led Warna Merah pada Pin Nomor 3
int PinLedHijau=4; // Led Warna Hijau pada Pin Nomor 4
int PinLedBiru=5; // Led Warna Biru pada Pin Nomor 5
int Hasil,HasilMerah,HasilHijau,HasilBiru;

void setup() {
// Menetapkan Pin Led Merah, Hijau, Biru sebagai OUTPUT:
  pinMode(PinLedMerah,OUTPUT); 
  pinMode(PinLedHijau,OUTPUT);
  pinMode(PinLedBiru,OUTPUT); 
  digitalWrite(PinLedMerah,LOW);
  digitalWrite(PinLedHijau,LOW);
  digitalWrite(PinLedBiru,LOW);

  Serial.begin(9600);
  delay(1000);

  Serial.println("  R   G   B");
  Serial.println("--- --- ---");

}

void loop() {

   digitalWrite(PinLedMerah,HIGH); // Menyalakan Led Merah
   delay(150); // Jeda 150 mili detik agar LDR bisa Membaca Warna Merah
// Membaca Data Sensor (LDR) :
   Hasil= analogRead(PinSensor);
   HasilMerah=map(Hasil,0,1023,0,255);
   Serial.print(HasilMerah);
   digitalWrite(PinLedMerah,LOW);   
   delay(150);

   digitalWrite(PinLedHijau,HIGH); // Menyalakan Led Hijau
   delay(150); // Jeda 150 mili detik agar LDR bisa Membaca Warna Hijau
// Membaca Data Sensor (LDR) :
   Hasil= analogRead(PinSensor);
   HasilHijau=map(Hasil,0,1023,0,255); 
   Serial.print(" ");
   Serial.print(HasilHijau);
   digitalWrite(PinLedHijau,LOW);   
   delay(150);

   digitalWrite(PinLedBiru,HIGH); // Menyalakan Led Biru
   delay(150); // Jeda 150 mili detik agar LDR bisa Membaca Warna Biru
// Membaca Data Sensor (LDR) :
   Hasil= analogRead(PinSensor);
   HasilBiru=map(Hasil,0,1023,0,255); 
   Serial.print(" ");
   Serial.println(HasilBiru);
   digitalWrite(PinLedBiru,LOW); 
   delay(150);
}
