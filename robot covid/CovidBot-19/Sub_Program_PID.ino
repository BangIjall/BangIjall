void PID_motor(){

  /*======================================== BACA RPM =======================================================*/
  if (++rpmTick > RPM_INTERVAL) {
    rpmTick = 0;
    m1.rpm = (float)m1.pulse * 60 * 1000 / RPM_INTERVAL / 135;
    m1.pulse = 0;

    m2.rpm = (float)m2.pulse * 60 * 1000 / RPM_INTERVAL / 135;
    m2.pulse = 0;

    m3.rpm = (float)m3.pulse * 60 * 1000 / RPM_INTERVAL / 135;
    m3.pulse = 0;

    m4.rpm = (float)m4.pulse * 60 * 1000 / RPM_INTERVAL / 135;
    m4.pulse = 0;
  }
  //=========================================================================================================
   
  // ========================================== PID =========================================================
  if (++m1.pidTick == PID_INTERVAL){
    m1.pidTick = 0;

    // ===== Motor PID =====
    m1.Err = abs(m1.setPoint) - m1.rpm;

    if (abs(m1.I) < m1.wind_up) m1.I += m1.Err;
    else            m1.I = 0;

    m1.pid = (m1.Kp * m1.Err * 0.1) + (m1.Ki * m1.I * 0.01) + (m1.Kd * (m1.Err - m1.lastErr) * 0.1);
    m1.lastErr = m1.Err;
    m1.pwm = m1.pwm + (int)m1.pid;

    if (m1.pwm < 5)     m1.pwm = 5;   // dead zone
    if (m1.pwm > 255)   m1.pwm = 255;
    if (m1.setPoint == 0) m1.pwm = 0;

    if (m1.mode == 1){
      if (m1.setPoint < 0)  set_m1_pwm(-m1.pwm);
      else          set_m1_pwm(m1.pwm);
    }
  }

  if (++m2.pidTick == PID_INTERVAL){
    m2.pidTick = 0;

    // ===== Motor PID =====
    m2.Err = abs(m2.setPoint) - m2.rpm;

    if (abs(m2.I) < m2.wind_up) m2.I += m2.Err;
    else            m2.I = 0;

    m2.pid = (m2.Kp * m2.Err * 0.1) + (m2.Ki * m2.I * 0.01) + (m2.Kd * (m2.Err - m2.lastErr) * 0.1);
    m2.lastErr = m2.Err;
    m2.pwm = m2.pwm + (int)m2.pid;

    if (m2.pwm < 5)     m2.pwm = 5;   // dead zone
    if (m2.pwm > 255)   m2.pwm = 255;
    if (m2.setPoint == 0) m2.pwm = 0;

    if (m2.mode == 1){
      if (m2.setPoint < 0)  set_m2_pwm(-m2.pwm);
      else          set_m2_pwm(m2.pwm);
    }
  }

  if (++m3.pidTick == PID_INTERVAL){
    m3.pidTick = 0;

    // ===== Motor PID =====
    m3.Err = abs(m3.setPoint) - m3.rpm;

    if (abs(m3.I) < m3.wind_up) m3.I += m3.Err;
    else            m3.I = 0;

    m3.pid = (m3.Kp * m3.Err * 0.1) + (m3.Ki * m3.I * 0.01) + (m3.Kd * (m3.Err - m3.lastErr) * 0.1);
    m3.lastErr = m3.Err;
    m3.pwm = m3.pwm + (int)m3.pid;

    if (m3.pwm < 5)     m3.pwm = 5;   // dead zone
    if (m3.pwm > 255)   m3.pwm = 255;
    if (m3.setPoint == 0) m3.pwm = 0;

    if (m3.mode == 1){
      if (m3.setPoint < 0)  set_m3_pwm(-m3.pwm);
      else          set_m3_pwm(m3.pwm);
    }
  }

  if (++m4.pidTick == PID_INTERVAL){
    m4.pidTick = 0;

    // ===== Motor PID =====
    m4.Err = abs(m4.setPoint) - m4.rpm;

    if (abs(m4.I) < m4.wind_up) m4.I += m4.Err;
    
            m4.I = 0;

    m4.pid = (m4.Kp * m4.Err * 0.1) + (m4.Ki * m4.I * 0.01) + (m4.Kd * (m4.Err - m4.lastErr) * 0.1);
    m4.lastErr = m4.Err;
    m4.pwm = m4.pwm + (int)m4.pid;

    if (m4.pwm < 5)     m4.pwm = 5;   // dead zone
    if (m4.pwm > 255)   m4.pwm = 255;
    if (m4.setPoint == 0) m4.pwm = 0;

    if (m4.mode == 1){
      if (m4.setPoint < 0)  set_m4_pwm(-m4.pwm);
      else          set_m4_pwm(m4.pwm);
    }
  }
  //=============================================================================================
}
