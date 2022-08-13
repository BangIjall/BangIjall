void hitungCurah() {
  curah = curah + tip;
}

void hujan() {
  curahHariIni = curah;
  if (detik.equals("0")) { // Hanya print pada detik 0
    if (menit.equals("0") && jam.equals("7"))
    {
      curah = 0;
    }
  }
}

void bacaRTC() {
  now = rtc.now(); 
  jam = String(now.hour(), DEC);
  menit = String(now.minute(), DEC);
  detik = String(now.second(), DEC);
}
