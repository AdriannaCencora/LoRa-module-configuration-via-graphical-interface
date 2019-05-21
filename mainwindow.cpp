#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logic.h"
#include <QString>
#include <QMessageBox>
#include "console.h"
#include "logic_console.h"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  console(new Console),
  console_input(new Console)

{
  ui->setupUi(this);
  ui->conOutLayout->addWidget(console);
  ui->inputLayout->addWidget(console_input);

  console->setFixedHeight(500);
  console_input->setInputOption(true);
  console_input->setLocalEchoEnabled(true);


  LogicConsole::instance()->setOutput(console);
  LogicConsole::instance()->setInput(console_input);
  LogicConsole::instance()->getInputCon()->putData(">>");
 }

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_openBtn_clicked()
{
  if(!Logic::instance()->getController()->init())
    QMessageBox::critical(this,tr("Error"),tr("Open port Failed"));
  else {
      QString str = "Properly opened.";
      ui->paramBrowser->setText(str);
  }
}

void MainWindow::on_closeBtn_clicked()
{
  Logic::instance()->getController()->close();
}

void MainWindow::on_getParamBtn_clicked()
{
    Logic::instance()->getController()->readAllParameters();

  QString str = "Model: "+ QString::number(Logic::instance()->getController()->getModel(),16)+"\n"+
      "Version: " + QString::number(Logic::instance()->getController()->getVersion(),16)+ "\n"+
      "Features: " + QString::number(Logic::instance()->getController()->getFeature(),16)+"\n"+
      "\n"+
      "Mode: "+ QString::number(Logic::instance()->getController()->getMode(),16)+"\n"+
      "Save: " + QString::number(Logic::instance()->getController()->getSave(),16)+"\n"+
      "AddressHigh: " + QString::number(Logic::instance()->getController()->getAddressHigh(),16)+"\n"+
      "AddressLow: " + QString::number(Logic::instance()->getController()->getAddressLow(),16)+"\n"+
      "Speed: " + QString::number(Logic::instance()->getController()->getSpeed(),16)+"\n"+
      "Channel: " + QString::number(Logic::instance()->getController()->getChannel(),16)+"\n"+
      "Options: " + QString::number(Logic::instance()->getController()->getOptions(),16)+"\n"+
      "\n"+
      "ParityBit: " + QString::number(Logic::instance()->getController()->getParityBit(),2)+"\n"+
      "UartBaudRate: " + QString::number(Logic::instance()->getController()->getUARTBaudRate(),2)+"\n"+
      "AirDataRate: " + QString::number(Logic::instance()->getController()->getAirDataRate(),2)+"\n"+
      "FixedTranmision: " + QString::number(Logic::instance()->getController()->getOptionFixedTransmission(),2)+"\n"+
      "IODriveMode: " + QString::number(Logic::instance()->getController()->getOptionIODriveMode(),2)+"\n"+
      "WakeUpTime: " + QString::number(Logic::instance()->getController()->getOptionWakeUpTime(),2)+"\n"+
      "FEC: " + QString::number(Logic::instance()->getController()->getOptionFEC(),2)+"\n"+
      "Power: " + QString::number(Logic::instance()->getController()->getOptionPower(),2)+"\n";

  ui->paramBrowser->setText(str);

}

void MainWindow::on_setParamBtn_clicked()
{
  setMode();
  setChannel();
  setParityBit();
  setBaudRate();
  setAirDataRate();
  setFixMode();
  setIO();
  setWORTiming();
  setFEC();
  setPower();
  setChannel();
  setSave();


}

void MainWindow::on_resetBtn_clicked()
{
  Logic::instance()->getController()->reset();
}

void MainWindow::on_exitBtn_clicked()
{
  this->close();
}

void MainWindow::setParityBit()
{
  int index = ui->parityBox->currentIndex();
  switch(index)
    {
    case 0: Logic::instance()->getController()->setParityBit(PB_8N1);
      break;
    case 1: Logic::instance()->getController()->setParityBit(PB_8O1);
      break;
    case 2: Logic::instance()->getController()->setParityBit(PB_8E1);
      break;
    }
}

void MainWindow::setAirDataRate()
{
  int index = ui->airBox->currentIndex();
  switch(index)
    {
    case 0: Logic::instance()->getController()->setAirDataRate(ADR_300);
      break;
    case 1: Logic::instance()->getController()->setAirDataRate(ADR_1200);
      break;
    case 2: Logic::instance()->getController()->setAirDataRate(ADR_2400);
      break;
    case 3: Logic::instance()->getController()->setAirDataRate(ADR_4800);
      break;
    case 4: Logic::instance()->getController()->setAirDataRate(ADR_9600);
      break;
    case 5: Logic::instance()->getController()->setAirDataRate(ADR_19200);
      break;
    }
}

void MainWindow::setBaudRate()
{
  int index = ui->baudBox->currentIndex();
  switch(index)
    {
    case 0: Logic::instance()->getController()->setUARTBaudRate(UDR_1200);
      break;
    case 1: Logic::instance()->getController()->setUARTBaudRate(UDR_2400);
      break;
    case 2: Logic::instance()->getController()->setUARTBaudRate(UDR_4800);
      break;
    case 3: Logic::instance()->getController()->setUARTBaudRate(UDR_9600);
      break;
    case 4: Logic::instance()->getController()->setUARTBaudRate(UDR_19200);
      break;
    case 5: Logic::instance()->getController()->setUARTBaudRate(UDR_38400);
      break;
    case 6: Logic::instance()->getController()->setUARTBaudRate(UDR_57600);
      break;
    case 7: Logic::instance()->getController()->setUARTBaudRate(UDR_115200);
      break;
    }
}

