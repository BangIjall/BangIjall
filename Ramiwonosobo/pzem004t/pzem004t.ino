#include <SoftwareSerial.h>

#define PZEM_DEFAULT_ADDR     0xF8
#define UPDATE_TIME           200
#define READ_TIMEOUT          100
#define CMD_RIR               0X04

float voltage();
float current();
uint8_t _addr;   // Device address
struct {
  float voltage;
  float current;
  float power;
  float energy;
  float frequeny;
  float pf;
  uint16_t alarms;
}  _currentValues; // Measured values
uint64_t _lastRead; // Last time values were updated
void init(uint8_t addr); // Init common to all constructors
bool updateValues();    // Get most up to date values from device registers and cache them
uint16_t recieve(uint8_t *resp, uint16_t len); // Receive len bytes into a buffer
bool sendCmd8(uint8_t cmd, uint16_t rAddr, uint16_t val, bool check = false, uint16_t slave_addr = 0xFFFF); // Send 8 byte command
void setCRC(uint8_t *buf, uint16_t len);           // Set the CRC for a buffer
bool checkCRC(const uint8_t *buf, uint16_t len);   // Check CRC of buffer
uint16_t CRC16(const uint8_t *data, uint16_t len);
uint8_t addr=PZEM_DEFAULT_ADDR;

SoftwareSerial pzem(32, 33);

void setup() {
  Serial.begin(9600);
  pzem.begin(9600);
  init(addr);
}

void loop() {
  float tegangan = voltage();
  if ( !isnan(tegangan) ) {
    Serial.print("Voltage: "); Serial.print(tegangan); Serial.println("V");
  } else {
    Serial.println("Error reading voltage");
  }

  float arus = current();
  if ( !isnan(arus) ) {
    Serial.print("Current: "); Serial.print(arus); Serial.println("A");
  } else {
    Serial.println("Error reading current");
  }

  Serial.println();
  delay(2000);
}
