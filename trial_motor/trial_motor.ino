 /* Increase/Decrease Motor speed with S-shaped velocity profile
  * 
  * Sketch by Benedict Tan
  * v. 2 -- 18042016
  *
  */  

#include <elapsedMillis.h>  //independent timer
#include <AFMotor.h>  //ADAfruit lib for motor control
#include <Encoder.h>

AF_DCMotor motor(1, MOTOR12_64KHZ); //registers motor pin and sets the pwm freq
Encoder myEnc(2,14);

// Define constants
#define SSSpeed       255   // Motor steady-state speed (0 to 255 as a PWM duty cycle)
#define SSStart       0    // Time to start of steady-state (seconds)
#define SSEnd         5    // Time to end of steady-state (seconds)
#define rampEnd       10    // Time to end of run

// Define variables
elapsedMillis timer0; //millisecond timer
long interval = 0; //use long so that interval can be larger than 32767 (in milliseconds)
double duty = 0;
// ========================================================================================================================

void setup()
{
  // initiaize serial for debug
  Serial.begin(9600);
  
}

// ========================================================================================================================

// Increase pwm duty cycle based on length of time
void up(int targetSpeed, int targetStart, int dir)
{
  timer0 = 0;
  interval = (targetStart) * 1000L; //need to put L so that interval becomes a long variable

  while (timer0 < interval)
  {
    duty = (targetSpeed / 2) * (cos((((timer0) * PI)/interval)+PI) + 1);  //S-shape equation
    motor.setSpeed(duty); //sets pwm pulse based on equation
    motor.run(dir); //sets direction of motor

    //debug messages
    Serial.print(duty);
    Serial.print("\t");
    Serial.println("UP");
  }
}
// ========================================================================================================================
// Decrease pwm duty cycle based on length of time
void down(int targetStart, int targetEnd, int dir)
{
  timer0 = 0;
  interval = (targetEnd - targetStart) * 1000L;

  while (timer0 < interval)
  {
    duty = (SSSpeed / 2) * (cos(((PI / (interval)) * ((targetStart * 1000) + timer0)) - ((PI * targetStart * 1000) / (interval))) + 1);
    motor.setSpeed(duty);
    motor.run(dir);

    //debug messages
    Serial.print(duty);
    Serial.print("\t");
    Serial.print(timer0);
    Serial.print("\t");
    Serial.print(interval);
    Serial.print("\t");
    Serial.println("DOWN");

  }
}
// ========================================================================================================================
// Hold pwm at target value for given time
void hold(int targetStart, int targetEnd, int dir)
{
  timer0 = 0;
  interval = (targetEnd - targetStart) * 1000L;
  while (timer0 < interval) {
    motor.setSpeed(SSSpeed);
    motor.run(dir);
    
    //debug messages
    //Serial.println(timer0);
    Serial.print("dir");
    Serial.print("\t");
    Serial.println("HOLD");
  }
}
// ========================================================================================================================
// Hold pwm at target value for given time
void hold2(int targetStart, int targetEnd, int dir)
{
  //timer0 = 0;
  interval = (targetEnd - targetStart) * 1000L;
  motor.setSpeed(SSSpeed);
  motor.run(dir);
  delay(interval);
    
    //debug messages
    //Serial.println(timer0);
    Serial.print("dir");
    Serial.print("\t");
    Serial.print("HOLD");
    Serial.print("\t");
    Serial.println(myEnc.read());
  }

// ========================================================================================================================

void loop()
{
  Serial.println("Waiting..");
  delay(1000);
  //Ramp UP
  //up(SSSpeed, SSStart, FORWARD);
  //Hold
  hold2(SSStart, SSEnd, FORWARD);
  //Ramp DOWN
  //down(SSEnd, rampEnd, FORWARD);
  delay(1000);
  
  //Ramp UP
  //up(SSSpeed, SSStart, BACKWARD);
  //Hold
  hold2(SSStart, SSEnd, BACKWARD);
  //Ramp DOWN
  //down(SSEnd, rampEnd, BACKWARD);
  //delay(1000);
  
}
