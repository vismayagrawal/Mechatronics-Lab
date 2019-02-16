/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Button
*/
// constants won't change. They're used here to set pin numbers:
#include <Servo.h>

Servo myservo;

const int buttonPin_1 = 7;     // the number of the pushbutton pin
const int buttonPin_2 = 8;

// variables will change:
int buttonState_1 = 0;
int buttonState_2 = 0; // variable for reading the pushbutton status
int buttonPushCounter=0;
int lastButtonState_1=0;
int lastButtonState_2=0;
int pos = 90; 

void setup() {;
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin_1, INPUT_PULLUP);
  pinMode(buttonPin_2, INPUT_PULLUP);
  
  Serial.begin(9600);
  myservo.attach(5);
  myservo.write(90);
}

void loop() {
  // read the pushbutton input pin: 
  buttonState_1 = digitalRead(buttonPin_1);
  buttonState_2 = digitalRead(buttonPin_2);

  
  // compare the buttonState to its previous state
  if (buttonState_1 != lastButtonState_1) {
    // if the state has changed, increment the counter
    if (buttonState_1 == LOW) {
      // if the current state is HIGH then the button went from off to on:
      pos = pos + 1;
      Serial.println(pos);
      myservo.write(pos);
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }

  if (buttonState_2 != lastButtonState_2) {
    // if the state has changed, increment the counter
    if (buttonState_2 == LOW) {
      // if the current state is HIGH then the button went from off to on:
      pos = pos - 1;
      Serial.println(pos);
      myservo.write(pos);
     }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState_1 = buttonState_1;
  lastButtonState_2 = buttonState_2;
}
