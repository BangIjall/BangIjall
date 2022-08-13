#include <esp_now.h>
#include <WiFi.h>

#define uS_TO_S_FACTOR 1000000UL
#define TIME_TO_SLEEP  10

int kondisi;

//ISI DENGAN PERBANDINGAN R NILAI KECIL DIBAGI R TOTAL
float perbandingan = 60.00;

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

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
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

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  // register peer
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  // register first peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  test.humA1 = 0;
  test.humA2 = 0;
  test.humB1 = 0;
  test.humB2 = 0;
  test.temp1 = 0;
  test.temp2 = 0;
  test.vltg = (analogRead(13) * (3.30 / 4095.00)) * perbandingan;

  //koding pengiriman harus ada di paling bawah
  if (kondisi == 2) {
    esp_err_t result = esp_now_send(0, (uint8_t *) &test, sizeof(test));
    kondisi = 0;
    if (result == ESP_OK) {
      Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }
  }

  delay(1000);
}