void MainWindow::setFixMode()
{
  int index = ui->fixedBox->currentIndex();
  switch(index)
    {
    case 0: Logic::instance()->getController()->setOptionFixedTransmission(OPT_FMDISABLE);
      break;
    case 1: Logic::instance()->getController()->setOptionFixedTransmission(OPT_FMENABLE);
      break;
    }
}

void MainWindow::setFEC()
{
  int index = ui->fecBox->currentIndex();
  switch(index)
    {
    case 0: Logic::instance()->getController()->setOptionFEC(OPT_FECDISABLE);
      break;
    case 1: Logic::instance()->getController()->setOptionFEC(OPT_FECENABLE);
      break;

    }
}

void MainWindow::setWORTiming()
{
  int index = ui->worBox->currentIndex();
  switch(index)
    {
    case 0: Logic::instance()->getController()->setOptionWakeUpTime(OPT_WAKEUP250);
      break;
    case 1: Logic::instance()->getController()->setOptionWakeUpTime(OPT_WAKEUP500);
      break;
    case 2: Logic::instance()->getController()->setOptionWakeUpTime(OPT_WAKEUP750);
      break;
    case 3: Logic::instance()->getController()->setOptionWakeUpTime(OPT_WAKEUP1000);
      break;
    case 4: Logic::instance()->getController()->setOptionWakeUpTime(OPT_WAKEUP1250);
      break;
    case 5: Logic::instance()->getController()->setOptionWakeUpTime(OPT_WAKEUP1500);
      break;
    case 6: Logic::instance()->getController()->setOptionWakeUpTime(OPT_WAKEUP1750);
      break;
    case 7: Logic::instance()->getController()->setOptionWakeUpTime(OPT_WAKEUP2000);
      break;
    }
}

void MainWindow::setIO()
{
  int index = ui->ioBox->currentIndex();
  switch(index)
    {
    case 0: Logic::instance()->getController()->setOptionIODriveMode(OPT_IOOPENDRAIN);
      break;
    case 1: Logic::instance()->getController()->setOptionIODriveMode(OPT_IOPUSHPULL);
      break;

    }
}

void MainWindow::setMode()
{
  int index = ui->modeBox->currentIndex();
  switch(index)
    {
    case 0: Logic::instance()->getController()->setMode(MODE_NORMAL);
      break;
    case 1: Logic::instance()->getController()->setMode(MODE_WAKEUP);
      break;
    case 2: Logic::instance()->getController()->setMode(MODE_POWER_SAVING);
      break;
    case 3: Logic::instance()->getController()->setMode(MODE_SLEEP);
      break;
    }
}

void MainWindow::setSave()
{
  int index = ui->saveBox->currentIndex();
  switch(index)
    {
    case 0: Logic::instance()->getController()->setSave(PERMANENT);
        Logic::instance()->getController()->saveParameters(PERMANENT);

        break;
    case 1: Logic::instance()->getController()->setSave(TEMPORARY);
          Logic::instance()->getController()->saveParameters(TEMPORARY);

          break;

      }
    }

  void MainWindow::setPower()
  {
    int index = ui->powerBox->currentIndex();
    switch(index)
      {
      case 0: Logic::instance()->getController()->setOptionPower(OPT_TP30);
        break;
      case 1: Logic::instance()->getController()->setOptionPower(OPT_TP27);
        break;
      case 2: Logic::instance()->getController()->setOptionPower(OPT_TP24);
        break;
      case 3: Logic::instance()->getController()->setOptionPower(OPT_TP21);
        break;
      }
  }

  void MainWindow::setChannel()
  {

    int index = ui->channelBox->currentIndex();
    switch(index)
      {
      case 0: Logic::instance()->getController()->setChannel(CHAN_0);
        break;
      case 1: Logic::instance()->getController()->setChannel(CHAN_1);
        break;
      case 2: Logic::instance()->getController()->setChannel(CHAN_2);
        break;
      case 3: Logic::instance()->getController()->setChannel(CHAN_3);
        break;
      case 4: Logic::instance()->getController()->setChannel(CHAN_4);
        break;
      case 5: Logic::instance()->getController()->setChannel(CHAN_5);
        break;
      case 6: Logic::instance()->getController()->setChannel(CHAN_6);
        break;
      case 7: Logic::instance()->getController()->setChannel(CHAN_7);
        break;
      case 8: Logic::instance()->getController()->setChannel(CHAN_8);
        break;
      case 9: Logic::instance()->getController()->setChannel(CHAN_9);
        break;
      case 10: Logic::instance()->getController()->setChannel(CHAN_10);
        break;
      case 11: Logic::instance()->getController()->setChannel(CHAN_11);
        break;
      case 12: Logic::instance()->getController()->setChannel(CHAN_12);
        break;
      case 13: Logic::instance()->getController()->setChannel(CHAN_13);
        break;
      case 14: Logic::instance()->getController()->setChannel(CHAN_14);
        break;
      case 15: Logic::instance()->getController()->setChannel(CHAN_15);
        break;
      case 16: Logic::instance()->getController()->setChannel(CHAN_16);
        break;
      }
  }

void MainWindow::on_inputLine_textEdited(const QString &arg1)
{

}

void MainWindow::keyPressEvent(QKeyEvent *e){

}
