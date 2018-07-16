



#include <QApplication>
#include <QDesktopWidget>
#include "qtkeyboardfriendlygraphicsviewdemomenudialog.h"


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog d;
  d.show();
  return a.exec();
}
