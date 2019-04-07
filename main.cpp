#include <QCoreApplication>
#include "controller.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  Controller controller = Controller();

  if(!controller.init()) {
      printf("failed init\n");
    }

  for (;;)
  {
    putchar (controller.getByte());
    fflush (stdout);
  }
  return a.exec();
}
