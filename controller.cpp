#include "controller.h"
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <unistd.h>

Controller::Controller(uint8_t M0_PIN, uint8_t M1_PIN, uint8_t AUX_PIN)
{
  _M0 = M0_PIN;
  _M1 = M1_PIN;
  _AUX = AUX_PIN;
}

bool Controller::init()
{
  printf("starting up modules\n");

  if(wiringPiSetupGpio() < 0) {
          printf("failed setting GPIO\n");
          return 1;
  }

  pinMode(_AUX, INPUT);
  pinMode(_M0, OUTPUT);
  pinMode(_M1, OUTPUT);

   // startup in mode 0(normal)
  setMode(MODE_NORMAL);

  // open uart
  if((serialDevice = serialOpen("/dev/ttyS0", 9600)) < 0) {
          printf("failed setting uart\n");
          return false;
    }

  return true;
}

void Controller::setMode(uint8_t mode)
{
  switch (mode) {
    case MODE_NORMAL:
      digitalWrite(_M0, LOW);
      digitalWrite(_M1, LOW);
      break;
    case MODE_WAKEUP:
      digitalWrite(_M0, LOW);
      digitalWrite(_M1, HIGH);
      break;
    case MODE_POWER_SAVING:
      digitalWrite(_M0, HIGH);
      digitalWrite(_M1, LOW);
      break;
    case MODE_SLEEP:
      digitalWrite(_M0, HIGH);
      digitalWrite(_M1, HIGH);
      break;
    default:
      break;
    }
}

void Controller::sendByte(uint8_t byte)
{

}

uint8_t Controller::getByte()
{
  return serialGetchar(serialDevice);
}


bool Controller::readVersion()
{
  _parameters[0] = 0;
  _parameters[1] = 0;
  _parameters[2] = 0;
  _parameters[3] = 0;

  setMode(MODE_SLEEP);
  int msg = 0xC3;

  //That's not final solution, just for tests :o
  write(serialDevice, &msg, 1);
  write(serialDevice, &msg, 1);
  write(serialDevice, &msg, 1);


  //Not sure if I do that correctly... :F
  if (read(serialDevice, _parameters, 4) == -1) {
      printf("error while reading bytes\n");
    }

  _model = _parameters[1];
  _version =  _parameters[2];
  _features = _parameters[3];

  setMode(MODE_NORMAL);

  if (_parameters[0] != 0xC3)
    return false;

  return true;
}

void Controller::displayVersionInfo()
{
  printf("Version number is: %d\n", _version);
  printf("Module model is: %d\n", _model);
  printf("Other module feature: %d\n", _features);

}


