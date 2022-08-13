/*
* TUGAS AKHIR
* " SISTEM PENGUKUR DEBIT AIR DENGAN KOMUNIKASI LORA
* UNTUK USAHA AIR MINUM ISI ULANG "
* DISUSUN OLEH : 
* 1. MARISKA ERLIN MAULINA (3.32.18.0.11)
* 2. YUSTINUS NOVIAN NINO PANDEGA BHAKTI (3.32.18.0.24)
* TAHUN 2021
*/

#include <Arduino.h>            //Deklarasi pustaka arduino
#include <Wire.h>               //Deklarasi pustaka wire
#include <SPIFFS.h>             //Deklarasi pustaka penyimpanan mikrokontroler
#include <LiquidCrystal_I2C.h>  //Deklarasi pustaka tampilan kristal cair dengan I2C
#include "RTClib.h"             //Deklarasi pustaka sistem waktu nyata
#include <Ticker.h>             //Deklarasi pustaka ticker
#include <Wire.h>               // Deklarasi pustaka wire
#include "send_data.h"          //Deklarasi pustaka pengiriman LoRa
//======== Deklarasi Pin SENSOR Hc-sr04 ==========================
const byte Echo = 39;           //Deklarasi pin ultrasonik
const byte Trig = 13;           //Deklarasi pin ultrasonik
long echotime;
float distance;                 //Deklarasi perhitungan desimal
float volume;                   //Deklarasi nilai volume
//======== Deklarasi Pin SENSOR AIR ==============================
#define FLOW_METER_PIN 16       //Deklarasi pin sensor laju aliran air
//======== Deklarasi Pin BUZZER ==================================
#define BUZZER 17               //Deklarasi pin buzzer
//======== Deklarasi Pin TUAS KENDALI ============================
#define Button 4                //Deklarasi pin tombol tuas kendali
#define VRY 2                   //Deklarasi pin sumbu Y
#define VRX 15                  //Deklarasi pin sumbu X
//======== Deklarasi Pin TUAS KENDALI ============================
#define ok digitalRead(Button) == 0     //Deklarasi nilai gerak tombol
#define atas analogRead(VRY) >= 3000    //Deklarasi nilai gerak sumbu Y atas
#define bawah analogRead(VRY) <= 1000   //Deklarasi nilai gerak sumbu Y bawah
#define kiri analogRead(VRX) >= 3000    //Deklarasi nilai gerak sumbu X kiri
#define kanan analogRead(VRX) <= 1000   //Deklarasi nilai gerak sumbu X kanan
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);     //inisialisasi LCD 20x4
RTC_DS1307 rtc;                         //inisialisasi RTC ds1307
DateTime now;                           //inisialisasi waktu sekarang
Ticker timerDebit;                      //eksekusi fungsi setiap 1 detik menghitung rpm
Ticker timerLora;                       //eksekusi fungsi 1 detik pengiriman Lora
char isi = 0;                           //menyimpan karakter berupa angka
int data;                               //mendeklarasi data
void menu();                            //deklarasi fungsi menu
void modelora();                        //deklarsi menu lora
void aturwaktu();                       //deklarasi menu aturwaktu
void aturtanggal();                     //deklarasi menu aturtanggal
void aturulang();                       //deklarasi mengatur ulang data
void kirim_1menit();                    //deklarasi pengiriman tiap 1 menit
void kirim_2menit();                    //deklarasi pengiriman tiap 2 menit
void kirim_5menit();                    //deklarasi pengiriman tiap 5 menit
void kirim_10menit();                   //deklarasi pengiriman tiap 10 menit
void set_tanggal();                     //deklarasi untuk mengatur tanggal
void set_bulan();                       //deklarasi untuk mengatur bulan
void set_tahun();                       //deklarasi untuk mengatur tahun
void set_jam();                         //deklarasi untuk mengatur jam
void set_menit();                       //deklarasi untuk mengatur menit
void hitungVolume();                    //deklarasi untuk menghitung volume tandon
void hitungDebit();                     //deklarasi untuk menghitung laju aliran air
void aturulang_ya();                    //deklarasi mengatur ulang data
void ICACHE_RAM_ATTR pulseCounter();    //deklarasi
void sendLoraData();                    //deklarasi pengiriman data Lora
unsigned long pulse_sample;             //penyimpanan bilangan yang diperluas dan menyimpan 32bit
double vtotal, literPerDet;             //implementasi data ganda

unsigned int timerTickLora;             

int intervalKirim = 1;                  //menyimpan pengiriman 1 menit sebagai pengaturan awal
float vtotal_akhir;                     //tampil angka dalam bentuk desimal

