#ifndef QTKEYBOARDFRIENDLYGRAPHICSVIEW_TEST_H
#define QTKEYBOARDFRIENDLYGRAPHICSVIEW_TEST_H

#include <QtTest/QtTest>
#include "qtkeyboardfriendlygraphicsview.h"

namespace ribi {

class qtkeyboardfriendlygraphicsview_test : public QObject
{
    Q_OBJECT

private slots:
  void bash_keys();
  void key_left_selects_an_item_at_the_left();
  void space_selects_one_random_item_when_zero_were_selected();
  void space_selects_one_random_item_when_two_were_selected();
  void tap_shift_should_not_remove_focus();
};

} //~namespace ribi

#endif // QTKEYBOARDFRIENDLYGRAPHICSVIEW_TEST_H
