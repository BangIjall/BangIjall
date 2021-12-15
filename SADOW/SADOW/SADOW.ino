#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>
#include <Wire.h>
//#include <QMC5883LCompass.h>

//QMC5883LCompass compass;

#define enA 12
#define enB 14
#define USERNAME "BangIjal" //Username thinger.io
#define DEVICE_ID "NodeMCU"
#define DEVICE_CREDENTIAL "ifIXPDbC%bH31yNO"

#define SSID "OPPO A3s" //Hotspot yang kita pakai
#define SSID_PASSWORD "modal dikit dong"

#define SDA_PIN 4
#define SCL_PIN 5

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

const int16_t I2C_MASTER = 0x42;
const int16_t I2C_SLAVE = 0x08;
byte _ADDR = 0x0D;
int _vRaw[3] = {0,0,0};
int _get(int index);

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
  //compass.init();
  
  Wire.begin(SDA_PIN, SCL_PIN);        // join i2c bus (address optional for master)
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
    //compass.read();
    baca();

    A = getAzimuth();
    Serial.print("A: ");
    Serial.print(dir);
    Serial.println();
    rps = (jumlahPulsa / 100.00);
    // rpm = (jumlahPulsa/360.00)/0.00833333;
    rpm = (rps * 60); //*0.02789734276387736;
    Serial.print("Banyaknya Pulsa: ");
    Serial.print(jumlahPulsa);
    Serial.print("t");
    Serial.print("Rotasi Per Detik :");
    Serial.print(rps);
    Serial.print("t");
    Serial.print("Rotasi Per Menit :");
    Serial.println(rpm);
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
