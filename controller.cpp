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
    delay(100);
  // open uart
  if((_serialDevice = serialOpen("/dev/ttyAMA0", 9600)) < 0) {
          printf("failed setting uart\n");
          return false;
    }

  return true;
}

void Controller::setMode(uint8_t mode)
{
  delay(40);
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

  delay(40);
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

 // serialFlush(_serialDevice);

  //That's not final solution, just for tests :o
  write(_serialDevice, &msg, 1);
  write(_serialDevice, &msg, 1);
  write(_serialDevice, &msg, 1);

  delay(10);

    read(_serialDevice, _parameters, 6);

   _save = _parameters[0];
   _addressHigh = _parameters[1];
   _addressLow = _parameters[2];
   _sped = _parameters[3];
   _channel = _parameters[4];
   _options = _parameters[5];


    _parityBit = (_sped & 0xC0) >> 6;
    _UARTBaudRate = (_sped & 0x38) >> 3;
    _airDataRate = _sped & 0x07;

    _optionFixedTransmission = (_options & 0x80) >> 7;
    _optionIODriveMode = (_options & 0x40) >> 6;
    _optionWakeUpTime = (_options & 0x38) >> 3;
    _optionFEC = (_options &  0x04) >> 2;
    _optionPower = _options & 0x03;

    setMode(MODE_NORMAL);


   if (_save != 0xC0) {
        qDebug() <<"failed to read. not valid first byte";
         return false;
   }

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

  serialFlush(_serialDevice);

  write(_serialDevice, &msg, 1);
  write(_serialDevice, &msg, 1);
  write(_serialDevice, &msg, 1);

 read(_serialDevice, _parameters, 4);

  _save = _parameters[0];
  _model = _parameters[1];
  _version =  _parameters[2];
  _features = _parameters[3];

  setMode(MODE_NORMAL);

  if (_parameters[0] != 0xC3) {
      qDebug() <<"failed to read. not valid first byte";
    return false;
  }

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


  qDebug() << "---OPTIONS----";
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
  qDebug() << "0: " << hex << _save;
  qDebug() << "Version number is: " << hex << _version;
  qDebug() << "Module model is: " << hex << _model;
  qDebug() << "Other module feature: " << hex << _features;
}


