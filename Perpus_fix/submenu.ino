void menu() {
  while(1) {
    setting();
    if ((digitalRead(tombol[4])) == LOW) goto k;
  }
  k:
  lcd.clear();
}

void setting() {
  if ((digitalRead(tombol[2])) == LOW) var=var+1;
  if ((digitalRead(tombol[3])) == LOW) var=var-1;
  showcase(var);
  delay(50);
}

void showcase(int iabel) {
  switch(iabel) {
    case 0:
    lcd.clear();
    if ((digitalRead(tombol[0])) == LOW && tgl<31) tgl=tgl+1;
    if ((digitalRead(tombol[1])) == LOW && tgl>0) tgl=tgl-1;
    lcd.setCursor(1,0);
    lcd.print("Atur Tanggal");
    lcd.setCursor(8,1);
    lcd.print(tgl);
    EEPROM.write(0, tgl);
    delay(50);
    break;
    case 1:
    lcd.clear();
    if ((digitalRead(tombol[0])) == LOW && i<11) i=i+1;
    if ((digitalRead(tombol[1])) == LOW && i>0) i=i-1;
    lcd.setCursor(0,0);
    lcd.print("  Atur Bulan  ");
    lcd.setCursor(3,1);
    lcd.print(bulan[i]);
    delay(50);
    EEPROM.write(1, i);
    break;
    case 2:
    lcd.clear();
    if ((digitalRead(tombol[0])) == LOW && m<9) m=m+1;
    if ((digitalRead(tombol[1])) == LOW && m>0) m=m-1;
    lcd.setCursor(2,0);
    lcd.print("Atur Tahun");
    lcd.setCursor(6,1);
    lcd.print("202");
    lcd.setCursor(9,1);
    lcd.print(m);
    EEPROM.write(2, m);
    delay(50);
    break;
  }
}
