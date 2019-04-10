#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openBtn_clicked();

    void on_closeBtn_clicked();

    void on_getParamBtn_clicked();

    void on_setParamBtn_clicked();

    void on_resetBtn_clicked();

    void on_exitBtn_clicked();

    void on_handlerTestBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
