
#include "KB_Keypad.h"

KB_Chain_4x4_Keypad key;

void setup() {
  key.begin(0x20);                          //  Setting address default 0x20 OR 0x21
  Serial.begin(9600);
  Serial.println("I/O Start");
}

void loop() {
  key.digitalWrite(1, HIGH);                //  PIN 1 is HIGH
  delay(250);
  key.digitalWrite(1, LOW);                 //  PIN 1 is LOW
  delay(250);
}