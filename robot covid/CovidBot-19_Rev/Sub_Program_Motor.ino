void motor_init(void){
  // Motor 1
  pinMode(M1Apin, OUTPUT);  digitalWrite(M1Apin, LOW);
  pinMode(M1Bpin, OUTPUT);  digitalWrite(M1Bpin, LOW);
  pinMode(M1Epin, OUTPUT);  digitalWrite(M1Epin, LOW);
  pinMode(EN1A, INPUT_PULLUP);
  pinMode(EN1B, INPUT_PULLUP);

  // Motor 2
  pinMode(M2Apin, OUTPUT);  digitalWrite(M2Apin, LOW);
  pinMode(M2Bpin, OUTPUT);  digitalWrite(M2Bpin, LOW);
  pinMode(M2Epin, OUTPUT);  digitalWrite(M2Epin, LOW);
  pinMode(EN2A, INPUT_PULLUP);
  pinMode(EN2B, INPUT_PULLUP);

  // Motor 3
  pinMode(M3Apin, OUTPUT);  digitalWrite(M3Apin, LOW);
  pinMode(M3Bpin, OUTPUT);  digitalWrite(M3Bpin, LOW);
  pinMode(M3Epin, OUTPUT);  digitalWrite(M3Epin, LOW);
  pinMode(EN3A, INPUT_PULLUP);
  pinMode(EN3B, INPUT_PULLUP);

  // Motor 4
  pinMode(M4Apin, OUTPUT);  digitalWrite(M4Apin, LOW);
  pinMode(M4Bpin, OUTPUT);  digitalWrite(M4Bpin, LOW);
  pinMode(M4Epin, OUTPUT);  digitalWrite(M4Epin, LOW);
  pinMode(EN4A, INPUT_PULLUP);
  pinMode(EN4B, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(EN1A), encoder1, FALLING);
  attachInterrupt(digitalPinToInterrupt(EN2A), encoder2, FALLING);
  attachInterrupt(digitalPinToInterrupt(EN3A), encoder3, FALLING);
  attachInterrupt(digitalPinToInterrupt(EN4A), encoder4, FALLING);
  
 // -------------------- Konstanta PID Motor -------------------------
  m12.Kp = 0.8; m12.Ki = 0.02; m12.Kd = 2;  m12.wind_up = 1000;
  m34.Kp = 0.8; m34.Ki = 0.02; m34.Kd = 2;  m34.wind_up = 1000;
  m13.Kp = 0.8; m13.Ki = 0.02; m13.Kd = 2;  m13.wind_up = 1000;
  m24.Kp = 1.2; m24.Ki = 0.02; m24.Kd = 2;  m24.wind_up = 1000;
  cmps.Kp = 2; cmps.Ki = 0; cmps.Kd = 1;  cmps.wind_up = 1000;

 
  m1.pulse = 0; m2.pulse = 0; m3.pulse = 0; m4.pulse = 0;
  m1.pos = 0;   m2.pos = 0;   m3.pos = 0;   m4.pos = 0;
}

// ----------------------- Motor Encoder --------------------- //
void encoder1(void){
  if (digitalRead(EN1B))  m1.pos--;
  else          m1.pos++;
  m1.pulse++;
  
}

void encoder2(void){
  if (digitalRead(EN2B))  m2.pos--;
  else          m2.pos++;
  m2.pulse++;
}

void encoder3(void){
  if (digitalRead(EN3B))  m3.pos--;
  else          m3.pos++;
  m3.pulse++;
  
}

void encoder4(void){
  if (digitalRead(EN4B))  m4.pos--;
  else        m4.pos++;
  m4.pulse++;
}

