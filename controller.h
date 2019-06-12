#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "constants.h"
#include <stdint.h>
#include <QDebug>


class Controller
{
public:
    Controller(uint8_t M0_PIN = 21, uint8_t M1_PIN = 20, uint8_t AUX_PIN = 24);

    bool init();
    void close();
    void setMode(uint8_t mode);
    uint8_t getMode();

    bool readAllParameters();
    bool readVersionAndModel();
    bool reset();
    bool saveParameters(uint8_t saveLifeSpan);

    uint8_t getModel();
    uint8_t getVersion();
    uint8_t getFeature();

    uint8_t getSave();
    uint8_t getAddressHigh();
    uint8_t getAddressLow();
    uint8_t getSpeed();
    uint8_t getChannel();
    uint8_t getOptions();

    uint8_t getOptionFEC();
    uint8_t getParityBit();
    uint8_t getUARTBaudRate();
    uint8_t getAirDataRate();
    uint8_t getOptionFixedTransmission();
    uint8_t getOptionIODriveMode();
    uint8_t getOptionWakeUpTime();
    uint8_t getOptionPower();

    int getFileDescriptor();

    void setSave(uint8_t val);
    void setAdressHigh(uint8_t val);
    void setAdressLow(uint8_t val);
    void setSpeed(uint8_t val);
    void setChannel(uint8_t val);
    void setOptions(uint8_t val);

    void setParityBit(uint8_t parityBit);
    void setUARTBaudRate(uint8_t UARTBaudRate);
    void setAirDataRate(uint8_t airDataRate);
    void setOptionFixedTransmission(uint8_t optionFixedTransmission);
    void setOptionIODriveMode(uint8_t optionIODriveMode);
    void setOptionWakeUpTime(uint8_t optionWakeUpTime);
    void setOptionFEC(uint8_t optionFEC);
    void setOptionPower(uint8_t optionPower);

private:

    // pin variables


    uint8_t _M0;
    uint8_t _M1;
    uint8_t _AUX;
    
    int _fileDescriptorOfDevice;

    // variable for the 6 bytes that are sent to the module to program it
    // or bytes received to indicate modules programmed settings
    uint8_t _parameters[6];

    // individual variables for each of the 6 bytes
    // _parameters could be used as the main variable storage, but since some bytes
    // are a collection of several options, let's just make storage consistent
    uint8_t _save;
    uint8_t _addressHigh;
    uint8_t _addressLow;
    uint8_t _speed;
    uint8_t _channel;
    uint8_t _options;

    // individual variables for all the options
    uint8_t _parityBit;
    uint8_t _UARTBaudRate;
    uint8_t _airDataRate;
    uint8_t _optionFixedTransmission;
    uint8_t _optionIODriveMode;
    uint8_t _optionWakeUpTime;
    uint8_t _optionFEC;
    uint8_t _optionPower;

    uint8_t _model;
    uint8_t _version;
    uint8_t _features;

    void buildSpeedByte();
    void buildOptionByte();

    void setPinModes();
    bool openUARTConnection();
    void assignReadSettingsToVariables();
};

#endif // CONTROLLER_H

