#include <iostream>
#include <QApplication>
#include <QtTest/QtTest>
#include "qtkeyboardfriendlygraphicsview_test.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv); //!OCLINT 'a' is indeed never used, yet vital
  int error = 0;
  { ribi::qtkeyboardfriendlygraphicsview_test t; error |= QTest::qExec(&t, argc, argv); }

  if (error == 0) { std::cout << "Pass\n"; }
  if (error != 0) { std::cout << "Fail\n"; }
  return error;
}
