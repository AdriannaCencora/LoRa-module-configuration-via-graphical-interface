#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>
#include <QDebug>


#define MODE_NORMAL 0			// can send and recieve
#define MODE_WAKEUP 1			// sends a preamble to waken receiver
#define MODE_POWER_SAVING 2		// can't transmit but receive works only in wake up mode
#define MODE_SLEEP 3			// for programming

// options to save change permanently or temp (power down and restart will restore settings to last saved options
#define PERMANENT 0xC0
#define TEMPORARY 0xC2

// parity bit options (must be the same for transmitter and reveiver)
#define PB_8N1 0b00			// default
#define PB_8O1 0b01
#define PB_8E1 0b11

//UART data rates
// (can be different for transmitter and reveiver)
#define UDR_1200 0b000		// 1200 baud
#define UDR_2400 0b001		// 2400 baud
#define UDR_4800 0b010		// 4800 baud
#define UDR_9600 0b011		// 9600 baud default
#define UDR_19200 0b100		// 19200 baud
#define UDR_38400 0b101		// 34800 baud
#define UDR_57600 0b110		// 57600 baud
#define UDR_115200 0b111	// 115200 baud


// air data rates (certian types of modules)
// (must be the same for transmitter and reveiver)
#define ADR_300 0b000		// 300 baud
#define ADR_1200 0b001		// 1200 baud
#define ADR_2400 0b010		// 2400 bauduint8_t Controller:: getMode()

#define ADR_4800 0b011		// 4800 baud
#define ADR_9600 0b100		// 9600 baud
#define ADR_19200 0b101		// 19200 baud


//various options
// (can be different for transmitter and reveiver)

//Fixed transmission enabling
#define OPT_FMDISABLE 0b0
#define OPT_FMENABLE 0b1

//IO drive mode
#define OPT_IOOPENDRAIN 0b0
#define OPT_IOPUSHPULL  0b1

//Wireless wake-up time [ms]
#define OPT_WAKEUP250  0b000
#define OPT_WAKEUP500  0b001
#define OPT_WAKEUP750  0b010
#define OPT_WAKEUP1000 0b011
#define OPT_WAKEUP1250 0b100
#define OPT_WAKEUP1500 0b101
#define OPT_WAKEUP1750 0b110
#define OPT_WAKEUP2000 0b111

//FEC switch
#define OPT_FECDISABLE  0b0
#define OPT_FECENABLE 0b1


//TODO: Transmission power still needs to be checked (doc).

class Controller
{
public:
    Controller(uint8_t M0_PIN = 21, uint8_t M1_PIN = 20, uint8_t AUX_PIN = 24);

private:
    // pin variables
    uint8_t _M0;
    uint8_t _M1;
    uint8_t _AUX;

    //file descriptor
    int _serialDevice;

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

    //consist of UART parity bit, UART baud rate and air data rate
    void buildSpeedByte();

    //consist of fixed transmission enabling, IO drive mode, FEC switch and transmission power
    void buildOptionByte();

public:
    bool init();
    void close();
    void setMode(uint8_t mode);
    uint8_t getMode();

    //read present configuration parameters
    bool readAllParameters();

    //read version, model and feature
    bool readVersionAndModel();
    void reset();
    //permanent or temporary
    void saveParameters(uint8_t duration);

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

};

#endif // CONTROLLER_H
