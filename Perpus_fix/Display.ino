void tampilan() {
  lcd.setCursor(0,0);
  lcd.print(tgl);
  lcd.setCursor(3,0);
  lcd.print(bulan[i]);
  lcd.setCursor(12,0);
  lcd.print("202");
  lcd.setCursor(15,0);
  lcd.print(m);
  lcd.setCursor(0,1);
  lcd.print("Data hitung:");
  lcd.setCursor(13,1);
  lcd.print(data);
}

void display_satuan(int satuan) {
switch (satuan)
  {
    //number 0
    case 0:
      digitalWrite(Aa, LOW);
      digitalWrite(Ba, LOW);
      digitalWrite(Ca, LOW);
      digitalWrite(Da, LOW);
      digitalWrite(Ea, LOW);
      digitalWrite(Fa, LOW);
      digitalWrite(Ga, HIGH);
      break;
    //number 1
    case 1:
      digitalWrite(Aa, HIGH);
      digitalWrite(Ba, LOW);
      digitalWrite(Ca, LOW);
      digitalWrite(Da, HIGH);
      digitalWrite(Ea, HIGH);
      digitalWrite(Fa, HIGH);
      digitalWrite(Ga, HIGH);
      break;
    //number 2
    case 2:
      digitalWrite(Aa, LOW);
      digitalWrite(Ba, LOW);
      digitalWrite(Ca, HIGH);
      digitalWrite(Da, LOW);
      digitalWrite(Ea, LOW);
      digitalWrite(Fa, HIGH);
      digitalWrite(Ga, LOW);
      break;
    //number 3
    case 3:
      digitalWrite(Aa, LOW);
      digitalWrite(Ba, LOW);
      digitalWrite(Ca, LOW);
      digitalWrite(Da, LOW);
      digitalWrite(Ea, HIGH);
      digitalWrite(Fa, HIGH);
      digitalWrite(Ga, LOW);
      break;
    //number 4
    case 4:
      digitalWrite(Aa, HIGH);
      digitalWrite(Ba, LOW);
      digitalWrite(Ca, LOW);
      digitalWrite(Da, HIGH);
      digitalWrite(Ea, HIGH);
      digitalWrite(Fa, LOW);
      digitalWrite(Ga, LOW);
      break;
    //number 5
    case 5:
      digitalWrite(Aa, LOW);
      digitalWrite(Ba, HIGH);
      digitalWrite(Ca, LOW);
      digitalWrite(Da, LOW);
      digitalWrite(Ea, HIGH);
      digitalWrite(Fa, LOW);
      digitalWrite(Ga, LOW);
      break;
    //number 6
    case 6:
      digitalWrite(Aa, LOW);
      digitalWrite(Ba, HIGH);
      digitalWrite(Ca, LOW);
      digitalWrite(Da, LOW);
      digitalWrite(Ea, LOW);
      digitalWrite(Fa, LOW);
      digitalWrite(Ga, LOW);
      break;
    //number 7
    case 7:
      digitalWrite(Aa, LOW);
      digitalWrite(Ba, LOW);
      digitalWrite(Ca, LOW);
      digitalWrite(Da, HIGH);
      digitalWrite(Ea, HIGH);
      digitalWrite(Fa, HIGH);
      digitalWrite(Ga, HIGH);
      break;
    //number 8
    case 8:
      digitalWrite(Aa, LOW);
      digitalWrite(Ba, LOW);
      digitalWrite(Ca, LOW);
      digitalWrite(Da, LOW);
      digitalWrite(Ea, LOW);
      digitalWrite(Fa, LOW);
      digitalWrite(Ga, LOW);
      break;
    //number 9
    case 9:
      digitalWrite(Aa, LOW);
      digitalWrite(Ba, LOW);
      digitalWrite(Ca, LOW);
      digitalWrite(Da, LOW);
      digitalWrite(Ea, HIGH);
      digitalWrite(Fa, LOW);
      digitalWrite(Ga, LOW);
      break;
  }
}

