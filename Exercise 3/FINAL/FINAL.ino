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
Servo myservo_2;

int ldr1 = 0;
int ldr2 = 0;
int ldr3 = 0;
int d_ldr1 = 0;
int d_ldr2 = 0;
int d_ldr3 = 0;

int r_I = 245;
int g_I = 245;
int b_I = 245;
int maximum = 0;
int inside = 1;

int red = 11;
int green = 10;
int blue = 9;
int i = 1;

int cal = 0;
int color = 0;
int detected_color = -1;

int em = 7;

void setup() {
  Serial.begin(9600);
  myservo_1.attach(5);
  myservo_1.write(40);
  myservo_2.attach(6);
  myservo_2.write(160);
  delay(100);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(em, OUTPUT); //EM

  pinMode(A2, INPUT);
  lcd.begin(16, 2);

}

void AutoCalibrate() {
  while (inside == 1) {
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

    if (inside == 1) {
      if (ldr1 > ldr2 && ldr1 > ldr3) {
        maximum = ldr1;
      }
      else if (ldr2 > ldr3) {
        maximum = ldr2;
      }
      else {
        maximum = ldr3;
      }

      if (maximum - ldr1 > 20) {
        r_I = r_I - 1;
      }
      if (maximum - ldr2 > 20) {
        g_I = g_I - 1;
      }
      if (maximum - ldr3 > 20) {
        b_I = b_I - 1;
      }

      Serial.println(r_I);
      Serial.println(g_I);
      Serial.println(b_I);
      if (maximum - ldr1 < 20 && maximum - ldr2 < 20 && maximum - ldr3 < 20) {
        inside = 0;
        Serial.println("DONE");
      }
    }
  }
}

void ManualCalibrate() {
  while (inside == 1) {
    read_ldr();
    if (inside == 1) {
      if (ldr1 > ldr2 && ldr1 > ldr3) {
        maximum = ldr1;
      }
      else if (ldr2 > ldr3) {
        maximum = ldr2;
      }
      else {
        maximum = ldr3;
      }
      Serial.println(r_I);
      Serial.println(g_I);
      Serial.println(b_I);
      if (maximum - ldr1 < 60 && maximum - ldr2 < 60 && maximum - ldr3 < 60) {
        inside = 0;
        Serial.println("DONE");
      }
    }
  }
  d_ldr1 = ldr1;
  d_ldr2 = ldr2;
  d_ldr3 = ldr3;


}

void read_ldr() {
  digitalWrite(red, HIGH);
  delay(150);
  ldr1 = analogRead(A2);
  digitalWrite(red, 0);

  digitalWrite(green, HIGH);
  delay(150);
  ldr2 = analogRead(A2);
  digitalWrite(green, 0);

  digitalWrite(blue, HIGH);
  delay(150);
  ldr3 = analogRead(A2);
  digitalWrite(blue, 0);

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
}

void reach_color() {
  int pos = 40;
  int in = 0;
  inside = 1;

  for (pos = 40; pos <= 160; pos += 5) { // goes from 0 degrees to 180 degrees
    myservo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(700);                       // waits 15ms for the servo to reach the position
    read_ldr();
    Serial.println(pos);
    int a = min(min(ldr1, ldr2), ldr3);
    int distance = 50;


    if (a == ldr1 && ldr2 - d_ldr2 > distance && ldr3 - d_ldr3 > distance) {
      Serial.println("Red");
      detected_color = 0;
      if (color == detected_color) {
        Serial.println(detected_color);
        Serial.println(color);
        in += 1;
        if (in == 2) {
          break;
        }
      }
    }
    if (a == ldr2 && ldr1 - d_ldr1 > distance && ldr3 - d_ldr3 > distance) {
      Serial.println("Green");
      detected_color = 1;
      if (color == detected_color) {
        Serial.println(detected_color);
        Serial.println(color);
        in += 1;
        if (in == 2) {
          break;
        }
      }
    }
    if (a == ldr3 && ldr1 - d_ldr1 > distance && ldr2 - d_ldr2 > distance) {
      Serial.println("Blue");
      detected_color = 2;
      if (color == detected_color) {
        Serial.println(detected_color);
        Serial.println(color);
        in += 1;
        if (in == 2) {
          break;
        }
      }
    }
  }

}

void loop() {

  ////////// Calibration

  Serial.println("Please enter 0 for Manual Calibration and 1 for Auto Calibration");
  while (Serial.available() == 0) {}

  while (Serial.available() > 0) {
    cal = Serial.parseInt();
    Serial.println(cal);
    if (cal == 1) {
      Serial.println("Start Auto");
      AutoCalibrate();
      Serial.println("Done Auto");
    }
    else if (cal == 0) {
      Serial.println("Start Manual");
      ManualCalibrate();
      Serial.println("Done Manual");
    }
  }

  //////// Colour

  Serial.println("Pick Up: Please enter 0, 1, 2 for R, G, B respectively");
  while (Serial.available() == 0) {}

  while (Serial.available() > 0) {
    color = Serial.parseInt();
  }

  reach_color();

  Serial.println("Desired input color Reached");
  myservo_2.write(10);
  digitalWrite(em, HIGH);
  delay(2000);

  myservo_2.write(160);
  delay(2000);

  Serial.println("Drop: Please enter 0, 1, 2 for R, G, B respectively");
  while (Serial.available() == 0) {}

  while (Serial.available() > 0) {
    color = Serial.parseInt();
  }

  reach_color();
  Serial.println("Desired output color Reached");
  myservo_2.write(10);
  delay(2000);
  digitalWrite(em, LOW);
  delay(1000);
  myservo_2.write(160);

  Serial.println("THANKS, HAVE A NICE DAY");
  delay(1000);
}