void setup()
{
  pinMode(BUZZER, OUTPUT);              //memfungsikan buzzer sebagai luaran

  // INIT SPIFFS
  if (!SPIFFS.begin(true))              //inisialisasi penyimpanan mikrokontroler
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  File file = SPIFFS.open("/volume.txt"); //file pada penyimpanan 
  if (file)
  {
    vtotal = file.readString().toFloat();
  }
  file.close();
  Serial.begin(115200);                   //meneampilakan pada serial monitor
  loraSetup();                            //memanggil fungsi lorastup
  rtc.begin();                            //memanggil library rtc
  lcd.begin();                            //memanggil library lcd
  lcd.backlight();                        //fungsi menyalakan lampu belakang lcd
  lcd.setCursor(0, 0);                    //mengatur letak prin karakter lcd pada sumbu x=0 , sumbu y=0
  lcd.print(" SISTEM  PENGUKURAN ");
  lcd.setCursor(0, 1);                    //mengatur letak prin karakter lcd pada sumbu x=0 , sumbu y=1
  lcd.print(" DEBIT  AIR  DENGAN ");
  lcd.setCursor(0, 2);                    //mengatur letak prin karakter lcd pada sumbu x=0 , sumbu y=2
  lcd.print("  KOMUNIKASI  LORA  ");
  lcd.setCursor(0, 3);                    //mengatur letak prin karakter lcd pada sumbu x=0 , sumbu y=3
  lcd.print("  UNTUK USAHA  AIR  ");
  delay(4000);                            //karakter muncul selama 4 detik
  lcd.clear();                            //menghapus layar lcd
  lcd.setCursor(0, 0);                    //mengatur letak prin karakter lcd pada sumbu x=0 , sumbu y=0
  lcd.print(" DEBIT  AIR  DENGAN ");
  lcd.setCursor(0, 1);                    //mengatur letak prin karakter lcd pada sumbu x=0 , sumbu y=1
  lcd.print("  KOMUNIKASI  LORA  ");
  lcd.setCursor(0, 2);                    //mengatur letak prin karakter lcd pada sumbu x=0 , sumbu y=2
  lcd.print("  UNTUK USAHA  AIR  ");
  lcd.setCursor(0, 3);                    //mengatur letak prin karakter lcd pada sumbu x=0 , sumbu y=3
  lcd.print("  MINUM  ISI ULANG  ");
  delay(4000);                            //karakter muncul selama 4 detik
  lcd.clear();                            //menghapus layar lcd
  pinMode(Button, INPUT_PULLUP);          //memfungsikan tombol terhubung dengan vcc
  pinMode(VRY, INPUT);                    //memfungsikan tuas kendali sumbu Y sebagai masukan
  pinMode(VRX, INPUT);                    //memfungsikan tuas kendali sumbu x sebagai masukan
  pinMode(FLOW_METER_PIN, INPUT_PULLUP);  //memfungsikan sensor laju aliran air terhubung dengan vcc
  attachInterrupt(digitalPinToInterrupt(FLOW_METER_PIN), pulseCounter, FALLING);  //pengesetan pin intterupt
  timerDebit.attach(1, hitungDebit);      //eksekusi menghitung debit 
  timerLora.attach_ms(900, sendLoraData); //eksekusi pengiriman data dengan lora
  pinMode(Echo, INPUT);                   //memfungsikan echo sebagai masukan
  pinMode(Trig, OUTPUT);                  //memfungsiakn trigger sebagai luaran
}

