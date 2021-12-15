#include <PS2X_lib.h>

#define ENA 3      //ENA
#define MOTORA_1 4 //IN3
#define MOTORA_2 5 //IN4
#define MOTORB_1 8 //IN1
#define MOTORB_2 7 //IN2
#define ENB 6      //ENB

int motor_right_speed = 0;
int motor_left_speed = 0;

PS2X ps2x; 

int error = 0; 
byte type = 0;
byte vibrate = 0;

void setup(){

 pinMode(ENA, OUTPUT);
 pinMode(MOTORA_1, OUTPUT);
 pinMode(MOTORA_2, OUTPUT);
 pinMode(ENB, OUTPUT);
 pinMode(MOTORB_1, OUTPUT);
 pinMode(MOTORB_2, OUTPUT);

 digitalWrite(ENA,0);
 digitalWrite(ENB,0);
 
 Serial.begin(57600);
  
 error = ps2x.config_gamepad(13,11,10,12, true, true);   
  
 if(error == 0){
  Serial.println("Found Controller, configured successful");
 }
   
 else if(error == 1)
  Serial.println("No controller found, check wiring or reset the Arduino");
   
 else if(error == 2)
  Serial.println("Controller found but not accepting commands");
  
 else if(error == 3)
  Serial.println("Controller refusing to enter Pressures mode, may not support it.");
   
 // Check for the type of controller
 type = ps2x.readType();
 switch(type) {
  case 0:
    Serial.println("Unknown Controller type");
    break;
  case 1:
    Serial.println("DualShock Controller Found");
    break;
  case 2:
    Serial.println("GuitarHero Controller Found");
    break;
  }
}

void loop(){
   
 if(error == 1) 
  return; 
  
 else { 
  
    ps2x.read_gamepad(false, vibrate); 
    
    int nJoyX = ps2x.Analog(PSS_LX); 
    int nJoyY = ps2x.Analog(PSS_LY); 
    
  
    nJoyX = map(nJoyX, 0, 255, -1023, 1023);
    nJoyY = map(nJoyY, 0, 255, 1023, -1023);
  
    int nMotMixL; 
    int nMotMixR; 
  
    float fPivYLimit = 1023.0;
        
    float   nMotPremixL;    
    float   nMotPremixR;    
    int     nPivSpeed;      
    float   fPivScale;      
  
    if (nJoyY >= 0) {
      // Forward
      nMotPremixL = (nJoyX>=0)? 1023.0 : (1023.0 + nJoyX);
      nMotPremixR = (nJoyX>=0)? (1023.0 - nJoyX) : 1023.0;
    } else {
      // Reverse
      nMotPremixL = (nJoyX>=0)? (1023.0 - nJoyX) : 1023.0;
      nMotPremixR = (nJoyX>=0)? 1023.0 : (1023.0 + nJoyX);
    }
  
    nMotPremixL = nMotPremixL * nJoyY/1023.0;
    nMotPremixR = nMotPremixR * nJoyY/1023.0;
  
    nPivSpeed = nJoyX;
    fPivScale = (abs(nJoyY)>fPivYLimit)? 0.0 : (1.0 - abs(nJoyY)/fPivYLimit);
  
    nMotMixL = (1.0-fPivScale)*nMotPremixL + fPivScale*( nPivSpeed);
    nMotMixR = (1.0-fPivScale)*nMotPremixR + fPivScale*(-nPivSpeed);
    
    motor_left_speed = nMotMixL;
    motor_right_speed = nMotMixR;
  
    if (motor_right_speed > 50) {
      digitalWrite(MOTORB_1,HIGH);
      digitalWrite(MOTORB_2,LOW);
    }
    else if (motor_right_speed < -50) {
      digitalWrite(MOTORB_1,LOW);
      digitalWrite(MOTORB_2, HIGH);
      
    }
    else {
      digitalWrite(MOTORB_1, LOW);
      digitalWrite(MOTORB_2, LOW);
    }
  
    if (motor_left_speed > 50) {
      digitalWrite(MOTORA_1, LOW);
      digitalWrite(MOTORA_2, HIGH);
    }
    else if (motor_left_speed < -50) {
      digitalWrite(MOTORA_1,HIGH);
      digitalWrite(MOTORA_2,LOW);
    }
    else {
      digitalWrite(MOTORA_1, LOW);
      digitalWrite(MOTORA_2, LOW);
    }
    analogWrite(ENA, abs(motor_left_speed));
    analogWrite(ENB, abs(motor_right_speed));
    if (abs(motor_left_speed > 50) || abs(motor_left_speed > 50)) {
      Serial.println("Moving!");
    }
   
   delay(50);
 }    
}
