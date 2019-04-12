#include "mainwindow.h"
#include "controller.h"
#include "logic.h"
#include <QApplication>


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
    QApplication a(argc, argv);
    MainWindow w;


    Controller controller = Controller();

    Logic::instance()->setController(&controller);  // <----now we can get access to controller in other class with  Logic::instance()->getCotroller()

    /*if(!controller.init()) {
        printf("failed init\n");         <----  Moved to openBtn handler in mainwindow class
    }*/

  /*  if(controller.readVersionAndModel()) {
        controller.displayModelVersionFeature();
    }*/

    /*if(controller.readAllParameters()) {
        controller.displayAllParameters();
    }*/
    w.show();
    return a.exec();
}