void loop()
{
  unsigned long info_millis = millis();   //inisialisasi parameter millis
  while (1)
  {
    ///////////Tampilkan Waktu RTC pada LCD//////////////
    if (millis() - info_millis > 1000)    //menjalankan fungsi dalam interval 1 detik
    {
      now = rtc.now();                    //inisialisasi waktu dan tanggal saat ini
      lcd.clear();                        //menghapus karakter pada layar lcd
      lcd.setCursor(0, 0);                //mengatur letak prin karakter lcd pada sumbu x=0 , sumbu y=0
      lcd.print(now.day(), DEC);          //menampilkan hari saat ini pada lcd
      lcd.print('/');                     //menampilkan pembatas
      lcd.print(now.month(), DEC);        //menampilkan bulan saat ini pada lcd
      lcd.print('/');                     //menampikan pembatas
      lcd.print(now.year(), DEC);         //menampilkan tahun saat ini pada lcd
      lcd.setCursor(12, 0);               //mengatur letak prin karakter lcd pada sumbu x=12 , sumbu y=0
      lcd.print(now.hour(), DEC);         //menampilkan jam saat ini pada lcd
      lcd.print(':');                     //menampilkan pembatas
      lcd.print(now.minute(), DEC);       //menampilkan menit saat ini pada lcd
      lcd.print(':');                     //menampilkan pembatas
      lcd.print(now.second(), DEC);       //menampilkan detik saat ini pada lcd
      ////// Tampilkan Waktu RTC pada Serial Monitor //////
      Serial.print(now.hour(), DEC);      //menampilkan jam saat ini pada serial monitor
      Serial.print(':');                  //menampilkan pembatas
      Serial.print(now.minute(), DEC);    //menampilkan menit saat ini pada serial monitor
      Serial.print(':');                  //menampilkan pembatas
      Serial.print(now.second(), DEC);    //menampilkan detik saat ini pada serial monitor
      Serial.print(" ");                  //memberikan jarak spasi
      Serial.print(now.day(), DEC);       //menampilkan hari saat ini pada serial monitor
      Serial.print('/');                  //menampilkan pembatas
      Serial.print(now.month(), DEC);     //menampilkan bulan saat ini pada serial monitor
      Serial.print('/');                  //menampilkan pembatas
      Serial.println(now.year(), DEC);    //menampilkan tahun saat ini pada serial monitor
      ////// Tampilan Data Sensor pada LCD ///////////////
      lcd.setCursor(0, 1);                //mengatur letak prin karakter lcd pada sumbu x=0 , sumbu y=1
      lcd.print("Debit   : " + (String)literPerDet + " L"); //menampilkan perhitungan debit air pada lcd
      lcd.setCursor(0, 2);                //mengatur letak prin karakter lcd pada sumbu x=0 , sumbu y=2
      lcd.print("Vtotal  : " + (String)vtotal + " L");  //menampilkan Vtotal dari debit yang mengalir pada lcd
      lcd.setCursor(0, 3);                //mengatur letak prin karakter lcd pada sumbu x=0 , sumbu y=3
      lcd.print("Vtandon : " + (String)volume + " L");  //menampilkan volume tandon pada lcd
      if ((volume > 135) || (volume < 30))   //pengaturan buzzer berbunyi saat air diatas 135L dan dibawah 30L
      {
        digitalWrite(BUZZER, !digitalRead(BUZZER));  //pembacaan buzzer hidup atau mati
      }
      else digitalWrite(BUZZER, LOW);
      info_millis = millis();                        //menjalankan fungsi dalam interval 1 detik
    }
    if (ok)              //Klik tombol tuas kendali untuk masuk Menu
    {
      while (ok);
      lcd.clear();
      delay(200);
      menu();
      break;
    }
  }
}

void ICACHE_RAM_ATTR pulseCounter()       //penempatan fungsi pada  RAM
{
  pulse_sample++;
}

////// Program sensor laju aliran air ///////////////////
void hitungDebit()
{
  literPerDet = pulse_sample / 7.5 / 60;      //rumus menghitung liter per detik (a)
  pulse_sample = 0;                           
  vtotal += literPerDet;                      //kalkulasi vtotal berdasarkan debit air yang mengalir (a+ = b)
  Serial.printf("Debit : %.2f , VTotal : %.2f\n", literPerDet, vtotal);  //menampilkan debit dan vtotal air pada serial monitor
  File f = SPIFFS.open("/volume.txt", FILE_WRITE);    //penyimpanan data pada mikrokontroler
  f.print(vtotal);
  f.close();
  hitungVolume();       //pemanggilan fungsi hitung volume tandon
}

////// Program sensor ultrasonik mencari volume ///////////
void hitungVolume()
{
  digitalWrite(Trig, HIGH);          //mengeluarkan sinyal
  delayMicroseconds(10);             //jeda dalam microsecond
  digitalWrite(Trig, LOW);           //tidak mengeluarkan sinyal
  echotime = pulseIn(Echo, HIGH);    //menerima sinyal terus menerus
  distance = 0.0001 * ((float)echotime * 340.0) / 2.0;    //rumus mencari jarak dalam cm
  Serial.print(distance);                          //menampilkan nilai jarak pada serial monitor
  Serial.print(" cm ,");                           //menampilkan satuan cm
  volume = 1699.34 * (86.05 - distance) / 1000.00; //rumus volume tendon Luas alas * Tinggi / 1000
  Serial.print(volume);                            //menampilkan nilai volume tandon pada serial monitor
  Serial.print(" L ");                             //menampilkan satuan liter
}

////// Program pengiriman LoRa /////////////////////////////
void sendLoraData()
{
  if (now.second() == 0 && (now.minute() % intervalKirim) == 0) //interval pengiriman
  {
    if (vtotal > vtotal_akhir + 0.01)                           //Data terkirim jika terjadi perubahan
    {
      kirimData(vtotal, volume);                                //data yang dikirim dengan lora
      vtotal_akhir = vtotal;
      delay(1300);                                              //dalam 1 detik mengirim 1 data
    }
  }
}

