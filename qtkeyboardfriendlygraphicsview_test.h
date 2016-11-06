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
  void ctrl_space_selects_one_random_item_when_zero_were_selected();
  void ctrl_space_selects_one_random_item_when_two_were_selected();
  void collect_focusable_and_selectable_items();
  void key_left_selects_an_item_at_the_left();
  void press_alt_nonsense_is_rejected();
  void press_arrow_when_no_items_is_rejected();
  void press_ctrl_space_is_accepted();
  void press_ctrl_nonsense_is_rejected();
  void press_shift_arrow_when_no_items_is_rejected();
  void press_shift_nonsense_is_rejected();
  void press_space_is_accepted();
  void press_space_when_no_items_is_rejected();
  void press_nonsense_is_rejected();
  void space_selects_one_random_item_when_zero_were_selected();
  void space_selects_one_random_item_when_two_were_selected();
  void tap_shift_should_not_remove_focus();
  void version();
};

} //~namespace ribi

#endif // QTKEYBOARDFRIENDLYGRAPHICSVIEW_TEST_H
