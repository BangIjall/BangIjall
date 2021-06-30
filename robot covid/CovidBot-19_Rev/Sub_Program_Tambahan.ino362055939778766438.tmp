float getBearing() {
  int timeout = I2C_TIMEOUT;
  
  Wire.beginTransmission(_i2cAddress);

  Wire.write(BEARING_REGISTER);

  int nackCatcher = Wire.endTransmission(false);

  if(nackCatcher != 0){return 0;}
  
  Wire.requestFrom(_i2cAddress , _TWO_BYTES);

  while(Wire.available() < _TWO_BYTES && (timeout-- > 0))
    delay(1);

  if (timeout <= 0) return 0;

  _byteHigh = Wire.read(); 
  _byteLow = Wire.read();

  _bearing = ((_byteHigh<<8) + _byteLow) / 10;

  return _bearing;
}
