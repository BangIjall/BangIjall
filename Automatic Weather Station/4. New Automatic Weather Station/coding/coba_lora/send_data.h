////// Program penghubung LoRa dengan ANTARES.id Web Telkom/////////////////
#include <lorawan.h>
//ABP Credentials
const char *devAddr = "3988e799";
const char *nwkSKey = "d8dfb2cd21120db00000000000000000";
const char *appSKey = "0000000000000000477636d3358c0f46";

const unsigned long interval = 10000; // 10 s interval to send message
unsigned long previousMillis = 0;     // will store last time message sent
unsigned int counter = 0;             // message counter

const sRFM_pins RFM_pins = {
    .CS = 18,
    .RST = 14,
    .DIO0 = 26,
    .DIO1 = 33,
};

void loraSetup()
{
    if (!lora.init())
    {
        Serial.println("RFM95 not detected");
        delay(5000);
        return;
    }

    // Set LoRaWAN Class change CLASS_A or CLASS_C
    lora.setDeviceClass(CLASS_C);               // pengaturan LORAWAN

    // Set Data Rate
    lora.setDataRate(SF10BW125);                //pengaturan data rate

    // Set FramePort Tx
    lora.setFramePortTx(5);                     //pengaturan frame port

    // set channel to random
    lora.setChannel(MULTI);                     //pengaturan chanel

    // Set TxPower to 15 dBi (max)
    lora.setTxPower(15);                        //pengaturan txtower

    // Put ABP Key and DevAddress here
    lora.setNwkSKey(nwkSKey);
    lora.setAppSKey(appSKey);
    lora.setDevAddr(devAddr);
}

void kirimData(float volume, float tandon)
{
    char myStr[50];
    byte outStr[50];
    byte recvStatus = 0;
    int port, channel, freq;
    bool newmessage = false;
    sprintf(myStr, "%.2f,%.2f", volume, tandon); //data yang dikirim dengan lora

    Serial.print("Sending: ");                   //tampilan pada serial monitor
    Serial.println(myStr);
    lora.sendUplink(myStr, strlen(myStr), 0);
    port = lora.getFramePortTx();
    channel = lora.getChannel();
    freq = lora.getChannelFreq(channel);
    Serial.print(F("fport: "));
    Serial.print(port);
    Serial.print(" ");
    Serial.print(F("Ch: "));
    Serial.print(channel);
    Serial.print(" ");
    Serial.print(F("Freq: "));
    Serial.print(freq);
    Serial.println(" ");

    lora.update();                                 //memperbarui data lora
}