void display_puluhan(int puluhan) {
switch (puluhan)
  {
    //number 0
    case 0:
      digitalWrite(Ab, LOW);
      digitalWrite(Bb, LOW);
      digitalWrite(Cb, LOW);
      digitalWrite(Db, LOW);
      digitalWrite(Eb, LOW);
      digitalWrite(Fb, LOW);
      digitalWrite(Gb, HIGH);
      break;
    //number 1
    case 1:
      digitalWrite(Ab, HIGH);
      digitalWrite(Bb, LOW);
      digitalWrite(Cb, LOW);
      digitalWrite(Db, HIGH);
      digitalWrite(Eb, HIGH);
      digitalWrite(Fb, HIGH);
      digitalWrite(Gb, HIGH);
      break;
    //number 2
    case 2:
      digitalWrite(Ab, LOW);
      digitalWrite(Bb, LOW);
      digitalWrite(Cb, HIGH);
      digitalWrite(Db, LOW);
      digitalWrite(Eb, LOW);
      digitalWrite(Fb, HIGH);
      digitalWrite(Gb, LOW);
      break;
    //number 3
    case 3:
      digitalWrite(Ab, LOW);
      digitalWrite(Bb, LOW);
      digitalWrite(Cb, LOW);
      digitalWrite(Db, LOW);
      digitalWrite(Eb, HIGH);
      digitalWrite(Fb, HIGH);
      digitalWrite(Gb, LOW);
      break;
    //number 4
    case 4:
      digitalWrite(Ab, HIGH);
      digitalWrite(Bb, LOW);
      digitalWrite(Cb, LOW);
      digitalWrite(Db, HIGH);
      digitalWrite(Eb, HIGH);
      digitalWrite(Fb, LOW);
      digitalWrite(Gb, LOW);
      break;
    //number 5
    case 5:
      digitalWrite(Ab, LOW);
      digitalWrite(Bb, HIGH);
      digitalWrite(Cb, LOW);
      digitalWrite(Db, LOW);
      digitalWrite(Eb, HIGH);
      digitalWrite(Fb, LOW);
      digitalWrite(Gb, LOW);
      break;
    //number 6
    case 6:
      digitalWrite(Ab, LOW);
      digitalWrite(Bb, HIGH);
      digitalWrite(Cb, LOW);
      digitalWrite(Db, LOW);
      digitalWrite(Eb, LOW);
      digitalWrite(Fb, LOW);
      digitalWrite(Gb, LOW);
      break;
    //number 7
    case 7:
      digitalWrite(Ab, LOW);
      digitalWrite(Bb, LOW);
      digitalWrite(Cb, LOW);
      digitalWrite(Db, HIGH);
      digitalWrite(Eb, HIGH);
      digitalWrite(Fb, HIGH);
      digitalWrite(Gb, HIGH);
      break;
    //number 8
    case 8:
      digitalWrite(Ab, LOW);
      digitalWrite(Bb, LOW);
      digitalWrite(Cb, LOW);
      digitalWrite(Db, LOW);
      digitalWrite(Eb, LOW);
      digitalWrite(Fb, LOW);
      digitalWrite(Gb, LOW);
      break;
    //number 9
    case 9:
      digitalWrite(Ab, LOW);
      digitalWrite(Bb, LOW);
      digitalWrite(Cb, LOW);
      digitalWrite(Db, LOW);
      digitalWrite(Eb, HIGH);
      digitalWrite(Fb, LOW);
      digitalWrite(Gb, LOW);
      break;
  }
}

void display_ratusan(int ratusan) {
switch (ratusan)
  {
    //number 0
    case 0:
      digitalWrite(Ac, LOW);
      digitalWrite(Bc, LOW);
      digitalWrite(Cc, LOW);
      digitalWrite(Dc, LOW);
      digitalWrite(Ec, LOW);
      digitalWrite(Fc, LOW);
      digitalWrite(Gc, HIGH);
      break;
    //number 1
    case 1:
      digitalWrite(Ac, HIGH);
      digitalWrite(Bc, LOW);
      digitalWrite(Cc, LOW);
      digitalWrite(Dc, HIGH);
      digitalWrite(Ec, HIGH);
      digitalWrite(Fc, HIGH);
      digitalWrite(Gc, HIGH);
      break;
    //number 2
    case 2:
      digitalWrite(Ac, LOW);
      digitalWrite(Bc, LOW);
      digitalWrite(Cc, HIGH);
      digitalWrite(Dc, LOW);
      digitalWrite(Ec, LOW);
      digitalWrite(Fc, HIGH);
      digitalWrite(Gc, LOW);
      break;
    //number 3
    case 3:
      digitalWrite(Ac, LOW);
      digitalWrite(Bc, LOW);
      digitalWrite(Cc, LOW);
      digitalWrite(Dc, LOW);
      digitalWrite(Ec, HIGH);
      digitalWrite(Fc, HIGH);
      digitalWrite(Gc, LOW);
      break;
    //number 4
    case 4:
      digitalWrite(Ac, HIGH);
      digitalWrite(Bc, LOW);
      digitalWrite(Cc, LOW);
      digitalWrite(Dc, HIGH);
      digitalWrite(Ec, HIGH);
      digitalWrite(Fc, LOW);
      digitalWrite(Gc, LOW);
      break;
    //number 5
    case 5:
      digitalWrite(Ac, LOW);
      digitalWrite(Bc, HIGH);
      digitalWrite(Cc, LOW);
      digitalWrite(Dc, LOW);
      digitalWrite(Ec, HIGH);
      digitalWrite(Fc, LOW);
      digitalWrite(Gc, LOW);
      break;
    //number 6
    case 6:
      digitalWrite(Ac, LOW);
      digitalWrite(Bc, HIGH);
      digitalWrite(Cc, LOW);
      digitalWrite(Dc, LOW);
      digitalWrite(Ec, LOW);
      digitalWrite(Fc, LOW);
      digitalWrite(Gc, LOW);
      break;
    //number 7
    case 7:
      digitalWrite(Ac, LOW);
      digitalWrite(Bc, LOW);
      digitalWrite(Cc, LOW);
      digitalWrite(Dc, HIGH);
      digitalWrite(Ec, HIGH);
      digitalWrite(Fc, HIGH);
      digitalWrite(Gc, HIGH);
      break;
    //number 8
    case 8:
      digitalWrite(Ac, LOW);
      digitalWrite(Bc, LOW);
      digitalWrite(Cc, LOW);
      digitalWrite(Dc, LOW);
      digitalWrite(Ec, LOW);
      digitalWrite(Fc, LOW);
      digitalWrite(Gc, LOW);
      break;
    //number 9
    case 9:
      digitalWrite(Ac, LOW);
      digitalWrite(Bc, LOW);
      digitalWrite(Cc, LOW);
      digitalWrite(Dc, LOW);
      digitalWrite(Ec, HIGH);
      digitalWrite(Fc, LOW);
      digitalWrite(Gc, LOW);
      break;
  }
}
