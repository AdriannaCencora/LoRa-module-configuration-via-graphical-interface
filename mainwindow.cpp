#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openBtn_clicked()
{
    //TODO open port
}

void MainWindow::on_closeBtn_clicked()
{
    //TODO close port
}

void MainWindow::on_getParamBtn_clicked()
{
    //TODO get parameters
    //Jakby byla przydatna wrzucam tez konwersje z stringa do Qstringa

    QString str1 = "Label1: " + QString::fromStdString("TODO") + "\n";
    QString str2 = "Label2: " + QString::fromStdString("TODO") + "\n";

    ui->paramBrowser->setText(str1+str2);
}

void MainWindow::on_setParamBtn_clicked()
{
    //TODO set parameters
    //Dane tekstowe z combo boxow:
    ui->parityBox->currentText();   //8N1, 8E1, 8O1
    ui->baudBox->currentText();     //1200, 2400...
    ui->airBox->currentText();      //0,3k 1,2k ...
    ui->fecBox->currentText();      //Enable, Disable
    ui->fixedBox->currentText();    //Enable, Disable
    ui->worBox->currentText();      //250, 500 ...
    //Mozna tez ui->#BOX#->currentIndex;
}

void MainWindow::on_resetBtn_clicked()
{
    //TODO reset
}

void MainWindow::on_exitBtn_clicked()
{
    //TODO exit
}

void MainWindow::on_handlerTestBtn_clicked()
{
    //Testy

    QString str1 = "Parity: " + ui->parityBox->currentText() + " \n";
    QString str2 = "Baud: " + ui->baudBox->currentText() + "\n";
    QString str3 = "Air: " + ui->airBox->currentText() + " \n";
    QString str4 = "Fec: " + ui->fecBox->currentText() + " \n";
    QString str5 = "Fixed: " + ui->fixedBox->currentText() + " \n";
    QString str6 = "WOR: " + ui->worBox->currentText() + " \n";

    ui->paramBrowser->setText(str1+str2+str3+str4+str5+str6);
}
