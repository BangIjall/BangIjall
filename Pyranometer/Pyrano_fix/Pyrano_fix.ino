#include <LiquidCrystal_I2C.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_INA219.h>

/* 0- Umum */

int decimalPrecision = 2;

/* 1- Arus & Radiasi */

Adafruit_INA219 ina219;                      /*  Adafruit_INA219 ina219_B(0x45); tambahkan alamat dan variable jika menggunakan lebih dari 1 Modul INA219*/
float currentSampleRead   = 0;               /* Untuk tempat data mengambil sampel */
unsigned long currentLastSample   = 0;       /* Untuk tempat data pengaktifan pengambilan sampel */
float currentSampleSum    = 0;               /* Untuk tempat data nilai jumlah data */
float currentSampleCount  = 0;               /* Untuk hitungan pengambilan sampel yaitu maksimal 100 sampel */
float currentMean ;                          /* Untuk tempat data rata rata arus */
float konstanta = 0.159   ;                  // konstanta untuk konversi arus ke radiasi
float Irradiation = 0.00;                    /* Untuk tempat data radiasi dalam satuan W/m2. */

/* 2 - LCD Display  */

LiquidCrystal_I2C LCD(0x27, 20, 4);          /* Membuat nama objek Liquid Crystal I2C dengan nama LCD */
unsigned long startMillisLCD;                /* start hitungan waktu untuk LCD Display */
unsigned long currentMillisLCD;              /* waktu millis pada LCD Display */
const unsigned long periodLCD = 1000;        // jeda penampilan LCD Display dalam satuan milisecond


void setup() {

  /* 0- General */

  Serial.begin(9600);                        /* Inisialisasi Serial Monitor */

  /* 1- Arus */

  ina219.begin();                            /* Inisialisasi sensor arus */

  /* 2 - LCD Display  */

  LCD.begin();                               /* Inisialisasi LCD Display */
  LCD.setCursor(0, 0);                       /* Set LCD koordinat 0, 0 */
  startMillisLCD = millis();                 /* set hitungan waktu penampilan LCD pertama */
}

void loop() {

  /* 1- DC Current & Radiasi */

  if (millis() >= currentLastSample + 1 )                                                              /* Setiap 1 milli second mendaoatkan 1 bacaan sampel */
  {
    currentSampleRead = ina219.getCurrent_mA () + 1;                                                  /* membaca sampel dengan kalibrasi sensor arus */
    currentSampleSum = currentSampleSum + currentSampleRead ;                                         /* Akumulasi sampel */
    currentSampleCount = currentSampleCount + 1;                                                      /* hitungan penomoran sampel */
    currentLastSample = millis();                                                                     /* untuk mereset waktu start lampau */
  }

  if (currentSampleCount == 100)                                                                      /* after 1000 count or 1000 milli seconds (1 second), do the calculation and display value*/
  {
    currentMean = currentSampleSum / currentSampleCount;                                              /* menghitung rata rata arus */
    Irradiation = (currentMean / konstanta * 1000);                                                   /* menghitung radiasi */
    Serial.print(currentMean, decimalPrecision);
    Serial.print(" mA  ");
    Serial.print(Irradiation, decimalPrecision);
    Serial.print(" W/m2  ");
    currentSampleSum = 0;                                                                             /* untuk reset nilai akumulasi untuk cycle selanjutnya */
    currentSampleCount = 0;                                                                           /* untuk reset total penomoran sampel untuk cycle selanjutnya */
  }

  /* 2 - LCD Display  */

  currentMillisLCD = millis();                                                                        /* Set waktu millis */
  if (currentMillisLCD - startMillisLCD >= periodLCD)
  {
    LCD.setCursor(0, 0);                                                                          /* Set cursor pada koordinat 0, 0 */
    LCD.print(" Arus :  ");
    LCD.setCursor(0, 1);                                                                          /* Set cursor pada koordinat 0, 1 */
    LCD.print(currentMean, decimalPrecision);                                                     /* display arus dengan ketelitian 2 angka di belakang koma  */
    LCD.print(" mA   ");
    LCD.setCursor(0, 2);                                                                          /* Set cursor pada koordinat 0, 2 */
    LCD.print(" Radiasi :  ");
    LCD.setCursor(0, 3);                                                                          /* Set cursor pada koordinat 0, 3 */
    LCD.print(Irradiation, 0);                                                                    /* display radiasi */
    LCD.print(" W/m2   ");
    startMillisLCD = currentMillisLCD ;                                                           /* Set selisih millis = 0 */

    Serial.print(currentMean, decimalPrecision);
    Serial.print(" mA  ");
    Serial.print(Irradiation, decimalPrecision);
    Serial.println(" W/m2  ");
  }
}
