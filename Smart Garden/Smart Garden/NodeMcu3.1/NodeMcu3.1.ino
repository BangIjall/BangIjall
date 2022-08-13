#include <CTBot.h>
#include <CTBotInlineKeyboard.h>
#include <SoftwareSerial.h>

SoftwareSerial NodemcuSerial(13, 15);

CTBotReplyKeyboard Tbl;
CTBotInlineKeyboard TbLpotomatison, TbLpotomatisoff, TbLptomaton, TbLpbayamon, TbLplavenderon, TbLptomatoff, TbLpbayamoff, TbLplavenderoff, TbLpsistemoff;

String ssid = "Al -Firdaus";
String pass = "12345678";
String token = "5598447248:AAEW0gO4AgjWSyg2_8iyN9weFe1c6RQ1p78";
//const int id = 1198952505;

CTBot myBot;

//delete
#define Otomatis_ON  "Otomatis_ON"
#define Otomatis_OFF  "Otomatis_OFF"
#define Tomat_ON "Tomat_ON"
#define Tomat_OFF "Tomat_OFF"
#define Bayam_ON "Bayam_ON"
#define Bayam_OFF "Bayam_OFF"
#define Lavender_ON "Lavender_ON"
#define Lavender_OFF "Lavender_OFF"
#define Sistem_OFF  "Sistem_OFF"
#define Tidak  "Tidak"

String pesan;
String dataIn;
String x;
String tanki;

String statusOtomatis;
String statusTomat;
String statusBayam;
String statusLavender;

String soil1;
String soil2;
String soil3;
String soil4;
String soil5;
String soil6;
String soil7;
String soil8;
String soil9;
String flow1;
String flow2;
String flow3;
String distance;

bool tomat = false;
bool otomatisss = false;
bool bayam = false;
bool lavender = false;

int pesanOtomatis = 11;
int pesanTomat = 22;
int pesanBayam = 33;
int pesanLavender = 44;
int pesanParam = 55;
int pesanOff = 66;
int pesanStatus = 77;

int index1, index2, index3, index4, index5, index6, index7, index8, index9, index10, index11, index12, index13, index14, index15, index16;
int indexA, indexB, indexC, indexD;

//penampung data dari Arduino
String arrayData[14];

bool TampilkanTombol;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  NodemcuSerial.begin(4800);
  Serial.println("Starting Bot");

  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);

  if (myBot.testConnection())
    Serial.println("Koneksi Berhasil");
  else
    Serial.println("Koneksi Gagal");

  Tbl.addButton("Otomatis");
  Tbl.addRow();
  Tbl.addButton("Tomat");
  Tbl.addButton("Bayam");
  Tbl.addButton("Lavender");
  Tbl.addRow();
  Tbl.addButton("Sistem OFF");
  Tbl.addRow();
  Tbl.addButton("Cek Status");
  Tbl.addButton("Cek Parameter");
  Tbl.enableResize();
  TampilkanTombol = false;

  TbLpotomatison.addButton("✅ Ya", Otomatis_ON, CTBotKeyboardButtonQuery);
  TbLpotomatison.addButton("❌ Tidak", Tidak, CTBotKeyboardButtonQuery);

  TbLptomaton.addButton("✅ Ya", Tomat_ON, CTBotKeyboardButtonQuery);
  TbLptomaton.addButton("❌ Tidak", Tidak, CTBotKeyboardButtonQuery);

  TbLpbayamon.addButton("✅ Ya", Bayam_ON, CTBotKeyboardButtonQuery);
  TbLpbayamon.addButton("❌ Tidak", Tidak, CTBotKeyboardButtonQuery);

  TbLplavenderon.addButton("✅ Ya", Lavender_ON, CTBotKeyboardButtonQuery);
  TbLplavenderon.addButton("❌ Tidak", Tidak, CTBotKeyboardButtonQuery);

  TbLptomatoff.addButton("✅ Ya", Tomat_OFF, CTBotKeyboardButtonQuery);
  TbLptomatoff.addButton("❌ Tidak", Tidak, CTBotKeyboardButtonQuery);

  TbLpbayamoff.addButton("✅ Ya", Bayam_OFF, CTBotKeyboardButtonQuery);
  TbLpbayamoff.addButton("❌ Tidak", Tidak, CTBotKeyboardButtonQuery);

  TbLplavenderoff.addButton("✅ Ya", Lavender_OFF, CTBotKeyboardButtonQuery);
  TbLplavenderoff.addButton("❌ Tidak", Tidak, CTBotKeyboardButtonQuery);

  TbLpsistemoff.addButton("✅ Ya", Sistem_OFF, CTBotKeyboardButtonQuery);
  TbLpsistemoff.addButton("❌ Tidak", Tidak, CTBotKeyboardButtonQuery);
}

