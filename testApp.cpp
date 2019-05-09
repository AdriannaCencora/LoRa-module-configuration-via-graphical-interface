#include <gtest/gtest.h>
#include "controller.h"

struct testApp : public testing::Test {

    Controller uut;

};

TEST_F(testApp, IfSetModeOnWakeUpExpects1) {
    uut.setMode(MODE_WAKEUP);

    EXPECT_EQ(1, uut.getMode());
}

TEST_F(testApp, IfSetParityBitOnPB_8N1Expects0b00) {
    uut.setParityBit(PB_8N1);

    EXPECT_EQ(0b00, uut.getParityBit());
}

TEST_F(testApp, IfSetParityBitOnPB_8O1Expects0b01) {
    uut.setParityBit(PB_8O1);

    EXPECT_EQ(0b01, uut.getParityBit());
}

TEST_F(testApp, IfSetParityBitOnPB_8E1Expects0b11) {
    uut.setParityBit(PB_8E1);

    EXPECT_EQ(0b11, uut.getParityBit());
}

TEST_F(testApp, IfSetIndividualBitsExpectSpeedByteBuildsProperly) {
    uut.setParityBit(PB_8N1);
    uut.setUARTBaudRate(UDR_9600);
    uut.setAirDataRate(ADR_2400);

    EXPECT_EQ(0b00, uut.getParityBit());
    EXPECT_EQ(0b011, uut.getUARTBaudRate());
    EXPECT_EQ(0b010, uut.getAirDataRate());
    EXPECT_EQ(0x1A, uut.getSpeed());
}

TEST_F(testApp, IfSetIndividualBitsExpectOptionByteBuildsProperly) {
    uut.setOptionFixedTransmission(OPT_FMENABLE);
    uut.setOptionIODriveMode(OPT_IOPUSHPULL);
    uut.setOptionWakeUpTime(OPT_WAKEUP1500);
    uut.setOptionFEC(OPT_FECENABLE);
    uut.setOptionPower(OPT_TP21);

    EXPECT_EQ(0b1, uut.getOptionFixedTransmission());
    EXPECT_EQ(0b1, uut.getOptionIODriveMode());
    EXPECT_EQ(0b101, uut.getOptionWakeUpTime());
    EXPECT_EQ(0b1, uut.getOptionFEC());
    EXPECT_EQ(0b11, uut.getOptionPower());

    EXPECT_EQ(0xEF, uut.getOptions());
}

TEST_F(testApp, IfSetChannelToCHAN_16Expects0x1F) {
    uut.setChannel(CHAN_16);

    EXPECT_EQ(0x1F, uut.getChannel());
}
