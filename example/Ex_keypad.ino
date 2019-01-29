
#include "KB_Keypad.h"

KB_Chain_4x4_Keypad key;

void setup() {
  key.begin(0x20);                          //  Setting address default 0x20 OR 0x21
  Serial.begin(9600);
  Serial.println("Keypad Start");
  key.on(PRESS,[](char key){                //  Event for get character
    Serial.println(key);
  });
}

void loop() {
  key.scanKey();                            //  Scan key from keypad
}