void loop() {
  TBMessage msg ;
  if (myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("/start")) {
      myBot.sendMessage(msg.sender.id, "Halo...\nSelamat Datang Di SmaGaBot.\n\nGunakan tombol dibawah untuk mengontrol Sistem Smart Garden 👇", Tbl);
      //Serial.println("\nUser memulai Bot \n");
      TampilkanTombol = true;
    }
    else if (msg.text.equalsIgnoreCase("Otomatis")) {
      //      NodemcuSerial.print("Sistem OFF");
      myBot.sendMessage(msg.sender.id, "Apakah anda ingin menyalakan Otomatis?", TbLpotomatison);
    }

    else if (msg.text.equalsIgnoreCase("Tomat")) {
      if (tomat) {
        //        NodemcuSerial.print("Tomat");
        myBot.sendMessage(msg.sender.id, "Saat ini Tomat dalam keadaan ON\nApakah anda ingin mematikan Tomat?", TbLptomatoff);
      }
      else {
        myBot.sendMessage(msg.sender.id, "Saat ini Tomat dalam keadaan OFF\nApakah anda ingin menyalakan Tomat?", TbLptomaton);
      }
    }
    else if (msg.text.equalsIgnoreCase("Bayam")) {
      if (bayam) {
        //        NodemcuSerial.print("Bayam");
        myBot.sendMessage(msg.sender.id, "Saat ini Bayam dalam keadaan ON\nApakah anda ingin mematikan Bayam?", TbLpbayamoff);
      }
      else {
        myBot.sendMessage(msg.sender.id, "Saat ini Bayam dalam keadaan OFF\nApakah anda ingin menyalakan Bayam?", TbLpbayamon);
      }
    }
    else if (msg.text.equalsIgnoreCase("Lavender")) {
      if (lavender) {
//        NodemcuSerial.print("Lavender");
        myBot.sendMessage(msg.sender.id, "Saat ini Lavender dalam keadaan ON\nApakah anda ingin mematikan Lavender?", TbLplavenderoff);
      }
      else {
        myBot.sendMessage(msg.sender.id, "Saat ini Lavender dalam keadaan OFF\nApakah anda ingin menyalakan Lavender?", TbLplavenderon);
      }
    }
    else if (msg.text.equalsIgnoreCase("Sistem OFF")) {
      //      NodemcuSerial.print("Sistem OFF");
      myBot.sendMessage(msg.sender.id, "Apakah anda ingin mematikan Sistem?", TbLpsistemoff);
    }


    else if (msg.text.equalsIgnoreCase("Cek Status")) {
      Serial.print('@');
      NodemcuSerial.print('@');
      Serial.print(',');
      NodemcuSerial.print(',');
      Serial.print("pesanStatus");
      NodemcuSerial.print(pesanStatus);
      Serial.print(',');
      NodemcuSerial.print(',');
      Serial.print('#');
      NodemcuSerial.print('#');
      Serial.println(" ");
      NodemcuSerial.print(" ");
      parsingStatus();
      
      if (tomat) statusTomat = "Tomat ON";
      else statusTomat = "Tomat OFF";
      if (bayam) statusBayam = "Bayam ON";
      else statusBayam = "Bayam OFF";
      if (lavender) statusLavender = "Lavender ON";
      else statusLavender = "Lavender OFF";
      
      if (tomat && bayam && lavender) myBot.sendMessage(msg.sender.id, "Status saat ini : \n\n👉 Otomatis ON \n\n👉 " + tanki + "\n\n👉 " + statusTomat + "\n\n👉 " + statusBayam + "\n\n👉 " + statusLavender, Tbl);
      else myBot.sendMessage(msg.sender.id, "Status saat ini : \n\n👉 Otomatis OFF \n\n👉 " + tanki + "\n\n👉 " + statusTomat + "\n\n👉 " + statusBayam + "\n\n👉 " + statusLavender, Tbl);
    }

    else if (msg.text.equalsIgnoreCase("Cek Parameter")) {
      //Serial.println("Cek Parameter");
      //      NodemcuSerial.println("Cek Parameter");
      Serial.print('@');
      NodemcuSerial.print('@');
      Serial.print(',');
      NodemcuSerial.print(',');
      Serial.print("pesanParam");
      NodemcuSerial.print(pesanParam);
      Serial.print(',');
      NodemcuSerial.print(',');
      Serial.print('#');
      NodemcuSerial.print('#');
      Serial.println(" ");
      NodemcuSerial.print(" ");
      parsingData();
      myBot.sendMessage(msg.sender.id, "Parameter saat ini : \n\n👉 Soil1 : " + soil1 + "\n\n👉 Soil2 : " + soil2 + "\n\n👉 Soil3 : " + soil3 + "\n\n👉 Soil4 : " + soil4 + "\n\n👉 Soil5 : " + soil5 + "\n\n👉 Soil6 : " + soil6 + "\n\n👉 Soil7 : " + soil7 + "\n\n👉 Soil8 : " + soil8 + "\n\n👉 Soil9 : " + soil9 + "\n\n👉 Flow1 : " + flow1 + "\n\n👉 Flow2 : " + flow2 + "\n\n👉 Flow3 : " + flow3 + "\n\n👉 distance : " + distance, Tbl);
    }

    else if (msg.messageType == CTBotMessageQuery) {
      if (msg.callbackQueryData.equals(Otomatis_ON)) {
        //       Serial.println("Sistem OFF");
        Serial.print('@');
        NodemcuSerial.print('@');
        Serial.print(',');
        NodemcuSerial.print(',');
        Serial.print("11");
        NodemcuSerial.print(pesanOtomatis);
        Serial.print(',');
        NodemcuSerial.print(',');
        Serial.print('#');
        NodemcuSerial.print('#');
        Serial.println(" ");
        NodemcuSerial.print(" ");
        myBot.sendMessage(msg.sender.id, "Otomatis Telah Dinyalakan");
        tomat = true;
        bayam = true;
        lavender = true;
      }
      else if (msg.callbackQueryData.equals(Tomat_ON)) {
        Serial.print('@');
        NodemcuSerial.print('@');
        Serial.print(',');
        NodemcuSerial.print(',');
        Serial.print("22");
        NodemcuSerial.print(pesanTomat);
        Serial.print(',');
        NodemcuSerial.print(',');
        Serial.print('#');
        NodemcuSerial.print('#');
        Serial.println(" ");
        NodemcuSerial.print(" ");
        //Serial.println("Tomat ON");
        //        NodemcuSerial.println("Tomat ON");
        myBot.sendMessage(msg.sender.id, "🚫 Tomat Telah Dinyalakan");
        tomat = true;
      }
      else if (msg.callbackQueryData.equals(Tomat_OFF)) {
        Serial.print('@');
        NodemcuSerial.print('@');
        Serial.print(',');
        NodemcuSerial.print(',');
        Serial.print("pesanTomat");
        NodemcuSerial.print(pesanTomat);
        Serial.print(',');
        NodemcuSerial.print(',');
        Serial.print('#');
        NodemcuSerial.print('#');
        Serial.println(" ");
        NodemcuSerial.print(" ");
        //Serial.println("Tomat OFF");
        //        NodemcuSerial.println("Tomat OFF");
        myBot.sendMessage(msg.sender.id, "💡 Tomat Telah Dimatikan");
        tomat = false;
      }
      else if (msg.callbackQueryData.equals(Bayam_ON)) {
        Serial.print('@');
        NodemcuSerial.print('@');
        Serial.print(',');
        NodemcuSerial.print(',');
        Serial.print("pesanBayam");
        NodemcuSerial.print(pesanBayam);
        Serial.print(',');
        NodemcuSerial.print(',');
        Serial.print('#');
        NodemcuSerial.print('#');
        Serial.println(" ");
        NodemcuSerial.print(" ");
        //Serial.println("Bayam ON");
        //        NodemcuSerial.println("Bayam ON");
        myBot.sendMessage(msg.sender.id, "🚫 Bayam Telah Dinyalakan");
        bayam = true;
      }
      else if (msg.callbackQueryData.equals(Bayam_OFF)) {
        Serial.print('@');
        NodemcuSerial.print('@');
        Serial.print(',');
        NodemcuSerial.print(',');
        Serial.print("pesanBayam");
        NodemcuSerial.print(pesanBayam);
        Serial.print(',');
        NodemcuSerial.print(',');
        Serial.print('#');
        NodemcuSerial.print('#');
        Serial.println(" ");
        NodemcuSerial.print(" ");
        //Serial.println("Bayam OFF");
        //        NodemcuSerial.println("Bayam OFF");
        myBot.sendMessage(msg.sender.id, "🚫 Bayam Telah Dimatikan");
        bayam = false;
      }
      else if (msg.callbackQueryData.equals(Lavender_ON)) {
        //Serial.println("Lavender ON");
        Serial.print('@');
        NodemcuSerial.print('@');
        Serial.print(',');
        NodemcuSerial.print(',');
        Serial.print("pesanLavender");
        NodemcuSerial.print(pesanLavender);
        Serial.print(',');
        NodemcuSerial.print(',');
        Serial.print('#');
        NodemcuSerial.print('#');
        Serial.println(" ");
        NodemcuSerial.print(" ");
        //        NodemcuSerial.println("Lavender ON");
        myBot.sendMessage(msg.sender.id, "🚫 Lavender Telah Dinyalakan");
        lavender = true;
      }
      else if (msg.callbackQueryData.equals(Lavender_OFF)) {
        //Serial.println("Lavender OFF");
        Serial.print('@');
        NodemcuSerial.print('@');
        Serial.print(',');
        NodemcuSerial.print(',');
        Serial.print("pesanLavender");
        NodemcuSerial.print(pesanLavender);
        Serial.print(',');
        NodemcuSerial.print(',');
        Serial.print('#');
        NodemcuSerial.print('#');
        Serial.println(" ");
        NodemcuSerial.print(" ");
        myBot.sendMessage(msg.sender.id, "🚫 Lavender Telah Dimatikan");
        lavender = false;
      }
      else if (msg.callbackQueryData.equals(Sistem_OFF)) {
        // Serial.println("Sistem OFF");
        Serial.print('@');
        NodemcuSerial.print('@');
        Serial.print(',');
        NodemcuSerial.print(',');
        Serial.print("pesanOff");
        NodemcuSerial.print(pesanOff);
        Serial.print(',');
        NodemcuSerial.print(',');
        Serial.print('#');
        NodemcuSerial.print('#');
        Serial.println(" ");
        NodemcuSerial.print(" ");
        myBot.sendMessage(msg.sender.id, "🚫 Sistem Telah Dimatikan");
        tomat = false;
        bayam = false;
        lavender = false;
      }
      else if (msg.callbackQueryData.equals(Tidak)) {
        myBot.sendMessage(msg.sender.id, "❌ Perintah Telah Dibatalkan!!!");
        Serial.println("Tidak");
      }
    }
    else {
      myBot.sendMessage(msg.sender.id, "⛔️ ERROR: Perintah tidak dikenal?!\n\nGunakan tombol dibawah untuk mengontrol lampu 👇", Tbl);
    }
  }
}