void menu()                                     //menu utama
{
  //lcd.clear();

  while (1)                                     //perulangan
  {
    //print_cursor(0,0,"      Menu      ");
    if (atas){while (atas);isi = isi + 1;}      //penambahan nilai isi untuk merubah case menu
    if (bawah){while (bawah);isi = isi - 1;}    //pengurangan nilai isi untuk merubah case menu
    isi = constrain(isi, 0, 3);                 //batasan nilai isi 0-3
    switch (isi)                                //pindah isi
    {
    case 0:                                               //tampilan case 0 pada LCD
      lcd.setCursor(0, 0); lcd.print(">Pilih Mode     "); //menampilkan karakter pada sumbu x=0 dan y=0
      lcd.setCursor(0, 1); lcd.print(" Atur Waktu     "); //menampilkan karakter pada sumbu x=0 dan y=1
      lcd.setCursor(0, 2); lcd.print(" Atur Tanggal   "); //menampilkan karakter pada sumbu x=0 dan y=2
      lcd.setCursor(0, 3); lcd.print(" Atur Ulang     "); //menampilkan karakter pada sumbu x=0 dan y=3
      if (ok){ while (ok); lcd.clear();modelora();}       //tekan tombol tuas kendali untuk ke fungsi modelora
      break;
    case 1:                                               //tampilan case 1 pada LCD
      lcd.setCursor(0, 0); lcd.print(" Pilih Mode     "); //menampilkan karakter pada sumbu x=0 dan y=0
      lcd.setCursor(0, 1); lcd.print(">Atur Waktu     "); //menampilkan karakter pada sumbu x=0 dan y=1
      lcd.setCursor(0, 2); lcd.print(" Atur Tanggal   "); //menampilkan karakter pada sumbu x=0 dan y=2
      lcd.setCursor(0, 3); lcd.print(" Atur Ulang     "); //menampilkan karakter pada sumbu x=0 dan y=3
      if (ok){while (ok); lcd.clear(); aturwaktu();}      //tekan tombol tuas kendali untuk ke fungsi atur waktu
      break;
    case 2:                                               //tampilan case 2 pada LCD
      lcd.setCursor(0, 0); lcd.print(" Pilih Mode     "); //menampilkan karakter pada sumbu x=0 dan y=0
      lcd.setCursor(0, 1); lcd.print(" Atur Waktu     "); //menampilkan karakter pada sumbu x=0 dan y=1
      lcd.setCursor(0, 2); lcd.print(">Atur Tanggal   "); //menampilkan karakter pada sumbu x=0 dan y=2
      lcd.setCursor(0, 3); lcd.print(" Atur Ulang     "); //menampilkan karakter pada sumbu x=0 dan y=3
      if (ok){while (ok); lcd.clear(); aturtanggal();}    //tekan tombol tuas kendali untuk ke fungsi aturtanggal
      break;
    case 3:                                               //tampilan case 3 pada LCD
      lcd.setCursor(0, 0); lcd.print(" Pilih Mode     "); //menampilkan karakter pada sumbu x=0 dan y=0
      lcd.setCursor(0, 1); lcd.print(" Atur Waktu     "); //menampilkan karakter pada sumbu x=0 dan y=1
      lcd.setCursor(0, 2); lcd.print(" Atur Tanggal   "); //menampilkan karakter pada sumbu x=0 dan y=2
      lcd.setCursor(0, 3); lcd.print(">Atur Ulang     "); //menampilkan karakter pada sumbu x=0 dan y=3
      if (ok){while (ok); lcd.clear(); aturulang();}      //tekan tombol tuas kendali untuk ke fungsi atur ulang
      break;
    }
  }
}

