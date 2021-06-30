
void PID_motor(){

  /*======================================== BACA rps =======================================================*/
  if (++rpsTick > rps_INTERVAL) {
    rpsTick = 0;
    m1.rps = (float)m1.pulse * 1000 / rps_INTERVAL / 135;
    m1.v = m1.rps * phi * d_roda;     // cm/s 
    m1.pulse = 0;

    m2.rps = (float)m2.pulse * 1000 / rps_INTERVAL / 135;
    m2.v = m2.rps * phi * d_roda;     // cm/s 
    m2.pulse = 0;

    m3.rps = (float)m3.pulse * 1000 / rps_INTERVAL / 135;
    m3.v = m3.rps * phi * d_roda;     // cm/s 
    m3.pulse = 0; 

    m4.rps = (float)m4.pulse * 1000 / rps_INTERVAL / 135;
    m4.v = m4.rps * phi * d_roda;     // cm/s 
    m4.pulse = 0;
  }
  //=========================================================================================================
   
  // ========================================== PID =========================================================
  if (++m12.pidTick == PID_INTERVAL){ //depan
    m12.pidTick = 0;

    // ===== Motor PID =====
    m12.Err = m1.v - m2.v;

    if (abs(m12.I) < m12.wind_up) m12.I += m12.Err;
    else            m12.I = 0;

    m12.pid = (m12.Kp * m12.Err * 0.1) + (m12.Ki * m12.I * 0.01) + (m12.Kd * (m12.Err - m12.lastErr) * 0.1);
    m12.lastErr = m12.Err;
    
    if         (m12.Err == 0) m1.pwm = m2.pwm;
    else if    (m12.Err < 0)  m1.pwm = m1.pwm + (int)m12.pid;
    else if    (m12.Err > 0)  m2.pwm = m2.pwm + (int)m12.pid;
    
    if (m1.pwm < 5)     m1.pwm = 5;   // dead zone
    if (m1.pwm > 255)   m1.pwm = 255;
    if (m1.setPoint == 0) m1.pwm = 0;

    if (m2.pwm < 5)     m2.pwm = 5;   // dead zone
    if (m2.pwm > 255)   m2.pwm = 255;
    if (m2.setPoint == 0) m2.pwm = 0;
  }
  
  if (++m34.pidTick == PID_INTERVAL){ //belakang
    m34.pidTick = 0;

    // ===== Motor PID =====
    m34.Err = m3.v - m4.v;

    if (abs(m34.I) < m34.wind_up) m34.I += m34.Err;
    else            m34.I = 0;

    m34.pid = (m34.Kp * m34.Err * 0.1) + (m34.Ki * m34.I * 0.01) + (m34.Kd * (m34.Err - m34.lastErr) * 0.1);
    m34.lastErr = m34.Err;
    
    if         (m34.Err == 0) m3.pwm = m4.pwm;
    else if    (m34.Err < 0)  m3.pwm = m3.pwm + (int)m34.pid;
    else if    (m34.Err > 0)  m4.pwm = m4.pwm + (int)m34.pid;
    
    if (m3.pwm < 5)       m3.pwm = 5;   // dead zone
    if (m3 .pwm > 255)    m3.pwm = 255;
    if (m3.setPoint == 0) m3.pwm = 0;

    if (m4.pwm < 5)       m4.pwm = 5;   // dead zone
    if (m4.pwm > 255)     m4.pwm = 255;
    if (m4.setPoint == 0) m4.pwm = 0;

  }

    if (++m13.pidTick == PID_INTERVAL){ //belakang
    m13.pidTick = 0;

    // ===== Motor PID =====
    m13.Err = m1.v - m3.v;

    if (abs(m13.I) < m13.wind_up) m13.I += m13.Err;
    else            m13.I = 0;

    m13.pid = (m13.Kp * m13.Err * 0.1) + (m13.Ki * m13.I * 0.01) + (m13.Kd * (m13.Err - m13.lastErr) * 0.1);
    m13.lastErr = m13.Err;
    
    if         (m13.Err == 0) m1.pwm = m4.pwm;
    else if    (m13.Err < 0)  m1.pwm = m1.pwm + (int)m13.pid;
    else if    (m13.Err > 0)  m3.pwm = m3.pwm + (int)m13.pid;
    
    if (m1.pwm < 5)       m1.pwm = 5;   // dead zone
    if (m1.pwm > 255)     m1.pwm = 255;
    if (m1.setPoint == 0) m1.pwm = 0;
    
    if (m3.pwm < 5)       m3.pwm = 5;   // dead zone
    if (m3 .pwm > 255)    m3.pwm = 255;
    if (m3.setPoint == 0) m3.pwm = 0;

  }

  
    if (++m24.pidTick == PID_INTERVAL){ //belakang
    m24.pidTick = 0;

    // ===== Motor PID =====
    m24.Err = m2.v - m4.v;

    if (abs(m24.I) < m24.wind_up) m24.I += m24.Err;
    else            m24.I = 0;

    m24.pid = (m24.Kp * m24.Err * 0.1) + (m24.Ki * m24.I * 0.01) + (m24.Kd * (m24.Err - m24.lastErr) * 0.1);
    m24.lastErr = m24.Err;
    
    if         (m24.Err == 0) m2.pwm = m4.pwm;
    else if    (m24.Err < 0)  m2.pwm = m2.pwm + (int)m24.pid;
    else if    (m24.Err > 0)  m4.pwm = m4.pwm + (int)m24.pid;
    
    if (m2.pwm < 5)       m2.pwm = 5;   // dead zone
    if (m2 .pwm > 255)    m2.pwm = 255;
    if (m2.setPoint == 0) m2.pwm = 0;

    if (m4.pwm < 5)       m4.pwm = 5;   // dead zone
    if (m4.pwm > 255)     m4.pwm = 255;
    if (m4.setPoint == 0) m4.pwm = 0;

  }

   if (++cmps.pidTick == PID_INTERVAL){ //kompas
    cmps.pidTick = 0;

    // ===== Motor PID =====
    cmps.Err = cmps.sp - cmps.act;

    if (abs(cmps.I) < cmps.wind_up) cmps.I += cmps.Err;
    else            cmps.I = 0;

    cmps.pid = (cmps.Kp * cmps.Err * 0.1) + (cmps.Ki * cmps.I * 0.01) + (cmps.Kd * (cmps.Err - cmps.lastErr) * 0.1);
    cmps.lastErr = cmps.Err;
    
    if         (cmps.Err == 0) m1.pwm = m2.pwm;
    else if    (cmps.Err > 0){
      m1.pwm = m1.pwm + (int)cmps.pid;
      m3.pwm = m3.pwm + (int)cmps.pid;
    }
    else if    (cmps.Err < 0){
      m2.pwm = m2.pwm + (int)cmps.pid;
      m4.pwm = m4.pwm + (int)cmps.pid;
    }

    if (m1.pwm < 5)       m1.pwm = 5;   // dead zone
    if (m1.pwm > 255)     m1.pwm = 255;
    if (m1.setPoint == 0) m1.pwm = 0;
    
    if (m2.pwm < 5)       m2.pwm = 5;   // dead zone
    if (m2 .pwm > 255)    m2.pwm = 255;
    if (m2.setPoint == 0) m2.pwm = 0;

    if (m3.pwm < 5)       m3.pwm = 5;   // dead zone
    if (m3.pwm > 255)     m3.pwm = 255;
    if (m3.setPoint == 0) m3.pwm = 0;
    
    if (m4.pwm < 5)       m4.pwm = 5;   // dead zone
    if (m4 .pwm > 255)    m4.pwm = 255;
    if (m4.setPoint == 0) m4.pwm = 0;

  }
}
