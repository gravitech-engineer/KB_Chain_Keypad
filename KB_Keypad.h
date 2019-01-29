#include "arduino.h"
#include "Wire.h"


#define I2C_default_addr 0x20 //
typedef enum {
  PRESS,
  RELEASE,
  DO
} KEYPAD_EVENT;

typedef void(*KeypadEventCallback)(char);

class KB_Chain_4x4_Keypad
{
  public:
    
    void on(KEYPAD_EVENT event, KeypadEventCallback callback) ;
    void scanKey();
    void begin(uint8_t _addr = I2C_default_addr);



    KeypadEventCallback _callback[3] = { NULL, NULL, NULL };
    int interval = 200;
    unsigned long first_time = 0;
    char keypad[4][4] = {
      {'1', '2', '3', 'A'},
      {'4', '5', '6', 'B'},
      {'7', '8', '9', 'C'},
      {'*', '0', '#', 'D'}
    };
    uint8_t lastKey = 0xFF;
    void digitalWrite(uint8_t pin, uint8_t logic);
    uint8_t digitalRead(uint8_t pin);
  private:
    uint8_t addr;
    uint8_t dataout;
    uint8_t datain;
    void writeRegister(uint8_t value);
    uint8_t readRegister();
};