//  NodemcuSerial.println();
//Menerima Data dari Arduino

//  if (NodemcuSerial.available() > 0)
//  {
//    c = NodemcuSerial.read();
//    Serial.println(pesan);
//    if (pesan == "Otomatis ON")
//    {
//      myBot.sendMessage(msg.sender.id, "Sistem Otomatis Telah Dinyalakan");
//    }
//    else if (pesan == "Tomat ON")
//    {
//      myBot.sendMessage(msg.sender.id, "Tomat Sudah ON");
//    }
//    else if (pesan == "Bayam ON")
//    {
//      myBot.sendMessage(msg.sender.id, "Bayam Sudah ON");
//    }
//    else if (pesan == "Lavender ON")
//    {
//      myBot.sendMessage(msg.sender.id, "Lavender Sudah ON");
//    }
//    else if (pesan == "Sistem OFF")
//    {
//      myBot.sendMessage(msg.sender.id, "Sistem Sudah OFF");
//    }
//    else if (pesan == "Tomat OFF")
//    {
//      myBot.sendMessage(msg.sender.id, "Tomat Sudah OFF");
//    }
//    else if (pesan == "Bayam OFF")
//    {
//      myBot.sendMessage(msg.sender.id, "Bayam Sudah OFF");
//    }
//    else if (pesan == "Lavender OFF")
//    {
//      myBot.sendMessage(msg.sender.id, "Lavender Sudah OFF");
//    }
//    else
//    {
//      int index = 0;
//      for (int i = 0; i < pesan.length(); i++)
//      {
//        char delimiter = '\n'; //pembatas data yang masuk
//        if (pesan[i] != delimiter)
//        { //jika data i tidak sama dengan delimiter
//          arrayData[index] += pesan[i];  // maka dianggap sebagai isi data index ke i
//        }
//        else {    //jika data berupa delimiter (#) index nambah
//          index++;
//        }
//      }
//      if (index == 13)
//      {
//
//        myBot.sendMessage(msg.sender.id, "Parameter Saat ini :\n\n Soil Moisture 1 : " + arrayData[0] + "\n" +
//                          "Soil Moisture 2 : " + arrayData[2] + "\n" +
//                          "Soil Moisture 3 : " + arrayData[2] + "\n" +
//                          "Soil Moisture 4 : " + arrayData[3] + "\n" +
//                          "Soil Moisture 5 : " + arrayData[4] + "\n" +
//                          "Soil Moisture 6 : " + arrayData[5] + "\n" +
//                          "Soil Moisture 7 : " + arrayData[6] + "\n" +
//                          "Soil Moisture 8 : " + arrayData[7] + "\n" +
//                          "Soil Moisture 9 : " + arrayData[8] + "\n" +
//                          "Water Flow 1 : " + arrayData[9] + "\n" +
//                          "Water Flow 2 : " + arrayData[10] + "\n" +
//                          "Water Flow 3 : " + arrayData[11] + "\n" +
//                          "Ultrasonik : " + arrayData[12] + "\n" +
//
//        Serial.print("Parameter Saat Ini: ");
//        Serial.println(arrayData[0] + "\n" + arrayData[1] + "\n" + arrayData[2] + "\n" + arrayData[3] + "\n" + arrayData[4] + "\n" + arrayData[5] + "\n" +
//                       arrayData[6] + "\n" + arrayData[7] + "\n" + arrayData[8] + "\n" + arrayData[9] + "\n" + arrayData[10] + "\n" + arrayData[11] + "\n" + arrayData[12]);
//      }
//
//        arrayData[0] = "" ;
//        arrayData[1] = "" ;
//        arrayData[2] = "" ;
//        arrayData[3] = "" ;
//        arrayData[4] = "" ;
//        arrayData[5] = "" ;
//        arrayData[6] = "" ;
//        arrayData[7] = "" ;
//        arrayData[8] = "" ;
//        arrayData[9] = "" ;
//        arrayData[10] = "" ;
//        arrayData[11] = "" ;
//        arrayData[12] = "" ;
//    }
//  }
//}

