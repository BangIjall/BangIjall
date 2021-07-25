// Blynk Auth
char auth[] = "fGRrWq8zl2v9n3tV6mUJ_7E_0M2XfRSA";

// GPS
#define TXPin 6
#define RXPin 3

// Blutut
#define BLUETOOTH_TX_PIN 10
#define BLUETOOTH_RX_PIN 11

// Motor
#define MOTOR_A_EN_PIN 5
#define MOTOR_B_EN_PIN 9
#define MOTOR_A_IN_1_PIN 7
#define MOTOR_A_IN_2_PIN 8
#define MOTOR_B_IN_1_PIN 12
#define MOTOR_B_IN_2_PIN 4

// Kalibrasi kecepatan
#define MOTOR_A_OFFSET 30
#define MOTOR_B_OFFSET 0

// Kalibrasi sudut kompas
#define DECLINATION_ANGLE 0.23f

#define COMPASS_OFFSET 0.0f


#define GPS_UPDATE_INTERVAL 1000


#define GPS_STREAM_TIMEOUT 18


#define GPS_WAYPOINT_TIMEOUT 45

// Struct Utama
struct GeoLoc {
  float lat;
  float lon;
};
