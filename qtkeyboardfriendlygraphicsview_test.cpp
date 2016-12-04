#include "qtkeyboardfriendlygraphicsview_test.h"
#include "qtkeyboardfriendlygraphicsview.h"

#include <cassert>
#include <memory>
#include <QApplication>
#include <QDebug>
#include <QGridLayout>
#include <QDialog>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QGraphicsView>

std::unique_ptr<ribi::QtKeyboardFriendlyGraphicsView> create_test_view(
  const int n = 3, QWidget * const parent = nullptr)
{
  std::unique_ptr<ribi::QtKeyboardFriendlyGraphicsView> view{
    std::make_unique<ribi::QtKeyboardFriendlyGraphicsView>(parent)
  };
  for (int i=0; i!=n; ++i)
  {
    QGraphicsRectItem * const item{new QGraphicsRectItem};
    item->setToolTip(QString("Item #") + QString::number(i));
    item->setFlag(QGraphicsItem::ItemIsFocusable);
    item->setFlag(QGraphicsItem::ItemIsSelectable);
    item->setSelected(false);
    view->scene()->addItem(item);

  }
  view->setGeometry(0,0,300,300);
  return view;
}

std::unique_ptr<QDialog> create_test_dialog(
  const int n = 3, QWidget * const parent = nullptr)
{
  std::unique_ptr<QDialog> dialog{
    std::make_unique<QDialog>(parent)
  };
  assert(!dialog->layout());
  dialog->setLayout(new QGridLayout);
  assert(dialog->layout());
  auto view = create_test_view(n, dialog.get());
  const auto raw_view_ptr = view.release();
  dialog->layout()->addWidget(raw_view_ptr);
  assert(dialog->layout()->itemAt(0)->widget() == raw_view_ptr);
  return dialog;
}


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
  ::ctrl_space_selects_one_random_item_when_two_were_selected()
{
  const auto view = create_test_view(2);
  for (const auto item: view->items())
  {
    item->clearFocus();
    item->setSelected(true);
  }
  view->show();
  QVERIFY(view->scene()->selectedItems().size() == 2);
  for (int i=0; i!=100; ++i) //Very often
  {
    QKeyEvent e(QEvent::KeyPress, Qt::Key_Space, Qt::ControlModifier);
    view->keyPressEvent(&e);
    //QTest::keyClick(&view, Qt::Key_Space, Qt::NoModifier);

    view->show();
    QVERIFY(view->scene()->selectedItems().size() == 1);
    QVERIFY(e.isAccepted());
  }
}


