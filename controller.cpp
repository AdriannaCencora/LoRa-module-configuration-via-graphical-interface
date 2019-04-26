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
    if(!readAllParameters()) {
        return false;
    }
    return true;
}

void Controller::close() {
    serialClose(_serialDevice);
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
    serialFlush(_serialDevice);
    //That's not final solution, just for tests :o
    write(_serialDevice, &msg, 1);
    write(_serialDevice, &msg, 1);
    write(_serialDevice, &msg, 1);

    delay(10);

    read(_serialDevice, _parameters, 6);

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
    setMode(MODE_NORMAL);


    if (_save != 0xC0) {
        qDebug() <<"failed to read. not valid first byte";
        return false;
    }

    return true;

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

bool Controller::readVersionAndModel()
{
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

void Controller::reset() {
    setMode(MODE_SLEEP);
    int msg = 0xC4;

    serialFlush(_serialDevice);

    write(_serialDevice, &msg, 1);
    write(_serialDevice, &msg, 1);
    write(_serialDevice, &msg, 1);
    setMode(MODE_NORMAL);

}
void Controller::saveParameters(uint8_t duration) {
    setMode(MODE_SLEEP);

    _save = duration;

    serialFlush(_serialDevice);
    write(_serialDevice, &_save, 1);
    write(_serialDevice, &_addressHigh, 1);
    write(_serialDevice, &_addressLow, 1);
    write(_serialDevice, &_speed, 1);
    write(_serialDevice, &_channel, 1);
    write(_serialDevice, &_options, 1);

    delay(100);
    setMode(MODE_NORMAL);
}
