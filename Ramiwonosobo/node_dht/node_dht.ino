#include <espnow.h>
#include <ESP8266WiFi.h>

#define uS_TO_S_FACTOR 1000000UL
#define TIME_TO_SLEEP  10

int kondisi;

// REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS 94:3C:C6:7B:4B:70
uint8_t broadcastAddress[] = {0x94, 0x3C, 0xC6, 0x7B, 0x4B, 0x70};

typedef struct test_struct {
  int humA1;
  int humA2;
  int humB1;
  int humB2;
  float temp1;
  float temp2;
  float vltg;
  int titik;
} test_struct;

typedef struct status_struct {
  int kirim;
} status_struct;

test_struct test;

status_struct pesan;

//esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&pesan, incomingData, sizeof(pesan));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("pesan: ");
  Serial.println(pesan.kirim);
  kondisi = pesan.kirim;
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

  esp_now_register_send_cb(OnDataSent);

  // register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  test.vltg = 0;
  test.titik = 1;
  //variabel yg diisi
  test.humA1 = random(0, 20);
  test.humA2 = random(0, 20);
  test.humB1 = random(0, 20);
  test.humB2 = random(0, 20);
  test.temp1 = random(0, 20);
  test.temp2 = random(0, 20);


  //koding pengiriman harus ada di paling bawah
  if (kondisi == 1) {
    esp_now_send(broadcastAddress, (uint8_t *) &test, sizeof(test));
    kondisi = 0;
  }

  delay(1000);
}
