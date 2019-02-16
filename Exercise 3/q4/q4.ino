/*
  Reading a serial ASCII-encoded string.

  This sketch demonstrates the Serial parseInt() function.
  It looks for an ASCII string of comma-separated values.
  It parses them into ints, and uses those to fade an RGB LED.

  Circuit: Common-Cathode RGB LED wired like so:
  - red anode: digital pin 3
  - green anode: digital pin 5
  - blue anode: digital pin 6
  - cathode: GND

  created 13 Apr 2012
  by Tom Igoe
  modified 14 Mar 2016
  by Arturo Guadalupi

  This example code is in the public domain.
*/
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 13, en = 12, d4 = 8, d5 = 4, d6 = 3, d7 = 2;
const int rs = 2, en = 3, d4 = 4, d5 = 8, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include <Servo.h>

Servo myservo_1;

int ldr1 = 0;
int ldr2 = 0;
int ldr3 = 0;

int r_I = 245;
int g_I = 245;
int b_I = 245;
int maximum = 0;
int inside = 1;

int red = 11;
int green = 10;
int blue = 9;
int i=1;

void setup() {
  Serial.begin(9600);
//  myservo_1.attach(5);
//  myservo_1.write(50); 
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(A2, INPUT);
  lcd.begin(16, 2);
  
}

void AutoCalibrate(){
  analogWrite(red, r_I);
  delay(150);
  ldr1 = analogRead(A2);
  analogWrite(red, 0);
  
  analogWrite(green, g_I);
  delay(150);
  ldr2 = analogRead(A2);
  analogWrite(green, 0);
  
  analogWrite(blue, b_I);
  delay(150);
  ldr3 = analogRead(A2);
  analogWrite(blue, 0);
  
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("R:");
  lcd.print(ldr1);
  
  lcd.print(" G:");
  lcd.print(ldr2);

  lcd.setCursor(0, 1);
  lcd.print("B:");
  lcd.print(ldr3);
  lcd.display();
  delay(100);

  if (inside ==1){
    if (ldr1>ldr2 && ldr1>ldr3){
      maximum =ldr1;
      }
    else if(ldr2>ldr3){
      maximum =ldr2;
      }
    else{
      maximum =ldr3;
      }
  
    if(maximum - ldr1 > 20){
        r_I = r_I - 1;
      }
    if(maximum - ldr2 > 20){
        g_I = g_I - 1;
      }
    if(maximum - ldr3 > 20){
        b_I = b_I - 1;
      } 

  Serial.println(r_I);
  Serial.println(g_I);
  Serial.println(b_I);
    if(maximum - ldr1<20 && maximum - ldr2<20 && maximum - ldr3<20){
      inside =0;
      Serial.println("DONE");
      }
  }  
  
}

void loop() {
  
  AutoCalibrate();



  
}
  
