void tekanan() {
  status = pressure.getPressure(P, T);
  if (status != 0)
  {
    Serial.print("absolute pressure: ");
    Serial.print(P, 2);
    Serial.print(" mb, ");
  }
}
