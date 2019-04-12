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
  if((_serialDevice = serialOpen("/dev/ttyAMA0", 9600)) < 0) {
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
uint8_t Controller:: getMode()
{
    digitalRead(_M0);
    digitalRead(_M1);
    if(_M0==LOW && _M1==LOW)
            return MODE_NORMAL;
    if(_M0==LOW && _M1==HIGH)
            return MODE_WAKEUP;
    if(_M0==HIGH && _M1==LOW)
            return MODE_POWER_SAVING;
    if(_M0==HIGH && _M1==HIGH)
            return MODE_SLEEP;
    return 1;         //<-be careful with that, just for testing
}

void Controller::buildSpedByte()
{

}

void Controller::buildOptionByte()
{

}


//TODO: Extract setting variable's values to specific functions
bool Controller::readAllParameters()
{
  _parameters[0] = 0;
  _parameters[1] = 0;
  _parameters[2] = 0;
  _parameters[3] = 0;
  _parameters[4] = 0;
  _parameters[5] = 0;

  setMode(MODE_SLEEP);
  int msg = 0xC1;

  //That's not final solution, just for tests :o
  write(_serialDevice, &msg, 1);
  write(_serialDevice, &msg, 1);
  write(_serialDevice, &msg, 1);

  if (read(_serialDevice, _parameters, 6) == -1) {
      qDebug() << "error while reading bytes : ";
    }
   _save = _parameters[0];
   _addressHigh = _parameters[1];
   _addressLow = _parameters[2];
   _sped = _parameters[3];
   _channel = _parameters[4];
   _options = _parameters[5];

   setMode(MODE_NORMAL);

    _parityBit = (_sped & 0xC0) >> 6;
    _UARTBaudRate = (_sped & 0x38) >> 3;
    _airDataRate = _sped & 0x07;

    _optionFixedTransmission = (_options & 0x80) >> 7;
    _optionIODriveMode = (_options & 0x40) >> 6;
    _optionWakeUpTime = (_options & 0x38) >> 3;
    _optionFEC = (_options &  0x04) >> 2;
    _optionPower = _options & 0x03;


   if (_save != msg)
     return false;

   return true;

}


//uint8_t Controller::getByte()
//{
//  return serialGetchar(_serialDevice);
//}


bool Controller::readVersionAndModel()
{

  //Unnecessary, as I think (???)
  _parameters[0] = 0;
  _parameters[1] = 0;
  _parameters[2] = 0;
  _parameters[3] = 0;

  setMode(MODE_SLEEP);
  int msg = 0xC3;

  write(_serialDevice, &msg, 1);
  write(_serialDevice, &msg, 1);
  write(_serialDevice, &msg, 1);


  //Not sure if I do that correctly... :F
  if (read(_serialDevice, _parameters, 4) == -1) {
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

void Controller::displayAllParameters()
{

  qDebug() << "----Default parameter values: C0 00 00 1A 06 44---- ";
  qDebug() << "0: " << hex << _save;
  qDebug() << "1: " << hex << _addressHigh;
  qDebug() << "2: " << hex << _addressLow;
  qDebug() << "3: " << hex << _sped;
  qDebug() << "4: " << hex << _channel;
  qDebug() << "5: " << hex << _options;


  qDebug() << "---OPTIONS---- " << _version;
  qDebug() << "parity: " << bin << _parityBit;
  qDebug() << "_UARTBaudRate: " << bin << _UARTBaudRate;
  qDebug() << "_airDataRate: " << bin << _airDataRate;
  qDebug() << "_optionFixedTransmission: " << bin << _optionFixedTransmission;
  qDebug() << "_optionIODriveMode" << bin << _optionIODriveMode;
  qDebug() << "_optionWakeUpTime" << bin << _optionWakeUpTime;
  qDebug() << "_optionFEC: " << bin << _optionFEC;
  qDebug() << "_optionPower: " << bin << _optionPower;


}

void Controller::displayModelVersionFeature()
{
  qDebug() << "Version number is: " << hex << _version;
  qDebug() << "Module model is: " << hex << _model;
  qDebug() << "Other module feature: " << hex << _features;
}
