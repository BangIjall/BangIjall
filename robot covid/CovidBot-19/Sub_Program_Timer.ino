ISR(TIMER5_OVF_vect) {
  TCNT5 = -250;
  PID_motor();
  if (n > 0) {
    if (++beepTick < tH) digitalWrite(buzz, HIGH);
    else  digitalWrite(buzz, LOW);
    if (beepTick >(tH + tL)) {
      beepTick = 0;
      n--;
    }
  }
  else {
    beepTick = 0;
    digitalWrite(buzz, LOW);
  }
}  
