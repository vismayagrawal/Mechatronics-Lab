#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int dir = 1;
int prox = 1;
int stat = -1;

void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  myservo.attach(5); 
  myservo.write(0); 
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    stat = Serial.read();
    Serial.println(stat);
  }
  
  if(stat == 49){
    prox = 1; 
  }else if(stat == 48){
    prox = 0;
  }
  
  Serial.println(prox);
  if (prox == 1){
    if(pos==180){
      dir = -1;
    }
    else if(pos==0){
      dir = 1;
    }

    pos = pos + dir;
    myservo.write(pos);
    //Serial.println(pos);
  }else if (prox == 0){
  }
  delay(500);
}
