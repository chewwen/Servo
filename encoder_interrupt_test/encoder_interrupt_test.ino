#include <AFMotor.h>
#include <Encoder.h>

AF_DCMotor motor(1, MOTOR12_64KHZ); //registers motor pin and sets the pwm freq
volatile long enc_count = 0;
int dir = BACKWARD;
int pos = 12;
int new_pos = 5000;
int i = 0;
Encoder myEnc(2, 14);

void setup() {
  // all your normal setup code
  Serial.begin(9600);
  home_motor(dir);
}

void home_motor(int dir) {
  motor.setSpeed(200);
  //motor.run(FORWARD);
  //delay(1000);
  while (new_pos != pos) {
    motor.run(dir);
    
    i++;
    if (i % 10 == 0) {
      pos = new_pos;
      new_pos = myEnc.read();
    }

    Serial.print("i: ");
    Serial.println(i);
    Serial.print("POS: ");
    Serial.println(pos);
    Serial.print("nPOS: ");
    Serial.println(new_pos);
  }
  //pos = myEnc.read();

  motor.run(RELEASE);
  Serial.println("HOME!!");
  myEnc.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  //home_motor();
  //Serial.println(myEnc.read());


}