void modelora()                                           //menu mode pengiriman lora
{
  while (1)                                               //perulangan
  {
    //print_cursor(0,0,"      Menu      ");
    if (atas){while (atas); isi = isi + 1;}               //penambahan nilai isi untuk merubah case menu
    if (bawah){while (bawah); isi = isi - 1;}             //pengurangan nilai isi untuk merubah case menu
    isi = constrain(isi, 0, 3);                           //batasan nilai isi 0-3
    switch (isi)                                          //pindah isi
    {
    case 0:                                               //tampilan case 0 pada lcd
      lcd.setCursor(0, 0); lcd.print(">Kirim/1  Menit "); //menampilkan karakter pada sumbu x=0 dan y=0
      lcd.setCursor(0, 1); lcd.print(" Kirim/2  Menit "); //menampilkan karakter pada sumbu x=0 dan y=1
      lcd.setCursor(0, 2); lcd.print(" Kirim/5  Menit "); //menampilkan karakter pada sumbu x=0 dan y=2
      lcd.setCursor(0, 3); lcd.print(" Kirim/10 Menit "); //menampilkan karakter pada sumbu x=0 dan y=3
      if (ok){while (ok); lcd.clear(); kirim_1menit();}   //tekan tombol tuas kendali untuk ke fungsi kirim per 1 menit
      break;
    case 1:                                               //tampilan case 1 pada lcd
      lcd.setCursor(0, 0); lcd.print(" Kirim/1  Menit "); //menampilkan karakter pada sumbu x=0 dan y=0
      lcd.setCursor(0, 1); lcd.print(">Kirim/2  Menit "); //menampilkan karakter pada sumbu x=0 dan y=1
      lcd.setCursor(0, 2); lcd.print(" Kirim/5  Menit "); //menampilkan karakter pada sumbu x=0 dan y=2
      lcd.setCursor(0, 3); lcd.print(" Kirim/10 Menit "); //menampilkan karakter pada sumbu x=0 dan y=3
      if (ok){while (ok); lcd.clear() ;kirim_2menit();}   //tekan tombol tuas kendali untuk ke fungsi kirim per 2 menit
      break;
    case 2:                                               //tampilan case 2 pada lcd
      lcd.setCursor(0, 0); lcd.print(" Kirim/1  Menit "); //menampilkan karakter pada sumbu x=0 dan y=0
      lcd.setCursor(0, 1); lcd.print(" Kirim/2  Menit "); //menampilkan karakter pada sumbu x=0 dan y=1
      lcd.setCursor(0, 2); lcd.print(">Kirim/5  Menit "); //menampilkan karakter pada sumbu x=0 dan y=2
      lcd.setCursor(0, 3); lcd.print(" Kirim/10 Menit "); //menampilkan karakter pada sumbu x=0 dan y=3
      if (ok){while (ok); lcd.clear(); kirim_5menit();}   //tekan tombol tuas kendali untuk ke fungsi kirim per 5 menit
      break;
    case 3:                                               //tampilan case 3 pada lcd
      lcd.setCursor(0, 0); lcd.print(" Kirim/1  Menit "); //menampilkan karakter pada sumbu x=0 dan y=0
      lcd.setCursor(0, 1); lcd.print(" Kirim/2  Menit "); //menampilkan karakter pada sumbu x=0 dan y=1
      lcd.setCursor(0, 2); lcd.print(" Kirim/5  Menit "); //menampilkan karakter pada sumbu x=0 dan y=2
      lcd.setCursor(0, 3); lcd.print(">Kirim/10 Menit "); //menampilkan karakter pada sumbu x=0 dan y=3
      if (ok){while (ok); lcd.clear(); kirim_10menit();}  //tekan tombol tuas kendali untuk ke fungsi kirim per 10 menit 
      break;
    }
  }
}

