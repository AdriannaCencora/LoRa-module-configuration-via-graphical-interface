#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>

#define MODE_NORMAL 0			// can send and recieve
#define MODE_WAKEUP 1			// sends a preamble to waken receiver
#define MODE_POWERDOWN 2		// can't transmit but receive works only in wake up mode
#define MODE_PROGRAM 3			// for programming


class Controller
{
public:
  Controller(uint8_t M0_PIN = 21, uint8_t M1_PIN = 20, uint8_t AUX_PIN = 24);

  bool init();

  void sendByte(uint8_t byte);

  uint8_t getByte();
  uint8_t getVersion();

private:
  // pin variables
  uint8_t _M0;
  uint8_t _M1;
  uint8_t _AUX;

  //file descriptor
  int serialDevice;

};

#endif // CONTROLLER_H
