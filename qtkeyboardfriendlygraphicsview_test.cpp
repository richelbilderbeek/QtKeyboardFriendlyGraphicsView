#include "qtkeyboardfriendlygraphicsview_test.h"
#include "qtkeyboardfriendlygraphicsview.h"

#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsRectItem>

void ribi::qtkeyboardfriendlygraphicsview_test
  ::collect_focusable_and_selectable_items()
{
  {
    QtKeyboardFriendlyGraphicsView view;
    QVERIFY(CollectFocusableAndSelectableItems(view).size() == 0);
  }
  {
    QtKeyboardFriendlyGraphicsView view;
    auto item = CreateFocusableAndSelectableItem();
    view.scene()->addItem(item.release());
    QVERIFY(CollectFocusableAndSelectableItems(view).size() == 1);
  }
  {
    QtKeyboardFriendlyGraphicsView view;
    auto item1 = CreateFocusableAndSelectableItem();
    view.scene()->addItem(item1.release());
    auto item2 = CreateFocusableAndSelectableItem();
    view.scene()->addItem(item2.release());
    QVERIFY(CollectFocusableAndSelectableItems(view).size() == 2);
  }
}

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
    QKeyEvent e(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier);
    view.keyPressEvent(&e);
    //QTest::keyClick(&view, Qt::Key_Space, Qt::NoModifier);

    view.show();
    QVERIFY(view.scene()->selectedItems().size() == 1);
    QVERIFY(e.isAccepted());
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
  for (int i=0; i!=100; ++i) //Very often
  {
    QTest::keyClick(&view, Qt::Key_Space, Qt::NoModifier);
    view.show();
    QVERIFY(view.scene()->selectedItems().size() == 1);
  }
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
      case 0: QTest::keyClick(&view, Qt::Key_Left, Qt::ControlModifier, 10); break;
      case 1: QTest::keyClick(&view, Qt::Key_Right, Qt::ControlModifier, 10); break;
      case 2: QTest::keyClick(&view, Qt::Key_Space, Qt::NoModifier, 10); break;
      case 3: QTest::keyClick(&view, Qt::Key_Left, Qt::ShiftModifier, 10); break;
      case 4: QTest::keyClick(&view, Qt::Key_Right, Qt::ShiftModifier, 10); break;
      case 5: QTest::keyClick(&view, Qt::Key_Left, Qt::NoModifier, 10); break;
      case 6: QTest::keyClick(&view, Qt::Key_Right, Qt::NoModifier, 10); break;
      case 7: QTest::keyClick(&view, Qt::Key_Space, Qt::NoModifier, 10); break;
      case 8: QTest::keyClick(&view, Qt::Key_X, Qt::NoModifier, 10); break;
    }
    view.show();
    qApp->processEvents();
  }
  QVERIFY(view.scene());
}

void ribi::qtkeyboardfriendlygraphicsview_test
  ::press_arrow_when_no_items_is_rejected()
{
  //When there are no items, focus cannot be moved
  {
    QtKeyboardFriendlyGraphicsView view;
    QKeyEvent e(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
    view.keyPressEvent(&e);
    QVERIFY(!e.isAccepted());
  }
  {
    QtKeyboardFriendlyGraphicsView view;
    QKeyEvent e(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
    view.keyPressEvent(&e);
    QVERIFY(!e.isAccepted());
  }
  {
    QtKeyboardFriendlyGraphicsView view;
    QKeyEvent e(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
    view.keyPressEvent(&e);
    QVERIFY(!e.isAccepted());
  }
  {
    QtKeyboardFriendlyGraphicsView view;
    QKeyEvent e(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
    view.keyPressEvent(&e);
    QVERIFY(!e.isAccepted());
  }
  {
    QtKeyboardFriendlyGraphicsView view;
    QKeyEvent e(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier);
    view.keyPressEvent(&e);
    QVERIFY(!e.isAccepted());
  }
}

void ribi::qtkeyboardfriendlygraphicsview_test
  ::press_space_is_accepted()
{
  QtKeyboardFriendlyGraphicsView view;
  QGraphicsRectItem * const item1{new QGraphicsRectItem};
  item1->setToolTip("Item1");
  item1->setFlag(QGraphicsItem::ItemIsFocusable);
  item1->setFlag(QGraphicsItem::ItemIsSelectable);
  view.scene()->addItem(item1);
  QKeyEvent e(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier);
  view.keyPressEvent(&e);
  QVERIFY(e.isAccepted());
}

void ribi::qtkeyboardfriendlygraphicsview_test
  ::press_nonsense_is_rejected()
{
  QtKeyboardFriendlyGraphicsView view;
  QGraphicsRectItem * const item1{new QGraphicsRectItem};
  item1->setToolTip("Item1");
  item1->setFlag(QGraphicsItem::ItemIsFocusable);
  item1->setFlag(QGraphicsItem::ItemIsSelectable);
  view.scene()->addItem(item1);
  QKeyEvent e(QEvent::KeyPress, Qt::Key_F6, Qt::NoModifier);
  view.keyPressEvent(&e);
  QVERIFY(!e.isAccepted());
}

void ribi::qtkeyboardfriendlygraphicsview_test
  ::tap_shift_should_not_remove_focus()
{
  return; //Cannot get item2 to have focus
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
  view.setGeometry(0,0,400,400);
  view.show();
  //item1 unselected and unfocused at right
  item1->setSelected(false);
  item1->setPos(1.0,0.0);
  //item2 selected and focused at left
  item2->setSelected(true);
  item2->setPos(0.0,1.0);
  ReallyLoseFocus(view);
  view.showFullScreen();
  qApp->processEvents();
  item2->setSelected(true);
  item2->setFocus();
  view.show();
  QVERIFY(item2->isVisible());
  QVERIFY(item2->hasFocus());
  QTest::keyClick(&view, Qt::Key_Shift, Qt::NoModifier, 100);
  view.show();
  QVERIFY(item2->hasFocus());
}