void aturtanggal()                                         //menu atur tanggal
{
  while (1)                                                //perulangan
  {
    //print_cursor(0,0,"      Menu      ");
    if (atas){while (atas); isi = isi + 1;}                //penambahan nilai isi untuk merubah case menu
    if (bawah){while (bawah); isi = isi - 1;}              //pengurangan nilai isi untuk merubah case menu
    isi = constrain(isi, 0, 3);                            //batasan nilai isi 0-3
    switch (isi)                                           //pindah isi
    {
    case 0:                                                //tampilan case 0 pada lcd
      lcd.setCursor(0, 0); lcd.print(">Set Tanggal     "); //menampilkan karakter pada sumbu x=0 dan y=0
      lcd.setCursor(0, 1); lcd.print(" Set Bulan       "); //menampilkan karakter pada sumbu x=0 dan y=1
      lcd.setCursor(0, 2); lcd.print(" Set Tahun       "); //menampilkan karakter pada sumbu x=0 dan y=2
      lcd.setCursor(0, 3); lcd.print(" Kembali         "); //menampilkan karakter pada sumbu x=0 dan y=3`
      if (ok){while (ok); lcd.clear(); set_tanggal();}     //tekan tombol tuas kendali untuk ke fungsi atur tanggal
      break;
    case 1:                                                //tampilan case 1 pada lcd
      lcd.setCursor(0, 0); lcd.print(" Set Tanggal     "); //menampilkan karakter pada sumbu x=0 dan y=0
      lcd.setCursor(0, 1); lcd.print(">Set Bulan       "); //menampilkan karakter pada sumbu x=0 dan y=1
      lcd.setCursor(0, 2); lcd.print(" Set Tahun       "); //menampilkan karakter pada sumbu x=0 dan y=2
      lcd.setCursor(0, 3); lcd.print(" Kembali         "); //menampilkan karakter pada sumbu x=0 dan y=3
      if (ok){while (ok); lcd.clear(); set_bulan();}       //tekan tombol tuas kendali untuk ke fungsi atur bulan
      break;
    case 2:                                                //tampilan case 2 pada lcd
      lcd.setCursor(0, 0); lcd.print(" Set Tanggal     "); //menampilkan karakter pada sumbu x=0 dan y=0
      lcd.setCursor(0, 1); lcd.print(" Set Bulan       "); //menampilkan karakter pada sumbu x=0 dan y=1
      lcd.setCursor(0, 2); lcd.print(">Set Tahun       "); //menampilkan karakter pada sumbu x=0 dan y=2
      lcd.setCursor(0, 3); lcd.print(" Kembali         "); //menampilkan karakter pada sumbu x=0 dan y=3
      if (ok){while (ok); lcd.clear(); set_tahun();}       //tekan tombol tuas kendali untuk ke fungsi atur tahun
      break;
    case 3:                                                //tampilan case 3 pada lcd
      lcd.setCursor(0, 0); lcd.print(" Set Tanggal     "); //menampilkan karakter pada sumbu x=0 dan y=0
      lcd.setCursor(0, 1); lcd.print(" Set Bulan       "); //menampilkan karakter pada sumbu x=0 dan y=1
      lcd.setCursor(0, 2); lcd.print(" Set Tahun       "); //menampilkan karakter pada sumbu x=0 dan y=2
      lcd.setCursor(0, 3); lcd.print(">Kembali         "); //menampilkan karakter pada sumbu x=0 dan y=3
      if (ok){while (ok); lcd.clear(); loop();}            //tekan tombol tuas kendali untuk ke fungsi kembali halaman utama
      break;
    }
  }
}

void aturwaktu()                                           //menu atur waktu
{
  while (1)                                                //perulangan
  {
    //print_cursor(0,0,"      Menu      ");
    if (atas){while (atas); isi = isi + 1;}                //penambahan nilai isi untuk merubah case menu
    if (bawah){while (bawah); isi = isi - 1;}              //pengurangan nilai isi untuk merubah case menu
    isi = constrain(isi, 0, 2);                            //batasan nilai isi 0-2
    switch (isi)                                           //pindah isi
    {
    case 0:                                                //tampilan case 0 pada lcd
      lcd.setCursor(0, 0); lcd.print(">Set Jam         "); //menampilkan karakter pada sumbu x=0 dan y=0
      lcd.setCursor(0, 1); lcd.print(" Set Menit       "); //menampilkan karakter pada sumbu x=0 dan y=1
      lcd.setCursor(0, 2); lcd.print(" Kembali         "); //menampilkan karakter pada sumbu x=0 dan y=2
      if (ok){while (ok); lcd.clear(); set_jam();}         //tekan tombol tuas kendali untuk ke fungsi atur jam
      break;
    case 1:                                                //tampilan case 1 pada lcd
      lcd.setCursor(0, 0); lcd.print(" Set Jam         "); //menampilkan karakter pada sumbu x=0 dan y=0
      lcd.setCursor(0, 1); lcd.print(">Set Menit       "); //menampilkan karakter pada sumbu x=0 dan y=1
      lcd.setCursor(0, 2); lcd.print(" Kembali         "); //menampilkan karakter pada sumbu x=0 dan y=2
      if (ok){while (ok); lcd.clear(); set_menit();}       //tekan tombol tuas kendali untuk ke fungsi atur menit
      break;
    case 2:                                                //tampilan case 2 pada lcd
      lcd.setCursor(0, 0); lcd.print(" Set Jam         "); //menampilkan karakter pada sumbu x=0 dan y=0
      lcd.setCursor(0, 1); lcd.print(" Set Menit       "); //menampilkan karakter pada sumbu x=0 dan y=1
      lcd.setCursor(0, 2); lcd.print(">Kembali         "); //menampilkan karakter pada sumbu x=0 dan y=2
      if (ok){while (ok); lcd.clear(); loop();}            //tekan tombol tuas kendali untuk ke fungsi ke halaman utama
      break;
    }
  }
}

