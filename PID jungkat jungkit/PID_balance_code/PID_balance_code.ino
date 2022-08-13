#include <Servo.h>
#include <NewPing.h>


///////////////////////Inputs/outputs///////////////////////
Servo myservo;
#define SONAR_NUM 1
#define MAX_DISTANCE 200
NewPing sonar[SONAR_NUM] = {
  NewPing(4, 5, MAX_DISTANCE)
};
///////////////////////////////////////////////////////

////////////////////////Variables///////////////////////
int Read = 0;
float distance = 0.0;
float elapsedTime, time, timePrev;
float distance_previous_error, distance_error;
int period = 50;
///////////////////////////////////////////////////////


///////////////////PID constants///////////////////////
float kp = 9;
float ki = 0.2;
float kd = 3200;
float distance_setpoint = 6;
float PID_p, PID_i, PID_d, PID_total;
///////////////////////////////////////////////////////



void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(125);
  time = millis();
}

void loop() {
  if (millis() > time + period)
  {
    time = millis();
    distance = get_dist(15);
    distance_error = distance_setpoint - distance;
    PID_p = kp * distance_error;
    float dist_diference = distance_error - distance_previous_error;
    PID_d = kd * ((distance_error - distance_previous_error) / period);

    if (-3 < distance_error && distance_error < 3)
    {
      PID_i = PID_i + (ki * distance_error);
    }
    else
    {
      PID_i = 0;
    }

    PID_total = PID_p + PID_i + PID_d;
    PID_total = map(PID_total, -150, 150, 150, 0);

    if (PID_total < 20) {
      PID_total = 20;
    }
    if (PID_total > 160) {
      PID_total = 160;
    }

    myservo.write(PID_total + 30);
    distance_previous_error = distance_error;
  }
}

float get_dist(int n)
{
  long sum = 0;
  for (int i = 0; i < n; i++)
  {
    sum = sum + sonar[0].ping_cm();
  }
  float distance_cm = sum / n;
  return (distance_cm);
}
