#include <LiquidCrystal_I2C.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_INA219.h>
#include<Wire.h>
#include<SD.h>
#include<SPI.h>
#include "RTClib.h"

Adafruit_INA219 ina219; //  Adafruit_INA219 ina219_B(0x45); tambahkan alamat dan variable jika menggunakan lebih dari 1 Modul INA219
float tegangan, shunt, arus, daya, Tarus; // menyatakan variable ini berisikan nilai ber koma

int decimalPrecision = 2;

float currentSampleRead   = 0;               /* to read the value of a sample*/
unsigned long currentLastSample   = 0;       /* to count time for each sample. Technically 1 milli second 1 sample is taken */
float currentSampleSum    = 0;               /* accumulation of sample readings */
float currentSampleCount  = 0;               /* to count number of sample. */
float currentMean ;                         /* to calculate the average value from all samples*/
float finalCurrent ;                        /* the final current reading without taking offset value*/
float finalCurrent2 ;                       /* the final current reading*/
float ShortCircuitCurrentSTC = 2.9   ;      // 0.159 Key in the Short Circuit Current (At STC condition) of your Solar Panel or Solar Cell. Value 9 showing 9.0A Isc Panel.
float Irradiation = 0.00;                   /* This shows the irradiation level in W/m2.

            /* 1.1 - Offset DC Current */
float currentOffset = 0.00;             // to Offset deviation and accuracy. Offset any fake current when no current operates.
// the offset will automatically done when you press the <SELECT> button on the LCD display module.
// you may manually set offset here if you do not have LCD shield
float offsetLastSample = 0;             /* to count time for each sample. Technically 1 milli second 1 sample is taken */
float offsetSampleCount = 0;            /* to count number of sample. */

/* 1.2 - Average Accumulate Irradiation */

float accumulateIrradiation = 0;                          /* Amount of accumulate irradiation*/
unsigned long startMillisIrradiation;                     /* start counting time for irradiation energy */
unsigned long currentMillisIrradiation;                   /* current counting time for irradiation energy */
const unsigned long periodIrradiation = 1000;             // refresh every X seconds (in seconds) Default 1000 = 1 second
float FinalAccumulateIrradiationValue = 0;                /* shows the final accumulate irradiation reading*/

LiquidCrystal_I2C LCD(0x27, 20, 4);                        /*Creating the LiquidCrystal object named LCD */
unsigned long startMillisLCD;                               /* start counting time for LCD Display */
unsigned long currentMillisLCD;                             /* current counting time for LCD Display */
const unsigned long periodLCD = 1000;                       // refresh every X seconds (in seconds) in LED Display. Default 1000 = 1 second

RTC_DS1307 RTC;                                             /* initiate Real Time Cloak for DS1307 chip */
DateTime now;                                               /* initiate time variable*/
int h = now.hour();                                         /* create h as variable for hour */
int chipSelect = 11;                                        /* ChipSelect pin based on the SC card shield using SPI communication. By default the pin is 10 on Arduino Uno. This pin cannot be changed */
File mySensorData;                                          // Variable for working with our file object
unsigned long startMillisSD;                                /* start counting time for SD Card */
unsigned long currentMillisSD;                              /* current counting time for SD Card */
const unsigned long periodSD = 60000;                       // refresh every X seconds (in seconds) Default 60000 = 1 minute

void setup() {
  Serial.begin(9600);                               /* In order to see value in serial monitor */

  ina219.begin(); // ganti ina219 sesuai dengan alamat

  /* 1.2 - Average Accumulate Irradiation */

  startMillisIrradiation = millis();                /* Record initial starting time for daily irradiation */

  /* 2 - LCD Display  */

  LCD.begin();                                 /* Tell Arduino that our LCD has 16 columns and 2 rows*/
  LCD.setCursor(0, 0);                              /* Set LCD to upper left corner to start display*/
  startMillisLCD = millis();

  /* 3 - SD memory card shield */

  pinMode(chipSelect, OUTPUT);                      /*reserve pin 10 as an ouput by default*/
  RTC.begin();
  Wire.begin();
  SD.begin(chipSelect);                             /* Initialise the SD Card with chipSelect connected to pin 10 by default*/
  startMillisSD = millis();                         /* Record initial starting time for SD card module */
  RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));   /*set the Real Time Cloak to the time same as your PC or Laptop time*/

  if (! RTC.isrunning())                            /* if RTC not running give warning in Serial Monitor */
  {
    Serial.println("RTC is not running !");
  }
  mySensorData = SD.open("Irrad.txt", FILE_WRITE);  // Open or create Irrad.txt on the SD card as a file to write to
  if (mySensorData)                                 // only to do these if data file opened sucessfully
  {
    DateTime now = RTC.now();                       /* get time information */
    mySensorData.print("Date");
    mySensorData.print(",");
    mySensorData.print("Current (A)");
    mySensorData.print(",");
    mySensorData.print("Irradiation (W/m2)");
    mySensorData.print(",");
    mySensorData.println("Daily Irradiation (Wh/m2/day)");
    mySensorData.close();                          //close the file
  }
}