void aturulang()                                           //menu atur ulang data
{
  while (1)                                                //perulangan
  {
    //print_cursor(0,0,"      Menu      ");
    if (atas){while (atas); isi = isi + 1;}                //penambahan nilai isi untuk merubah case menu
    if (bawah){while (bawah); isi = isi - 1;}              //pengurangan nilai isi untuk merubah case menu
    isi = constrain(isi, 0, 1);                            //batasan nilai isi 0-1
    switch (isi)                                           //pindah isi
    {
    case 0:                                                //tampilan case 2 pada lcd
      lcd.setCursor(0, 0); lcd.print("Atur ulang data? "); //menampilkan karakter pada sumbu x=0 dan y=0
      lcd.setCursor(0, 1); lcd.print(">YA              "); //menampilkan karakter pada sumbu x=0 dan y=1
      lcd.setCursor(0, 2); lcd.print(" TIDAK           "); //menampilkan karakter pada sumbu x=0 dan y=2
      if (ok){while (ok); lcd.clear(); aturulang_ya();}    //tekan tombol tuas kendali untuk ke fungsi ke konfirmasi atur ulang
      break;
    case 1:                                                //tampilan case 2 pada lcd
      lcd.setCursor(0, 0); lcd.print("Atur ulang data? "); //menampilkan karakter pada sumbu x=0 dan y=0
      lcd.setCursor(0, 1); lcd.print(" YA              "); //menampilkan karakter pada sumbu x=0 dan y=1
      lcd.setCursor(0, 2); lcd.print(">TIDAK           "); //menampilkan karakter pada sumbu x=0 dan y=2
      if (ok){while (ok); lcd.clear(); loop();}            //tekan tombol tuas kendali untuk ke fungsi ke halaman utama
      break;
    }
  }
}

////// Program pengaturan RTC secara manual dengan tuas kendali///////////
void set_tanggal()                                                        //fungsi pengaturan tanggal
{
  DateTime now = rtc.now();                                               //inisialisasi waktu dan tanggal saat ini
  data = now.day();                                                       //deklarasi data sebagai tanggal
  while (true)                                                            //perulangan
  {
    if (atas){while (atas); data = data - 1;}                             //penambahan nilai data untuk merubah angka
    if (bawah){while (bawah); data = data + 1;}                           //penambahan nilai isi untuk merubah angka
    data = constrain(data, 1, 31);                                        //pembatasan nilai data 1-31
    lcd.clear();                                                          //menghapus karakter pada lcd
    lcd.setCursor(0, 0);                                                  //menampilkan karakter pada sumbu x=0 dan y=0
    lcd.print("Set Tanggal :");                                           //karakter yang ditampilkan
    lcd.setCursor(15, 0);                                                 //menampilkan karakter pada sumbu x=15 dan y=0
    lcd.print(data, DEC);                                                 //nilai data tanggal
    delay(100);                                                           //jeda 100 milidetik
    if (ok){while (ok); rtc.adjust(DateTime(now.year(), now.month(), data,//pengesetan ulang data tanggal yabg sudah diatur
    now.hour(), now.minute(), now.second())); lcd.clear(); aturtanggal();
    }
  }
}

void set_bulan()                                                           //fungsi pengaturan bulan
{
  DateTime now = rtc.now();                                                //inisialisasi waktu dan tanggal saat ini
  data = now.month();                                                      //deklarasi data sebagai bulan
  while (true)                                                             //perulangan
  {
    if (atas){while (atas); data = data - 1;}                              //penambahan nilai data untuk merubah angka
    if (bawah){while (bawah); data = data + 1;}                            //pengurangan nilai data untuk merubah angka
    data = constrain(data, 1, 12);                                         //pembatasan nilai data 1-12
    lcd.clear();                                                           //menghapus karakter pada lcd
    lcd.setCursor(0, 0);                                                   //menampilkan karakter pada sumbu x=0 dan y=0
    lcd.print("Set Bulan :");                                              //karakter yang ditampilkan
    lcd.setCursor(13, 0);                                                  //menampilkan karakter pada sumbu x=13 dan y=0
    lcd.print(data, DEC);                                                  //nilai data bulan
    delay(100);                                                            //jeda 100 milidetik
    if (ok){while (ok); rtc.adjust(DateTime(now.year(), data, now.day(),   //pengesetan ulang data bulan yang sudah diatur
    now.hour(), now.minute(), now.second())); lcd.clear(); aturtanggal();
    }
  }
}

