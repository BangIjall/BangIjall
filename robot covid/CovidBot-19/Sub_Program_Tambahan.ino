int pulseToPWM(int pulse) {
  
  // If we're receiving numbers, convert them to motor PWM
  if ( pulse > 1000 ) {
    pulse = map(pulse, 1000, 2000, -500, 500);
    pulse = constrain(pulse, -255, 255);
  } else {
    pulse = 0;
  }

  // Anything in deadzone should stop the motor
  if ( abs(pulse) <= deadzone ) {
    pulse = 0;
  }

  return pulse;
}

void enc_clr() {
  m1.pulse = 0;
  m2.pulse = 0;
  m3.pulse = 0;
  m4.pulse = 0;
}
void sp_clr() {
  set_m1_pwm(0);
  set_m2_pwm(0);
  set_m3_pwm(0);
  set_m4_pwm(0);
  m1.setPoint = 0;
  m2.setPoint = 0;
  m3.setPoint = 0;
  m4.setPoint = 0;
}
void beep(int nyala, int _tH, int _tL) {
  n = nyala;
  tH = _tH;
  tL = _tL;
}
