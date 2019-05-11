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

  setPinModes();
  setMode(MODE_NORMAL);

  if(!openUARTConnection()) {
      printf("Failed setting uart.\n");
      return false;
    }

  if(!readAllParameters()) {
      printf("Cannot read parameters.\n");
      return false;
    }
  return true;
}

bool Controller::openUARTConnection() {
  _fileDescriptorOfDevice = serialOpen("/dev/ttyAMA0", 9600);
  if (_fileDescriptorOfDevice < 0) {
      return false;
    }
  return true;
}

void Controller::setPinModes() {
  pinMode(_AUX, INPUT);
  pinMode(_M0, OUTPUT);
  pinMode(_M1, OUTPUT);
}

void Controller::close() {
  serialClose(_fileDescriptorOfDevice);
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

uint8_t Controller::getMode() {
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

bool Controller::readVersionAndModel()
{
  setMode(MODE_SLEEP);
  uint8_t msg [3] = {0xC3, 0xC3, 0xC3};

  serialFlush(_fileDescriptorOfDevice);

  if (write(_fileDescriptorOfDevice, &msg, sizeof(msg)) < 0) {
      return false;
    }

  if (read(_fileDescriptorOfDevice, _parameters, 4) < 0) {
      return false;
    }

  serialFlush(_fileDescriptorOfDevice);

  _model = _parameters[1];
  _version =  _parameters[2];
  _features = _parameters[3];

  setMode(MODE_NORMAL);

  return true;
}

bool Controller::reset() {
  setMode(MODE_SLEEP);
  uint8_t msg [3] = {0xC4, 0xC4, 0xC4};

  serialFlush(_fileDescriptorOfDevice);

  if (write(_fileDescriptorOfDevice, &msg, sizeof(msg)) < 0) {
      return false;
    }

  setMode(MODE_NORMAL);

  return true;
}
bool Controller::saveParameters(uint8_t saveLifeSpan) {
  setMode(MODE_SLEEP);

  _save = saveLifeSpan;
  uint8_t parametersToBeSaved [6] = {_save, _addressHigh, _addressLow, _speed, _channel, _options };
  serialFlush(_fileDescriptorOfDevice);

  if (write(_fileDescriptorOfDevice, &parametersToBeSaved, sizeof(parametersToBeSaved)) < 0) {
      return false;
    }
  delay(60);
  setMode(MODE_NORMAL);

  return true;
}


bool Controller::readAllParameters()
{
  setMode(MODE_SLEEP);

  uint8_t msg [3]  = {0xC1, 0xC1, 0xC1};
  serialFlush(_fileDescriptorOfDevice);

  if (write(_fileDescriptorOfDevice, &msg, sizeof(msg)) < 0) {
      return false;
    }

  delay(60);

  if (read(_fileDescriptorOfDevice, _parameters, 6) < 0) {
      return false;
    }

  assignReadSettingsToVariables();

  setMode(MODE_NORMAL);

  return true;
}

void Controller::assignReadSettingsToVariables() {

  _save = _parameters[0];
  _addressHigh = _parameters[1];
  _addressLow = _parameters[2];
  _speed = _parameters[3];
  _channel = _parameters[4];
  _options = _parameters[5];

  _parityBit = (_speed & 0xC0) >> 6;
  _UARTBaudRate = (_speed & 0x38) >> 3;
  _airDataRate = _speed & 0x07;

  _optionFixedTransmission = (_options & 0x80) >> 7;
  _optionIODriveMode = (_options & 0x40) >> 6;
  _optionWakeUpTime = (_options & 0x38) >> 3;
  _optionFEC = (_options &  0x04) >> 2;
  _optionPower = _options & 0x03;

}

void Controller::setSave(uint8_t val) {
  _save = val;
}

void Controller::setAdressHigh(uint8_t val) {
  _addressHigh = val;
}

void Controller::setAdressLow(uint8_t val) {
  _addressLow = val;
}

void Controller::setSpeed(uint8_t val) {
  _speed = val;
}
void Controller::setChannel(uint8_t val) {
  _channel = val;
}

void Controller::setOptions(uint8_t val) {
  _options = val;
}


void Controller::setParityBit(uint8_t parityBit) {
  _parityBit = parityBit;
  buildSpeedByte();
}

void Controller::setUARTBaudRate(uint8_t UARTBaudRate) {
  _UARTBaudRate = UARTBaudRate;
  buildSpeedByte();
}

void Controller::setAirDataRate(uint8_t airDataRate) {
  _airDataRate = airDataRate;
  buildSpeedByte();
}

void Controller::setOptionFixedTransmission(uint8_t optionFixedTransmission) {
  _optionFixedTransmission = optionFixedTransmission;
  buildOptionByte();
}

void Controller::setOptionIODriveMode(uint8_t optionIODriveMode) {
  _optionIODriveMode = optionIODriveMode;
  buildOptionByte();
}

void Controller::setOptionWakeUpTime(uint8_t optionWakeUpTime) {
  _optionWakeUpTime = optionWakeUpTime;
  buildOptionByte();
}

void Controller::setOptionFEC(uint8_t optionFEC) {
  _optionFEC = optionFEC;
  buildOptionByte();
}

void Controller::setOptionPower(uint8_t optionPower) {
  _optionPower = optionPower;
  buildOptionByte();
}


void Controller::buildSpeedByte()
{
  _speed = (_parityBit << 6) | (_UARTBaudRate << 3) | _airDataRate;
}

void Controller::buildOptionByte()
{
  _options = (_optionFixedTransmission << 7) | (_optionIODriveMode << 6) | (_optionWakeUpTime << 3) | (_optionFEC << 2) | _optionPower;
}


uint8_t Controller::getModel() {
  return _model;
}

uint8_t Controller::getVersion() {
  return _version;
}

uint8_t Controller::getFeature() {
  return _features;
}

uint8_t Controller::getSave() {
  return _save;
}

uint8_t Controller::getAddressHigh() {
  return _addressHigh;
}

uint8_t Controller::getAddressLow() {
  return _addressLow;
}

uint8_t Controller::getSpeed() {
  return _speed;
}

uint8_t Controller::getChannel() {
  return _channel;
}

uint8_t Controller::getOptions() {
  return _options;
}

uint8_t Controller::getOptionFEC() {
  return _optionFEC;
}
uint8_t Controller::getParityBit() {
  return _parityBit;
}
uint8_t Controller::getUARTBaudRate() {
  return _UARTBaudRate;
}
uint8_t Controller::getAirDataRate() {
  return _airDataRate;
}
uint8_t Controller::getOptionFixedTransmission() {
  return _optionFixedTransmission;
}
uint8_t Controller::getOptionIODriveMode() {
  return _optionIODriveMode; }

uint8_t Controller::getOptionWakeUpTime() {
  return _optionWakeUpTime;
}
uint8_t Controller::getOptionPower() {
  return _optionPower;
}