void set_tahun()                                                            //fungsi pengaturan tahun
{                                                               
  DateTime now = rtc.now();                                                 //inisialisasi waktu dan tanggal saat ini
  data = now.year();                                                        //deklarasi data sebagai tahun
  while (true)                                                              //perulangan
  {
    if (atas){while (atas); data = data - 1;}                               //penambahan nilai data untuk merubah angka
    if (bawah){ while (bawah); data = data + 1;}                            //pengurangan nilai data untuk merubah angka
    lcd.clear();                                                            //menghapus karakter pada lcd
    lcd.setCursor(0, 0);                                                    //menampilkan karakter pada sumbu x=0 dan y=0
    lcd.print("Set Tahun :");                                               //karakter yang ditampilkan
    lcd.setCursor(13, 0);                                                   //menampilkan karakter pada sumbu x=14 dan y=0
    lcd.print(data, DEC);                                                   //nilai data tahun
    delay(100);                                                             //jeda 100 milidetik
    if (ok){while (ok); rtc.adjust(DateTime(data, now.month(), now.day(),   //pengesetan ulang data tahun yang sudah diatur
    now.hour(), now.minute(), now.second())); lcd.clear(); aturtanggal();
    }
  }
}

void set_jam()                                                               //fungsi pengaturan jam
{
  DateTime now = rtc.now();                                                  //inisialisasi waktu dan tanggal saat ini
  data = now.hour();                                                         //deklarasi data sebagai tahun
  while (true)                                                               //perulangan
  {
    if (atas){while (atas); data = data - 1;}                                //penambahan nilai data untuk merubah angka
    if (bawah){ while (bawah); data = data + 1;}                             //penambahan nilai data untuk merubah angka
    data = constrain(data, 0, 23);                                           //pembatasan nilai data 0-23
    lcd.clear();                                                             //menghapus karakter pada lcd
    lcd.setCursor(0, 0);                                                     //menampilkan karakter pada sumbu x=0 dan y=0
    lcd.print("Set Jam :");                                                  //karakter yang ditampilkan
    lcd.setCursor(11, 0);                                                    //menampilkan karakter pada sumbu x=11 dan y=0
    lcd.print(data, DEC);                                                    //nilai data jam
    delay(100);                                                              //jeda 100 milidetik
    if (ok){ while (ok); rtc.adjust(DateTime(now.year(), now.month(), now.day(), //pengesetan ulang data jam yang sudah diatur
    data, now.minute(), now.second())); lcd.clear(); aturwaktu();
    }
  }
}

void set_menit()                                                              //fungsi pengaturan menit
{
  DateTime now = rtc.now();                                                   //inisialisasi waktu dan tanggal saat ini
  data = now.minute();                                                        //deklarasi data sebagai menit
  while (true)                                                                //perulangan
  {
    if (atas){while (atas); data = data - 1;}                                 //penambahan nilai data untuk merubah angka
    if (bawah){while (bawah); data = data + 1;}                               //pengurangan nilai data untuk merubah angka
    data = constrain(data, 0, 59);                                            //pembatasan nilai data 0-59
    lcd.clear();                                                              //menghapus karakter pada lcd
    lcd.setCursor(0, 0);                                                      //menampilkan karakter pada sumbu x=0 dan y=0
    lcd.print("Set Menit :");                                                 //karakter yang ditampilkan
    lcd.setCursor(13, 0);                                                     //menampilkan karakter pada sumbu x=13 dan y=0
    lcd.print(data, DEC);                                                     //nilai data menit
    delay(100);                                                               //jeda 100 milidetik
    if (ok){while (ok); rtc.adjust(DateTime(now.year(), now.month(), now.day(), //pengesetan ulang data menit yang sudah diatur
    now.hour(), data, now.second())); lcd.clear(); aturwaktu();
    }
  }
}

////// Program atur ulang memori mikrokontroler /////////////////////
void aturulang_ya()                                       //fungsi konfirmasi atur ulang
{
  Serial.println("Atur ulang");                           //menampilkan pada serial monitor
  File f = SPIFFS.open("/volume.txt", FILE_WRITE);        //penyimpanan mikrokontroler
  vtotal = 0;                                             //pengaturan 0 pada penyimpanan mikrokontroler
  f.print(vtotal);                                        //alamat yang dituju
  f.close();                                              //tutup
  lcd.clear();
  delay(200);
  loop();
}

////// Program menu pengiriman mode LoRa ////////////////////////
void kirim_1menit()
{
  intervalKirim = 1;               //data interval kirim ketika waktu dibagi 1 = 0
  // simpanInterval(intervalKirim);
  loop();
}

void kirim_2menit()
{
  intervalKirim = 2;               //data interval kirim ketika waktu dibagi 2 = 0
  // simpanInterval(intervalKirim);
  loop();
}

void kirim_5menit()
{
  intervalKirim = 5;                //data interval kirim ketika waktu dibagi 5 = 0
  // simpanInterval(intervalKirim);
  loop();
}

void kirim_10menit()
{
  intervalKirim = 10;               //data interval kirim ketika waktu dibagi 10 = 0
  // simpanInterval(intervalKirim);
  loop();
}