#include "KB_Keypad.h"


void KB_Chain_4x4_Keypad::on(KEYPAD_EVENT event, KeypadEventCallback callback)
{
  _callback[event] = callback;
}


void KB_Chain_4x4_Keypad::begin(uint8_t _addr)
{
#if defined(ESP32) || defined(ESP8266)
    Wire.begin(4, 5);
#else
    Wire.begin();
#endif
    addr = _addr;
    datain = 0;
    dataout = 0xFF;
}



void KB_Chain_4x4_Keypad::scanKey() {
  uint8_t row = 0, col = 0;
  if (millis() - first_time >= interval) {
    Wire.beginTransmission(addr);
    Wire.write(0x0F);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)addr, (uint8_t)1);
    while (Wire.available()) {
      switch (Wire.read()) {
        case 0x0E : row = 1; break;
        case 0x0D : row = 2; break;
        case 0x0B : row = 3; break;
        case 0x07 : row = 4; break;
        default : row = 0;
      }
    }

    Wire.beginTransmission(addr);
    Wire.write(0xF0);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)addr, (uint8_t)1);
    while (Wire.available()) {
      switch (Wire.read()) {
        case 0xE0 : col = 1; break;
        case 0xD0 : col = 2; break;
        case 0xB0 : col = 3; break;
        case 0x70 : col = 4; break;
        default : col = 0;
      }
    }
    first_time  =  millis();
  
    if (row > 0 && col > 0) {
      if (lastKey == 0xFF) {
        if (_callback[PRESS]) {
            _callback[PRESS](keypad[row-1][col-1]);
          }
      }
      if (lastKey =- keypad[row - 1][col - 1]) {
        if (_callback[DO]) {
            _callback[DO](keypad[row-1][col-1]);
          }
      }
      lastKey = keypad[row - 1][col - 1];
    } else {
      if (lastKey != 0xFF) {
        if (_callback[RELEASE]) {
            _callback[RELEASE](lastKey);
          }
        lastKey = 0xFF;
      }
    }
  }
}


void KB_Chain_4x4_Keypad::writeRegister(uint8_t value)
{
  Wire.beginTransmission(addr);
  // Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}


uint8_t KB_Chain_4x4_Keypad::readRegister()
{
  // Wire.beginTransmission(addr);
  // Wire.endTransmission();
  // Wire.requestFrom((uint8_t)addr, 1);

  if (Wire.requestFrom(addr, (uint8_t)1) != 1)
  {
    return datain; // last value
  }
  datain = Wire.read();
  return datain;
}

void KB_Chain_4x4_Keypad::digitalWrite(uint8_t pin, uint8_t logic){
  if (pin > 7)
  {
    return;
  }
  if (logic == LOW)
  {
    dataout &= ~(1 << pin);
  }
  else
  {
    dataout |= (1 << pin);
  }
  writeRegister(dataout);
  
}
uint8_t KB_Chain_4x4_Keypad::digitalRead(uint8_t pin){
  if (pin > 7)
  {
    return 0;
  }
  readRegister();
  return (datain & (1 << pin)) > 0;
}
