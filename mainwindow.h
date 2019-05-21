#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Console;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void keyPressEvent(QKeyEvent *e) override;

    void on_openBtn_clicked();
    void on_closeBtn_clicked();
    void on_getParamBtn_clicked();
    void on_setParamBtn_clicked();
    void on_resetBtn_clicked();
    void on_exitBtn_clicked();
    void setParityBit();
    void setAirDataRate();
    void setBaudRate();
    void setFEC();
    void setFixMode();
    void setWORTiming();
    void setMode();
    void setIO();
    void setSave();
    void setPower();
    void setChannel();
    void on_inputLine_textEdited(const QString &arg1);

private:

    Ui::MainWindow *ui;
    Console *console;
    Console *console_input;

};

#endif // MAINWINDOW_H