void loop() {
  //
  if (millis() >= currentLastSample + 1 )                                                               /* every 1 milli second taking 1 reading */
  {
    currentSampleRead = ina219.getCurrent_mA () + 1;                                                      /* read the sample value */
    currentSampleSum = currentSampleSum + currentSampleRead ;                                         /* accumulate value with older sample readings*/
    currentSampleCount = currentSampleCount + 1;                                                      /* to move on to the next following count */
    currentLastSample = millis();                                                                     /* to reset the time again so that next cycle can start again*/
  }

  if (currentSampleCount == 100)                                                                       /* after 1000 count or 1000 milli seconds (1 second), do the calculation and display value*/
  {
    currentMean = currentSampleSum / currentSampleCount;                                              /* calculate average value of all sample readings taken*/
    //    finalCurrent = (((currentMean / 1024) * moduleSupplyVoltage) / mVperAmpValue);                    /* calculate the final current (without offset)*/
    //    finalCurrent2 = finalCurrent + currentOffset;                                                     /* The final current */
    Irradiation = (currentMean / ShortCircuitCurrentSTC * 1000);
    Serial.print(currentMean, decimalPrecision);
    Serial.print(" A  ");
    Serial.print(Irradiation, decimalPrecision);
    Serial.print(" W/m2  ");
    currentSampleSum = 0;                                                                             /* to reset accumulate sample values for the next cycle */
    currentSampleCount = 0;                                                                           /* to reset number of sample for the next cycle */
  }


  /* 1.2 - Average Accumulate Irradiation */

  currentMillisIrradiation = millis();                                                                 /* Count the time for current */

  if (currentMillisIrradiation - startMillisIrradiation >= periodIrradiation)
  {
    accumulateIrradiation = Irradiation / 3600 * (periodIrradiation / 1000);                          /* for smoothing calculation*/
    FinalAccumulateIrradiationValue =  FinalAccumulateIrradiationValue + accumulateIrradiation ;
    Serial.print(FinalAccumulateIrradiationValue, decimalPrecision);
    Serial.println(" Wh/m2/day");
    startMillisIrradiation = currentMillisIrradiation ;                                               /* Set the starting point again for next counting time */
    DateTime now = RTC.now();
    if ((now.hour() >= 23) && (now.second() >= 58))                                                   /* daily irradiation will reset to 0 at 12am everyday*/
    { // if do not want to reset everyday, then delete these codes
      FinalAccumulateIrradiationValue =  0;
    }
  }


  /* 2 - LCD Display  */

  currentMillisLCD = millis();
  if (currentMillisLCD - startMillisLCD >= periodLCD)
  {
    LCD.setCursor(0, 0);                                                                          /* Set cursor to first colum 0 and second row 1  */
    LCD.print(currentMean, decimalPrecision);                                                   /* display voltage value in LCD in first row  */
    LCD.print(" A   ");
    LCD.setCursor(8, 0);
    LCD.print(Irradiation, 0);                                                                    /* display current value in LCD in first row */
    LCD.print(" W/m2   ");
    LCD.setCursor(0, 1);
    LCD.print(FinalAccumulateIrradiationValue, 0);                                                /* display current value in LCD in first row */
    LCD.print(" Wh/m2/day        ");
    startMillisLCD = currentMillisLCD ;                                                           /* Set the starting point again for next counting time */
  }

  /* 3 - SD memory card shield */

//  currentMillisSD = millis();                                                                       /* keep counting time for SD memory function */
//  if (currentMillisSD - startMillisSD >= periodSD)                                                  /* if the time difference from begining is 1 minute (by default) do the following code */
//  {
//    mySensorData = SD.open("Irrad.txt", FILE_WRITE);                                              //Open Irrad.txt on the SD card as a file to write to
//    if (mySensorData)                                                                             //only to do these if data file opened sucessfully
//    {
//      DateTime now = RTC.now();                                                                   /* get time information */
//      mySensorData.print(now.year(), DEC);                                                        /* print the year today */
//      mySensorData.print("/");
//      mySensorData.print(now.month(), DEC);                                                       /* print the month today */
//      mySensorData.print("/");
//      mySensorData.print(now.day(), DEC);                                                         /* print the date today */
//      mySensorData.print(" ");
//      mySensorData.print(now.hour(), DEC);                                                        /* print the hour now */
//      mySensorData.print(":");
//      mySensorData.print(now.minute(), DEC);                                                      /* print the minute now */
//      mySensorData.print(":");
//      mySensorData.print(now.second(), DEC);                                                      /* print the second now */
//      mySensorData.print(",");
//      mySensorData.print(finalCurrent2);                                                          /* print the short circuit current */
//      mySensorData.print(",");
//      mySensorData.print(Irradiation);                                                            /* print the irradiance in W/m2 */
//      mySensorData.print(",");
//      mySensorData.println(FinalAccumulateIrradiationValue);                                      /* print the total daily irradiance in W/m2/day */
//      mySensorData.close();                                                                       //close the file
//      Serial.println("written to SD Card Successfully !");
//      startMillisSD = currentMillisSD ;
//    }
//  }
}
