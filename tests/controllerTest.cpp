#include "controllerTest.h"
#include <QtTest/QTest>
#include <unistd.h>
#include "../controller.h"

QTEST_MAIN(controllerTest)

controllerTest::controllerTest()
{

}

void controllerTest::testParityBitSetting_data() {
    QTest::addColumn<uint8_t>("setting");
    QTest::addColumn<uint8_t>("result");

    QTest::newRow("8N1") << (uint8_t)PB_8N1 << (uint8_t)0b00;
    QTest::newRow("8O1") << (uint8_t)PB_8O1 << (uint8_t)0b01;
    QTest::newRow("8E1") << (uint8_t)PB_8E1 << (uint8_t)0b11;
}

void controllerTest::testParityBitSetting() {
    QFETCH(uint8_t, setting);
    QFETCH(uint8_t, result);

    controller = new Controller();
    QVERIFY(controller->init());
    QVERIFY(controller->readAllParameters());
    controller->setParityBit(setting);
    controller->saveParameters(PERMANENT);
    controller->close();
    QVERIFY(controller->init());
    QVERIFY(controller->readAllParameters());
    QCOMPARE(controller->getParityBit(), result);

    controller->close();
    delete controller;
}

void controllerTest::testDataRateSetting_data() {
    QTest::addColumn<uint8_t>("setting");
    QTest::addColumn<uint8_t>("result");

    QTest::newRow("UDR1200") << (uint8_t)UDR_1200 << (uint8_t)0b000;
    QTest::newRow("UDR2400") << (uint8_t)UDR_2400 << (uint8_t)0b001;
    QTest::newRow("UDR4800") << (uint8_t)UDR_4800 << (uint8_t)0b010;
    QTest::newRow("UDR9600") << (uint8_t)UDR_9600 << (uint8_t)0b011;
    QTest::newRow("UDR19200") << (uint8_t)UDR_19200 << (uint8_t)0b100;
    QTest::newRow("UDR38400") << (uint8_t)UDR_38400 << (uint8_t)0b101;
    QTest::newRow("UDR57600") << (uint8_t)UDR_57600 << (uint8_t)0b110;
    QTest::newRow("UDR115200") << (uint8_t)UDR_115200 << (uint8_t)0b111;
}

void controllerTest::testDataRateSetting() {
    QFETCH(uint8_t, setting);
    QFETCH(uint8_t, result);

    controller = new Controller();
    QVERIFY(controller->init());
    QVERIFY(controller->readAllParameters());
    controller->setUARTBaudRate(setting);
    controller->saveParameters(PERMANENT);
    controller->close();
    QVERIFY(controller->init());
    QVERIFY(controller->readAllParameters());
    QCOMPARE(controller->getUARTBaudRate(), result);

    controller->close();
    delete controller;
}

void controllerTest::testAirDataRateSetting_data() {
    QTest::addColumn<uint8_t>("setting");
    QTest::addColumn<uint8_t>("result");

    QTest::newRow("ADR_300") << (uint8_t)ADR_300 << (uint8_t)0b000;
    QTest::newRow("ADR_1200") << (uint8_t)ADR_1200 << (uint8_t)0b001;
    QTest::newRow("ADR_2400") << (uint8_t)ADR_2400 << (uint8_t)0b010;
    QTest::newRow("ADR_4800") << (uint8_t)ADR_4800 << (uint8_t)0b011;
    QTest::newRow("ADR_9600") << (uint8_t)ADR_9600 << (uint8_t)0b100;
    QTest::newRow("ADR_19200") << (uint8_t)ADR_19200 << (uint8_t)0b101;
}

void controllerTest::testAirDataRateSetting() {
    QFETCH(uint8_t, setting);
    QFETCH(uint8_t, result);

    controller = new Controller();
    QVERIFY(controller->init());
    QVERIFY(controller->readAllParameters());
    controller->setAirDataRate(setting);
    controller->saveParameters(PERMANENT);
    controller->close();
    QVERIFY(controller->init());
    QVERIFY(controller->readAllParameters());
    QCOMPARE(controller->getAirDataRate(), result);

    controller->close();
    delete controller;
}

