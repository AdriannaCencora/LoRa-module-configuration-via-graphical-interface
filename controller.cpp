#include "controller.h"
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>

Controller::Controller(uint8_t M0_PIN, uint8_t M1_PIN, uint8_t AUX_PIN)
{
  _M0 = M0_PIN;
  _M1 = M1_PIN;
  _AUX = AUX_PIN;
}

bool Controller::init()
{
  pinMode(_AUX, INPUT);
  pinMode(_M0, OUTPUT);
  pinMode(_M1, OUTPUT);

   // startup in mode 0(normal)
  digitalWrite(_M0, 0);
  digitalWrite(_M1, 0);

  // open uart
  if((serialDevice = serialOpen("/dev/ttyAMA0", 9600)) < 0) {
          printf("failed setting uart\n");
          return false;
    }

  return true;
}

void Controller::sendByte(uint8_t byte)
{

}

uint8_t Controller::getByte()
{
  return serialGetchar(serialDevice);
}


uint8_t Controller::getVersion()
{
  return 0;
}
