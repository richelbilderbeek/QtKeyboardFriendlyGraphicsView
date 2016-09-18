#include "qtkeyboardfriendlygraphicsview_test.h"
#include "qtkeyboardfriendlygraphicsview.h"

#include <QKeyEvent>
#include <QGraphicsRectItem>
//#include "container.h"
//#include "fileio.h"
//#include "counter.h"
//#include "ribi_system.h"
//#include "ribi_time.h"

void ribi::qtkeyboardfriendlygraphicsview_test
  ::space_selects_one_random_item_when_two_were_selected()
{
  QtKeyboardFriendlyGraphicsView view;
  QGraphicsRectItem * const item1{new QGraphicsRectItem};
  QGraphicsRectItem * const item2{new QGraphicsRectItem};
  item1->setToolTip("Item1");
  item2->setToolTip("Item2");
  item1->setFlag(QGraphicsItem::ItemIsFocusable);
  item2->setFlag(QGraphicsItem::ItemIsFocusable);
  item1->setFlag(QGraphicsItem::ItemIsSelectable);
  item2->setFlag(QGraphicsItem::ItemIsSelectable);
  view.scene()->addItem(item1);
  view.scene()->addItem(item2);
  view.show();
  view.setGeometry(0,0,300,300);
  item1->clearFocus();
  item2->clearFocus();
  item1->setSelected(true);
  item2->setSelected(true);
  view.show();
  QVERIFY(view.scene()->selectedItems().size() == 2);
  for (int i=0; i!=100; ++i) //Very often
  {
    view.show();
    QTest::keyClick(&view, Qt::Key_Space, Qt::NoModifier, 100);
    view.show();
    QVERIFY(view.scene()->selectedItems().size() == 1);
  }
}


void ribi::qtkeyboardfriendlygraphicsview_test
  ::space_selects_one_random_item_when_zero_were_selected()
{
  QtKeyboardFriendlyGraphicsView view;
  QGraphicsRectItem * const item1{new QGraphicsRectItem};
  QGraphicsRectItem * const item2{new QGraphicsRectItem};
  item1->setToolTip("Item1");
  item2->setToolTip("Item2");
  item1->setFlag(QGraphicsItem::ItemIsFocusable);
  item2->setFlag(QGraphicsItem::ItemIsFocusable);
  item1->setFlag(QGraphicsItem::ItemIsSelectable);
  item2->setFlag(QGraphicsItem::ItemIsSelectable);
  view.scene()->addItem(item1);
  view.scene()->addItem(item2);
  view.show();
  view.setGeometry(0,0,300,300);
  item1->setSelected(false);
  item2->setSelected(false);
  view.show();
  QVERIFY(view.scene()->selectedItems().empty());
  QTest::keyClick(&view, Qt::Key_Space, Qt::NoModifier, 100);
  view.show();
  QVERIFY(view.scene()->selectedItems().size() == 1);
}

void ribi::qtkeyboardfriendlygraphicsview_test::key_left_selects_an_item_at_the_left()
{
  QtKeyboardFriendlyGraphicsView view;
  QGraphicsRectItem * const item1{new QGraphicsRectItem};
  QGraphicsRectItem * const item2{new QGraphicsRectItem};
  item1->setToolTip("Item1");
  item2->setToolTip("Item2");
  item1->setFlag(QGraphicsItem::ItemIsFocusable);
  item2->setFlag(QGraphicsItem::ItemIsFocusable);
  item1->setFlag(QGraphicsItem::ItemIsSelectable);
  item2->setFlag(QGraphicsItem::ItemIsSelectable);
  view.scene()->addItem(item1);
  view.scene()->addItem(item2);
  view.show();
  view.setGeometry(0,0,300,300);
  //item1 unselected and unfocused at right
  item1->setSelected(false);
  item1->setPos( 100.0,0.0);
  //item1 selected and focused at left
  item2->setSelected(true);
  item2->setFocus();
  item2->setPos(-100.0,0.0);
  view.show();
  QVERIFY(view.scene()->selectedItems().size() == 1);
  QTest::keyClick(&view, Qt::Key_Left, Qt::NoModifier, 100);
  view.show();
  QVERIFY(view.scene()->selectedItems().size() == 0);
}

void ribi::qtkeyboardfriendlygraphicsview_test::bash_keys()
{
  QtKeyboardFriendlyGraphicsView view;
  QGraphicsRectItem * const item1{new QGraphicsRectItem};
  QGraphicsRectItem * const item2{new QGraphicsRectItem};
  item1->setToolTip("Item1");
  item2->setToolTip("Item2");
  item1->setFlag(QGraphicsItem::ItemIsFocusable);
  item2->setFlag(QGraphicsItem::ItemIsFocusable);
  item1->setFlag(QGraphicsItem::ItemIsSelectable);
  item2->setFlag(QGraphicsItem::ItemIsSelectable);
  view.scene()->addItem(item1);
  view.scene()->addItem(item2);
  view.show();
  view.setGeometry(0,0,300,300);
  item1->setPos(150,150);
  item2->setPos(50,50);
  view.show();
  QVERIFY(view.scene());
  QVERIFY(!view.scene()->items().empty());
  for (int i=0; i!=100; ++i)
  {
    switch (std::rand() % 9)
    {
      case 0: QTest::keyClick(&view, Qt::Key_Left, Qt::ControlModifier, 100); break;
      case 1: QTest::keyClick(&view, Qt::Key_Right, Qt::ControlModifier, 100); break;
      case 2: QTest::keyClick(&view, Qt::Key_Space, Qt::NoModifier, 100); break;
      case 3: QTest::keyClick(&view, Qt::Key_Left, Qt::ShiftModifier, 100); break;
      case 4: QTest::keyClick(&view, Qt::Key_Right, Qt::ShiftModifier, 100); break;
      case 5: QTest::keyClick(&view, Qt::Key_Left, Qt::NoModifier, 100); break;
      case 6: QTest::keyClick(&view, Qt::Key_Right, Qt::NoModifier, 100); break;
      case 7: QTest::keyClick(&view, Qt::Key_Space, Qt::NoModifier, 100); break;
      case 8: QTest::keyClick(&view, Qt::Key_X, Qt::NoModifier, 100); break;
    }
    view.show();
  }
  QVERIFY(view.scene());
}

void ribi::qtkeyboardfriendlygraphicsview_test
  ::tap_shift_should_not_remove_focus()
{
  QtKeyboardFriendlyGraphicsView view;
  QGraphicsRectItem * const item1{new QGraphicsRectItem};
  QGraphicsRectItem * const item2{new QGraphicsRectItem};
  item1->setToolTip("Item1");
  item2->setToolTip("Item2");
  item1->setFlag(QGraphicsItem::ItemIsFocusable);
  item2->setFlag(QGraphicsItem::ItemIsFocusable);
  item1->setFlag(QGraphicsItem::ItemIsSelectable);
  item2->setFlag(QGraphicsItem::ItemIsSelectable);
  view.scene()->addItem(item1);
  view.scene()->addItem(item2);
  view.show();
  view.setGeometry(0,0,300,300);
  //item1 unselected and unfocused at right
  item1->setSelected(false);
  item1->setPos( 100.0,0.0);
  //item2 selected and focused at left
  item2->setSelected(true);
  item2->setFocus();
  item2->setPos(-100.0,0.0);
  view.show();
  QVERIFY(item2->hasFocus());
  QTest::keyClick(&view, Qt::Key_Shift, Qt::NoModifier, 100);
  view.show();
  QVERIFY(item2->hasFocus());
}
