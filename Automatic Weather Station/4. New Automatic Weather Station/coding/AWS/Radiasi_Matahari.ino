void pyrano() {
  for (int i = 1; i<100; i++) {
    currentSampleRead = ina219.getCurrent_mA () + 1;                                                  /* membaca sampel dengan kalibrasi sensor arus */
    currentSampleSum = currentSampleSum + currentSampleRead ;                                         /* Akumulasi sampel */
  }

  currentMean = currentSampleSum / 100;                                              /* menghitung rata rata arus */
  Irradiation = (currentMean / konstanta * 1000);
  currentSampleSum = 0;  
}
