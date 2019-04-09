#include <QCoreApplication>
#include "controller.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  Controller controller = Controller();

  if(!controller.init()) {
      printf("failed init\n");
    }

  if (controller.readVersionAndModel()) {
      controller.displayModelVersionFeature();
    }

  if (controller.readAllParameters()) {
      controller.displayAllParameters();
    }

  return a.exec();
}
