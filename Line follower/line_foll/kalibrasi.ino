void kalibrasi (){
  Serial.println ("kalibrasi on !");
 for (i=0; i<6; i++){
  nilaiMin[i] = 1023;
  nilaiMax[i] = 0;
 }
 delay(100);
 while (digitalRead(kendaliTombol) == HIGH){
  digitalWrite (12, HIGH);
  digitalWrite (13, LOW);
  delay(100);
  KendaliBacasensor();
  for(i=0;i<6;i++){
    if(sensor[i] > nilaiMax[i]) nilaiMax[i] = sensor[i];
    if(sensor[i] < nilaiMin[i]) nilaiMin[i] = sensor[i];
  }
  digitalWrite (12, LOW);
  digitalWrite (13, HIGH);
  delay(100);
 }
 Serial.println("Kalibrasi DONE!!");
 digitalWrite (12, HIGH);
 digitalWrite (13, HIGH);
 for(i=0;i<6;i++){
  nilaiRef[i] = (nilaiMax[i] + nilaiMin[i])/2.1;
  EEPROM.write(i,nilaiRef[i]);
 }
 delay(500);
}

void KendaliBacasensor (){
  sensor[0] = analogRead (A0)/4;
  sensor[1] = analogRead (A1)/4;
  sensor[2] = analogRead (A2)/4;
  sensor[3] = analogRead (A3)/4;
  sensor[4] = analogRead (A4)/4;
  sensor[5] = analogRead (A5)/4;
}

void bacaSensorbiner(){
  KendaliBacasensor();
  if (sensor[0] > nilaiRef[0]){
    biner[0] = 1;
  }
  else {
    biner[0] = 0;
  }
    if (sensor[1] > nilaiRef[1]){
    biner[1] = 1;
  }
  else {
    biner[1] = 0;
  }
    if (sensor[2] > nilaiRef[2]){
    biner[2] = 1;
  }
  else {
    biner[2] = 0;
  }
    if (sensor[3] > nilaiRef[3]){
    biner[3] = 1;
  }
  else {
    biner[3] = 0;
  }
    if (sensor[4] > nilaiRef[4]){
    biner[4] = 1;
  }
  else {
    biner[4] = 0;
  }
    if (sensor[5] > nilaiRef[5]){
    biner[5] = 1;
  }
  else {
    biner[5] = 0;
  }
}
void tampilDatasensor(){
  for(i=0;i<6;i++){
    Serial.print(sensor[i]);
    Serial.print("  ");
  }
  Serial.println(" ");
  delay(100);
}
void dataSensor(){
  for(i=0;i<6;i++){
    nilaiRef[i]=EEPROM.read(i);
  }
}

void KendaliTampilsensor (){
  bacaSensorbiner();
  Serial.print(biner[0]);
  Serial.print("  ");
  Serial.print(biner[1]);
  Serial.print("  ");
  Serial.print(biner[2]);
  Serial.print("  ");
  Serial.print(biner[3]);
  Serial.print("  ");
  Serial.print(biner[4]);
  Serial.print("  ");
  Serial.print(biner[5]);
  Serial.print("  ");
}
