#include <PS2X_lib.h>  //for v1.6

// These are used to set the direction of the bridge driver.
#define ENA 3      //ENA
#define MOTORA_1 4 //IN3
#define MOTORA_2 5 //IN4
#define MOTORB_1 8 //IN1
#define MOTORB_2 7 //IN2
#define ENB 6      //ENB

int motor_right_speed = 0;
int motor_left_speed = 0;

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte type = 0;
byte vibrate = 0;

void setup(){

 // Configure output pins
 pinMode(ENA, OUTPUT);
 pinMode(MOTORA_1, OUTPUT);
 pinMode(MOTORA_2, OUTPUT);
 pinMode(ENB, OUTPUT);
 pinMode(MOTORB_1, OUTPUT);
 pinMode(MOTORB_2, OUTPUT);

 // Disable both motors
 digitalWrite(ENA,0);
 digitalWrite(ENB,0);
 
 // Start serial communication
 Serial.begin(57600);
  
 error = ps2x.config_gamepad(13,11,10,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
 // Check for error
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

// Main loop
void loop(){
   
 if(error == 1) //skip loop if no controller found
  return; 
  
 else { //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate); // disable vibration of the controller   
    
    int nJoyX = ps2x.Analog(PSS_LX); // read x-joystick
    int nJoyY = ps2x.Analog(PSS_LY); // read y-joystick
    
  
    nJoyX = map(nJoyX, 0, 255, -1023, 1023);
    nJoyY = map(nJoyY, 0, 255, 1023, -1023);
  
    // OUTPUTS
    int nMotMixL; // Motor (left) mixed output
    int nMotMixR; // Motor (right) mixed output
  
    // CONFIG
    // - fPivYLimt  : The threshold at which the pivot action starts
    //                This threshold is measured in units on the Y-axis
    //                away from the X-axis (Y=0). A greater value will assign
    //                more of the joystick's range to pivot actions.
    //                Allowable range: (0..+127)
    float fPivYLimit = 1023.0;
        
    // TEMP VARIABLES
    float   nMotPremixL;    // Motor (left) premixed output
    float   nMotPremixR;    // Motor (right) premixed output
    int     nPivSpeed;      // Pivot Speed
    float   fPivScale;      // Balance scale between drive and pivot
  
    // Calculate Drive Turn output due to Joystick X input
    if (nJoyY >= 0) {
      // Forward
      nMotPremixL = (nJoyX>=0)? 1023.0 : (1023.0 + nJoyX);
      nMotPremixR = (nJoyX>=0)? (1023.0 - nJoyX) : 1023.0;
    } else {
      // Reverse
      nMotPremixL = (nJoyX>=0)? (1023.0 - nJoyX) : 1023.0;
      nMotPremixR = (nJoyX>=0)? 1023.0 : (1023.0 + nJoyX);
    }
  
    // Scale Drive output due to Joystick Y input (throttle)
    nMotPremixL = nMotPremixL * nJoyY/1023.0;
    nMotPremixR = nMotPremixR * nJoyY/1023.0;
  
    // Now calculate pivot amount
    // - Strength of pivot (nPivSpeed) based on Joystick X input
    // - Blending of pivot vs drive (fPivScale) based on Joystick Y input
    nPivSpeed = nJoyX;
    fPivScale = (abs(nJoyY)>fPivYLimit)? 0.0 : (1.0 - abs(nJoyY)/fPivYLimit);
  
    // Calculate final mix of Drive and Pivot
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
