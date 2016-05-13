#include <AFMotor.h>
#include <Encoder.h>

AF_DCMotor motor(1, MOTOR12_64KHZ); //registers motor pin and sets the pwm freq
volatile long enc_count = 0;
int dir = BACKWARD;
int pos = 12;
int new_pos = 5000;
int i = 0;
int end_pos = 0;

Encoder myEnc(2, 14);

void setup() {
  // all your normal setup code
  Serial.begin(9600);
  home_motor(dir);
  get_carriage_length();
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

//    Serial.print("i: ");
//    Serial.println(i);
//    Serial.print("POS: ");
    Serial.println(pos);
//    Serial.print("nPOS: ");
//    Serial.println(new_pos);
  }
  //pos = myEnc.read();

  motor.run(RELEASE);
  Serial.println("HOME!!");
  myEnc.write(0);
  Serial.println(myEnc.read());
}

void get_carriage_length(){
  motor.setSpeed(200);
  pos = 2323;
  while (new_pos != pos) {
    motor.run(FORWARD);
    i++;
    
    if (i % 10 == 0) {
      pos = new_pos;
      new_pos = myEnc.read();
    }

   /* Serial.print("i: ");
    Serial.println(i);
    Serial.print("POS: ");
    Serial.println(pos);
    Serial.print("nPOS: ");
    Serial.println(new_pos);*/
  }
  
  motor.run(RELEASE);
  Serial.println("END!!");
  end_pos = new_pos;

  while (myEnc.read() > 0){
    motor.setSpeed(200);
    motor.run(BACKWARD);
    //Serial.println(myEnc.read());
  }

  motor.run(RELEASE);
  Serial.println("HOME AGAIN!!");
  Serial.print("Carriage Length: ");
  Serial.println(end_pos);
}

void loop() {
  // put your main code here, to run repeatedly:
  //home_motor();
  //Serial.println(myEnc.read());


}