void ribi::qtkeyboardfriendlygraphicsview_test
  ::ctrl_space_selects_one_random_item_when_zero_were_selected()
{
  auto view = create_test_view(2);
  view->show();
  QVERIFY(view->scene()->selectedItems().empty());
  for (int i=0; i!=100; ++i) //Very often
  {
    QTest::keyClick(view.get(), Qt::Key_Space, Qt::ControlModifier);
    view->show();
    QVERIFY(view->scene()->selectedItems().size() == 1);
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
  ::press_alt_nonsense_is_rejected()
{
  QtKeyboardFriendlyGraphicsView view;
  QGraphicsRectItem * const item1{new QGraphicsRectItem};
  item1->setToolTip("Item1");
  item1->setFlag(QGraphicsItem::ItemIsFocusable);
  item1->setFlag(QGraphicsItem::ItemIsSelectable);
  view.scene()->addItem(item1);
  QKeyEvent e(QEvent::KeyPress, Qt::Key_F6, Qt::AltModifier);
  view.keyPressEvent(&e);
  QVERIFY(!e.isAccepted());
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
  ::press_ctrl_nonsense_is_rejected()
{
  QtKeyboardFriendlyGraphicsView view;
  QGraphicsRectItem * const item1{new QGraphicsRectItem};
  item1->setToolTip("Item1");
  item1->setFlag(QGraphicsItem::ItemIsFocusable);
  item1->setFlag(QGraphicsItem::ItemIsSelectable);
  view.scene()->addItem(item1);
  QKeyEvent e(QEvent::KeyPress, Qt::Key_F6, Qt::ControlModifier);
  view.keyPressEvent(&e);
  QVERIFY(!e.isAccepted());
}

void ribi::qtkeyboardfriendlygraphicsview_test
  ::press_ctrl_space_is_accepted()
{
  QtKeyboardFriendlyGraphicsView view;
  QGraphicsRectItem * const item1{new QGraphicsRectItem};
  item1->setToolTip("Item1");
  item1->setFlag(QGraphicsItem::ItemIsFocusable);
  item1->setFlag(QGraphicsItem::ItemIsSelectable);
  view.scene()->addItem(item1);
  QKeyEvent e(QEvent::KeyPress, Qt::Key_Space, Qt::ControlModifier);
  view.keyPressEvent(&e);
  QVERIFY(e.isAccepted());
}

void ribi::qtkeyboardfriendlygraphicsview_test
  ::press_shift_arrow_when_no_items_is_rejected()
{
  //When there are no items, focus cannot be moved
  {
    QtKeyboardFriendlyGraphicsView view;
    QKeyEvent e(QEvent::KeyPress, Qt::Key_Up, Qt::ShiftModifier);
    view.keyPressEvent(&e);
    QVERIFY(!e.isAccepted());
  }
  {
    QtKeyboardFriendlyGraphicsView view;
    QKeyEvent e(QEvent::KeyPress, Qt::Key_Right, Qt::ShiftModifier);
    view.keyPressEvent(&e);
    QVERIFY(!e.isAccepted());
  }
  {
    QtKeyboardFriendlyGraphicsView view;
    QKeyEvent e(QEvent::KeyPress, Qt::Key_Down, Qt::ShiftModifier);
    view.keyPressEvent(&e);
    QVERIFY(!e.isAccepted());
  }
  {
    QtKeyboardFriendlyGraphicsView view;
    QKeyEvent e(QEvent::KeyPress, Qt::Key_Left, Qt::ShiftModifier);
    view.keyPressEvent(&e);
    QVERIFY(!e.isAccepted());
  }
  {
    QtKeyboardFriendlyGraphicsView view;
    QKeyEvent e(QEvent::KeyPress, Qt::Key_Space, Qt::ShiftModifier);
    view.keyPressEvent(&e);
    QVERIFY(!e.isAccepted());
  }
}

void ribi::qtkeyboardfriendlygraphicsview_test
  ::press_shift_nonsense_is_rejected()
{
  QtKeyboardFriendlyGraphicsView view;
  QGraphicsRectItem * const item1{new QGraphicsRectItem};
  item1->setToolTip("Item1");
  item1->setFlag(QGraphicsItem::ItemIsFocusable);
  item1->setFlag(QGraphicsItem::ItemIsSelectable);
  view.scene()->addItem(item1);
  QKeyEvent e(QEvent::KeyPress, Qt::Key_F6, Qt::ShiftModifier);
  view.keyPressEvent(&e);
  QVERIFY(!e.isAccepted());
}

void ribi::qtkeyboardfriendlygraphicsview_test
  ::press_shift_space_add_selects_an_item_when_zero_were_selected()
{
  auto view = create_test_view();
  view->show();
  QVERIFY(view->scene()->selectedItems().empty());
  QTest::keyClick(view.get(), Qt::Key_Space, Qt::ShiftModifier);
  view->show();
  QVERIFY(view->scene()->selectedItems().size() == 1);
}

void ribi::qtkeyboardfriendlygraphicsview_test
  ::press_shift_space_add_selects_an_item_when_one_were_selected()
{
  auto view = create_test_view();
  view->show();
  QVERIFY(view->scene()->selectedItems().empty());
  for (int i=0; i!=100; ++i) //Very often
  {
    QTest::keyClick(view.get(), Qt::Key_Space, Qt::NoModifier);
    view->show();
    QVERIFY(view->scene()->selectedItems().size() == 1);
    QTest::keyClick(view.get(), Qt::Key_Space, Qt::ShiftModifier);
    QVERIFY(view->scene()->selectedItems().size() == 2);
  }
}

void ribi::qtkeyboardfriendlygraphicsview_test
  ::press_shift_space_add_selects_an_item_when_two_were_selected()
{
  auto view = create_test_view();
  view->show();
  QVERIFY(view->scene()->selectedItems().empty());
  for (int i=0; i!=100; ++i) //Very often
  {
    QTest::keyClick(view.get(), Qt::Key_Space, Qt::NoModifier);
    view->show();
    QTest::keyClick(view.get(), Qt::Key_Space, Qt::ShiftModifier);
    QTest::keyClick(view.get(), Qt::Key_Space, Qt::ShiftModifier);
    QVERIFY(view->scene()->selectedItems().size() == 3);
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
  ::press_space_when_no_items_is_rejected()
{
  QtKeyboardFriendlyGraphicsView view;
  QKeyEvent e(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier);
  view.keyPressEvent(&e);
  QVERIFY(!e.isAccepted());
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
  view.show();
  QKeyEvent e(QEvent::KeyPress, Qt::Key_F6, Qt::NoModifier);
  view.keyPressEvent(&e);
  QVERIFY(!e.isAccepted());
}

void ribi::qtkeyboardfriendlygraphicsview_test
  ::space_selects_one_random_item_when_two_were_selected()
{
  const auto view = create_test_view(2);
  for (const auto item: view->items())
  {
    item->clearFocus();
    item->setSelected(true);
  }
  view->show();
  QVERIFY(view->scene()->selectedItems().size() == 2);
  for (int i=0; i!=100; ++i) //Very often
  {
    QKeyEvent e(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier);
    view->keyPressEvent(&e);
    //QTest::keyClick(&view, Qt::Key_Space, Qt::NoModifier);

    view->show();
    QVERIFY(view->scene()->selectedItems().size() == 1);
    QVERIFY(e.isAccepted());
  }
}


void ribi::qtkeyboardfriendlygraphicsview_test
  ::space_selects_one_random_item_when_zero_were_selected()
{
  auto view = create_test_view(2);
  view->show();
  QVERIFY(view->scene()->selectedItems().empty());
  for (int i=0; i!=100; ++i) //Very often
  {
    QTest::keyClick(view.get(), Qt::Key_Space, Qt::NoModifier);
    view->show();
    QVERIFY(view->scene()->selectedItems().size() == 1);
  }
}

void ribi::qtkeyboardfriendlygraphicsview_test
  ::tap_shift_should_not_remove_focus()
{

  #ifdef FIX_ISSUE_3
  auto view = create_test_view(2);
  view->show();
  const auto items = view->items();
  assert(items.size() == 2);
  const auto item1 = items[0];
  const auto item2 = items[1];
  //item1 unselected and unfocused at right
  item1->setSelected(false);
  item1->setPos(1.0,0.0);
  //item2 selected and focused at left
  item2->setSelected(true);
  item2->setPos(0.0,1.0);
  ReallyLoseFocus(*view);
  view->showFullScreen();
  qApp->processEvents();
  item2->setSelected(true);
  item2->setFocus();
  view->show();
  QVERIFY(item2->isVisible());
  QVERIFY(item2->hasFocus());
  QTest::keyClick(view.get(), Qt::Key_Shift, Qt::NoModifier, 100);
  view->show();
  QVERIFY(item2->hasFocus());
  #endif // FIX_ISSUE_3
}

void ribi::qtkeyboardfriendlygraphicsview_test
  ::version()
{
  QVERIFY(!GetQtKeyboardFriendlyGraphicsViewVersion().empty());
  QVERIFY(!GetQtKeyboardFriendlyGraphicsViewVersionHistory().empty());
}

void ribi::qtkeyboardfriendlygraphicsview_test
  ::select_random_node_keyboard_edit()
{
  auto dialog = create_test_dialog(2);
  qApp->setActiveWindow(dialog.get());
  qApp->beep();
  dialog->show();
  assert(dialog->layout());
  const auto view = dynamic_cast<ribi::QtKeyboardFriendlyGraphicsView*>(
    dialog->layout()->itemAt(0)->widget());
  assert(view);
  const auto items = view->items();
  assert(items.size() == 2);
  const auto item1 = items[0];
  const auto item2 = items[1];
  for (const auto item: items)
  {
    item->clearFocus();
    item->setSelected(true);
  }

  QVERIFY(view->scene()->selectedItems().size() == 2);

  std::map<QGraphicsItem*, int> tally;
  tally.insert(std::make_pair(item1, 0));
  tally.insert(std::make_pair(item2, 0));
  const int n{1000};
  for (int i=0; i!=n; ++i)
  {
    QTest::keyClick(view, Qt::Key_Space, Qt::NoModifier, 10);
    qApp->processEvents();
    view->show();

    const auto selected_items = view->scene()->selectedItems();
    const auto n_items_selected = selected_items.size();
    QVERIFY(n_items_selected == 1);
    ++tally[selected_items[0]];
  }
  //Test if there are two IDs, both occuring multiple times
  QVERIFY(tally[item1] != n);
  QVERIFY(tally[item2] != n);
  assert(!"FIXED");
}
