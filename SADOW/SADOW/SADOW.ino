//pustaka 
#include <ESP8266WiFi.h>     //pustaka untuk WiFi                        
#include <ThingerESP8266.h>  //pustaka web yang akan digunakan                       
#include <Wire.h>            //pustaka untuk komunikasi I2C 


#define SDA_PIN 4                             //pin SDA pada D2
#define SCL_PIN 5                             //pin SCL pada D1
#define enA     12                            //pin D6 pada enable A
#define enB     14                            //pin D5 pada enable B
#define USERNAME "BangIjal"                   //Username pada akun web
#define DEVICE_ID "NodeMCU"                   //device yg digunakan
#define DEVICE_CREDENTIAL "ifIXPDbC%bH31yNO"  //API key
#define SSID "OPPO A3s"                       //Hotspot yang kita pakai
#define SSID_PASSWORD "modal dikit dong"      //password hotspot yg dipakai

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

byte _ADDR = 0x0D;
int _vRaw[3] = {0,0,0};

int pulsa = 0;
float rps, rpm;
int jumlahPulsa, lastjumlahPulsa;
int interval = 1000;
unsigned int waktulama, waktusekarang;
void ICACHE_RAM_ATTR encoder();

int dir, A;
float spd;
void setup() {
  Serial.begin(9600);
  
  Wire.begin(SDA_PIN, SCL_PIN);       
  _writeReg(0x0B,0x01);
  _setMode(0x01,0x0C,0x10,0X00);

  pinMode(enA, INPUT_PULLUP);
  pinMode(enB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(enA), encoder, FALLING);

  thing.add_wifi(SSID, SSID_PASSWORD);

  thing["SADOW"] >> [](pson & out) {
    out["direction"] = dir;
    out["speed"] = spd;
  };
}

void loop() {
  thing.handle();

  waktusekarang = millis();
  if ((waktusekarang - waktulama) >= interval) {
    baca();

    A = getAzimuth();
    rps = (jumlahPulsa / 100.00);
    rpm = (rps * 60)*0.02789734276387736;
    pulsa = 0;
    jumlahPulsa = 0;
    waktulama = waktusekarang;
  }

  dir = A;
  spd = rpm;
}


void ICACHE_RAM_ATTR encoder()
{
  if (digitalRead(enB) == 1)
  {
    pulsa++;
  }
  else
  {
    pulsa--;
  }
  jumlahPulsa = pulsa;
}

void baca() {
  Wire.beginTransmission(_ADDR);
  Wire.write(0x00);
  int err = Wire.endTransmission();
  if (!err) {
    Wire.requestFrom(_ADDR, (byte)6);
    _vRaw[0] = (int)(int16_t)(Wire.read() | Wire.read() << 8); //X
    _vRaw[1] = (int)(int16_t)(Wire.read() | Wire.read() << 8); //Y
    _vRaw[2] = (int)(int16_t)(Wire.read() | Wire.read() << 8); //Z
  }
}

void _writeReg(byte r, byte v){
  Wire.beginTransmission(_ADDR);
  Wire.write(r);
  Wire.write(v);
  Wire.endTransmission();
}

void _setMode(byte mode, byte odr, byte rng, byte osr){
  _writeReg(0x09,mode|odr|rng|osr);
}

int getAzimuth(){
  int a = atan2( _vRaw[1], _vRaw[0] ) * 180.0 / PI;
  return a < 0 ? 360 + a : a;
}
