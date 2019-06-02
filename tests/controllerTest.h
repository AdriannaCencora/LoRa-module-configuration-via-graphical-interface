#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H


#include <QObject>
#include "../controller.h"
#include "../constants.h"

class controllerTest: public QObject
{
    Q_OBJECT
    Controller *controller;
public:
    controllerTest();
private slots:
    void testParityBitSetting_data();
    void testParityBitSetting();
    void testDataRateSetting_data();
    void testDataRateSetting();
    void testAirDataRateSetting_data();
    void testAirDataRateSetting();
    void testChannelSetting_data();
    void testChannelSetting();
    void testWakeUpTimeSetting_data();
    void testWakeUpTimeSetting();
    void testTransmissionPowerSetting_data();
    void testTransmissionPowerSetting();
};

#endif // TESTCONTROLLER_H