// ===================================== Set motor PWM ===================================== //
// Set Motor 1 Speed
void set_m1_pwm(int speed){
  // Motor Dead Zone PWM
  //if(speed > 0 && speed < 20)   speed = 20;
  //if(speed < 0 && speed > -20)  speed = -20;

  if (speed < 0){
    digitalWrite(M1Apin, LOW);
    digitalWrite(M1Bpin, HIGH);
    analogWrite(M1Epin, abs(speed));
  }
  if (speed > 0){
    digitalWrite(M1Apin, HIGH);
    digitalWrite(M1Bpin, LOW);
    analogWrite(M1Epin, abs(speed));
  }
  if (speed == 0){
    digitalWrite(M1Apin, HIGH);
    digitalWrite(M1Bpin, HIGH);
    analogWrite(M1Epin, 0);
  }
}

// Set Motor 2 Speed
void set_m2_pwm(int speed){
  if (speed < 0){
    digitalWrite(M2Apin, LOW);
    digitalWrite(M2Bpin, HIGH);
    analogWrite(M2Epin, abs(speed));
  }
  if (speed > 0){
    digitalWrite(M2Apin, HIGH);
    digitalWrite(M2Bpin, LOW);
    analogWrite(M2Epin, abs(speed));
  }
  if (speed == 0){
    digitalWrite(M2Apin, HIGH);
    digitalWrite(M2Bpin, HIGH);
    analogWrite(M2Epin, 0);
  }
}

// Set Motor 3 Speed
void set_m3_pwm(int speed){
  // Motor Dead Zone PWM
  //if(speed > 0 && speed < 20)   speed = 20;
  //if(speed < 0 && speed > -20)  speed = -20;

  if (speed > 0){
    digitalWrite(M3Apin, LOW);
    digitalWrite(M3Bpin, HIGH);
    analogWrite(M3Epin, abs(speed));
  }
  if (speed < 0){
    digitalWrite(M3Apin, HIGH);
    digitalWrite(M3Bpin, LOW);
    analogWrite(M3Epin, abs(speed));
  }
  if (speed == 0){
    digitalWrite(M3Apin, HIGH);
    digitalWrite(M3Bpin, HIGH);
    analogWrite(M3Epin, 0);
  }
}

// Set Motor 4 Speed
void set_m4_pwm(int speed){
  if (speed < 0){
    digitalWrite(M4Apin, LOW);
    digitalWrite(M4Bpin, HIGH);
    analogWrite(M4Epin, abs(speed));
  }
  if (speed >  0){
    digitalWrite(M4Apin, HIGH);
    digitalWrite(M4Bpin, LOW);
    analogWrite(M4Epin,abs(speed));
  }
  if (speed == 0){
    digitalWrite(M4Apin, HIGH);
    digitalWrite(M4Bpin, HIGH);
    analogWrite(M4Epin, 0);
  }
}

// ========================================== Set Motor dengan PID ================================================ //
void m1PID(int speed){
  m1.mode = 1;
  m1.setPoint = speed;
  set_m1_pwm(speed);
}

void m2PID(int speed){
  m2.mode = 1;
  m2.setPoint = speed;
  set_m2_pwm(speed);
}

void m3PID(int speed){
  m3.mode = 1;
  m3.setPoint = speed;
  set_m3_pwm(speed);
}

void m4PID(int speed){
  m4.mode = 1;
  m4.setPoint = speed;
  set_m4_pwm(speed);
}

// ======================================== Set Speed 4 Motor ===================================================== //
void setMotor4PID(int m1, int m2, int m3, int m4){
  m1PID(m1); 
  m2PID(m2); 
  m3PID(m3); 
  m4PID(m4);
}

// ========================================== Kinematik base ======================================================= 
void base_Kinematic(int aX, int aY, int aZ) {
  int frontLeft, frontRight, backLeft, backRight;
  frontLeft  =   aX - aY - (0.5 * aZ);
  frontRight = - aX - aY + (0.5 * aZ);
  backLeft   = - aX - aY + (0.5 * aZ);
  backRight  =   aX - aY + (0.5 * aZ);

drive(frontLeft, frontRight, backLeft, backRight);

}

void drive(int m1,int m2,int m3,int m4){
  m1 = constrain(m1, -255, 255);
  m2 = constrain(m2, -255, 255);
  m3 = constrain(m3, -255, 255);
  m4 = constrain(m4, -255, 255);
  setMotor4PID(m1,m2,m3,m4);
}