void controllerTest::testChannelSetting_data() {
    QTest::newRow("CHAN_0") << (uint8_t)CHAN_0 << (uint8_t)0b0;
    QTest::newRow("CHAN_1") << (uint8_t)CHAN_1 << (uint8_t)0b1;
    QTest::newRow("CHAN_2") << (uint8_t)CHAN_2 << (uint8_t)0b10;
    QTest::newRow("CHAN_3") << (uint8_t)CHAN_3 << (uint8_t)0b11;
    QTest::newRow("CHAN_4") << (uint8_t)CHAN_4 << (uint8_t)0b100;
    QTest::newRow("CHAN_5") << (uint8_t)CHAN_5 << (uint8_t)0b101;
    QTest::newRow("CHAN_6") << (uint8_t)CHAN_6 << (uint8_t)0b110;
    QTest::newRow("CHAN_7") << (uint8_t)CHAN_7 << (uint8_t)0b111;
    QTest::newRow("CHAN_8") << (uint8_t)CHAN_8 << (uint8_t)0b1000;
    QTest::newRow("CHAN_9") << (uint8_t)CHAN_9 << (uint8_t)0b1001;
    QTest::newRow("CHAN_10") << (uint8_t)CHAN_10 << (uint8_t)0b1010;
    QTest::newRow("CHAN_11") << (uint8_t)CHAN_11 << (uint8_t)0b1011;
    QTest::newRow("CHAN_12") << (uint8_t)CHAN_12 << (uint8_t)0b1100;
    QTest::newRow("CHAN_13") << (uint8_t)CHAN_13 << (uint8_t)0b1101;
    QTest::newRow("CHAN_14") << (uint8_t)CHAN_14 << (uint8_t)0b1110;
    QTest::newRow("CHAN_15") << (uint8_t)CHAN_15 << (uint8_t)0b1111;
    QTest::newRow("CHAN_16") << (uint8_t)CHAN_16 << (uint8_t)0b11111;
}

void controllerTest::testChannelSetting() {
    QFETCH(uint8_t, setting);
    QFETCH(uint8_t, result);

    controller = new Controller();
    QVERIFY(controller->init());
    QVERIFY(controller->readAllParameters());
    controller->setChannel(setting);
    controller->saveParameters(PERMANENT);
    controller->close();
    QVERIFY(controller->init());
    QVERIFY(controller->readAllParameters());
    QCOMPARE(controller->getChannel(), result);

    controller->close();
    delete controller;
}

void controllerTest::testWakeUpTimeSetting_data() {
    QTest::newRow("OPT_WAKEUP250") << (uint8_t)OPT_WAKEUP250 << (uint8_t)0b000;
    QTest::newRow("OPT_WAKEUP500") << (uint8_t)OPT_WAKEUP500 << (uint8_t)0b001;
    QTest::newRow("OPT_WAKEUP750") << (uint8_t)OPT_WAKEUP750 << (uint8_t)0b010;
    QTest::newRow("OPT_WAKEUP1000") << (uint8_t)OPT_WAKEUP1000 << (uint8_t)0b011;
    QTest::newRow("OPT_WAKEUP1250") << (uint8_t)OPT_WAKEUP1250 << (uint8_t)0b100;
    QTest::newRow("OPT_WAKEUP1500") << (uint8_t)OPT_WAKEUP1500 << (uint8_t)0b101;
    QTest::newRow("OPT_WAKEUP1750") << (uint8_t)OPT_WAKEUP1750 << (uint8_t)0b110;
    QTest::newRow("OPT_WAKEUP2000") << (uint8_t)OPT_WAKEUP2000 << (uint8_t)0b111;
}

void controllerTest::testWakeUpTimeSetting() {
    QFETCH(uint8_t, setting);
    QFETCH(uint8_t, result);

    controller = new Controller();
    QVERIFY(controller->init());
    QVERIFY(controller->readAllParameters());
    controller->setOptionWakeUpTime(setting);
    controller->saveParameters(PERMANENT);
    controller->close();
    QVERIFY(controller->init());
    QVERIFY(controller->readAllParameters());
    QCOMPARE(controller->getOptionWakeUpTime(), result);

    controller->close();
    delete controller;
}

void controllerTest::testTransmissionPowerSetting_data() {
    QTest::newRow("OPT_TP30") << (uint8_t)OPT_TP30 << (uint8_t)0b00;
    QTest::newRow("OPT_TP27") << (uint8_t)OPT_TP27 << (uint8_t)0b01;
    QTest::newRow("OPT_TP24") << (uint8_t)OPT_TP24 << (uint8_t)0b10;
    QTest::newRow("OPT_TP21") << (uint8_t)OPT_TP21 << (uint8_t)0b11;
}

void controllerTest::testTransmissionPowerSetting() {
    QFETCH(uint8_t, setting);
    QFETCH(uint8_t, result);

    controller = new Controller();
    QVERIFY(controller->init());
    QVERIFY(controller->readAllParameters());
    controller->setOptionPower(setting);
    controller->saveParameters(PERMANENT);
    controller->close();
    QVERIFY(controller->init());
    QVERIFY(controller->readAllParameters());
    QCOMPARE(controller->getOptionPower(), result);

    controller->close();
    delete controller;
}
