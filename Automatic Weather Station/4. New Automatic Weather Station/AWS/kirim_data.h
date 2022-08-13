void kirim() {
  StaticJsonDocument<200> doc;
  doc["curah"] = curah;
  doc["Irradiation"] = Irradiation;
  doc["temp"] = temp;
  doc["hum"] = hum;
  doc["P"] = P;

  serializeJson(doc, linkSerial);
  
//  String dataKirim = String(curah) + "#" + String(Irradiation) + "#" + String(temp) + "#" + String(hum) + "#" + String(P);
//  Serial.println(dataKirim);
}

bool cek() {
  if (linkSerial.available()) {
    StaticJsonDocument<300> req;
    DeserializationError err = deserializeJson(req, linkSerial);

    if (err == DeserializationError::Ok) {
      // Print the values
      // (we must use as<T>() to resolve the ambiguity)
      Serial.print("minta = ");
      Serial.println(req["minta"].as<int>());
    }

    else {
      // Print error to the "debug" serial port
      Serial.print("deserializeJson() returned ");
      Serial.println(err.c_str());

      // Flush all bytes in the "link" serial port buffer
      while (linkSerial.available() > 0)
        linkSerial.read();
    }
  }
  
  if (doc["minta"].as<int>() = 1) {
    return true;
  }

  else {
    return false;
  }
}