void parsingData() {
  while (NodemcuSerial.available() <= 0);
  while (NodemcuSerial.available() > 0)
  {
    dataIn = NodemcuSerial.readString();
    if (dataIn.length() > 0) {
      index1 = dataIn.indexOf('@');
      index2 = dataIn.indexOf(',', index1 + 1);
      index3 = dataIn.indexOf(',', index2 + 1);
      index4 = dataIn.indexOf(',', index3 + 1);
      index5 = dataIn.indexOf(',', index4 + 1);
      index6 = dataIn.indexOf(',', index5 + 1);
      index7 = dataIn.indexOf(',', index6 + 1);
      index8 = dataIn.indexOf(',', index7 + 1);
      index9 = dataIn.indexOf(',', index8 + 1);
      index10 = dataIn.indexOf(',', index9 + 1);
      index11 = dataIn.indexOf(',', index10 + 1);
      index12 = dataIn.indexOf(',', index11 + 1);
      index13 = dataIn.indexOf(',', index12 + 1);
      index14 = dataIn.indexOf(',', index13 + 1);
      index15 = dataIn.indexOf(',', index14 + 1);
      index16 = dataIn.indexOf('#', index15 + 1);
    }
  }

  soil1 = dataIn.substring(index2 + 1, index3);
  soil2 = dataIn.substring(index3 + 1, index4);
  soil3 = dataIn.substring(index4 + 1, index5);
  soil4 = dataIn.substring(index5 + 1, index6);
  soil5 = dataIn.substring(index6 + 1, index7);
  soil6 = dataIn.substring(index7 + 1, index8);
  soil7 = dataIn.substring(index8 + 1, index9);
  soil8 = dataIn.substring(index9 + 1, index10);
  soil9 = dataIn.substring(index10 + 1, index11);
  flow1 = dataIn.substring(index11 + 1, index12);
  flow2 = dataIn.substring(index12 + 1, index13);
  flow3 = dataIn.substring(index13 + 1, index14);
  distance = dataIn.substring(index14 + 1, index15);

  Serial.println(soil1);
  Serial.println(soil2);
  Serial.println(soil3);
  Serial.println(soil4);
  Serial.println(soil5);
  Serial.println(soil6);
  Serial.println(soil7);
  Serial.println(soil8);
  Serial.println(soil9);
  Serial.println(flow1);
  Serial.println(flow2);
  Serial.println(flow3);
  Serial.println(distance);
}

void parsingStatus() {
  while (NodemcuSerial.available() <= 0);
  while (NodemcuSerial.available() > 0)
  {
    x = NodemcuSerial.readString();
    if (x.length() > 0) {
      indexA = x.indexOf('@');
      indexB = x.indexOf(',', indexA + 1);
      indexC = x.indexOf(',', indexB + 1);
      indexD = x.indexOf('#', indexC + 1);
    }
  }

  tanki = x.substring(indexB + 1, indexC);
  Serial.println(tanki);
}
