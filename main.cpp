#include <QCoreApplication>
#include "controller.h"
#include "logic.h"
#include <QApplication>

#include "mainwindow.h"
/*****************************************************************************************************************************/
/*                                                                                                                           */
/*  I've put -lcrypt flag to the project, couldnt compile without it,I have no idea what its doing (except fixing my errors) */
/*  so if dont need it or causing any errors rid of that                                                                     */
/*  I've also commented some code with "setMode" etc so sorry if forget to uncoment that                                     */
/*  And be careful with testing settng parameters!                                                                           */
/*  There arent any errors support.                                                                                          */
/*  So, try to test and HOPE IT WORKS somehow                                                                                */
/*                                                                                                                           */
/*****************************************************************************************************************************/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;

    Controller controller = Controller();

    Logic::instance()->setController(&controller);

    mainWindow.show();
    return app.exec();
}
