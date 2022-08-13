void ambilData() {
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  if (isnan(hum) || isnan(temp)) {
    Serial.println("ada masalah pada DHT");
    while(1)
      ;
  }
}
