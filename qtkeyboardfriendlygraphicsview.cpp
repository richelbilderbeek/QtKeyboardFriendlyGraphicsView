#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtkeyboardfriendlygraphicsview.h"

#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <random>
#include <stdexcept>
#include <QDebug>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsSimpleTextItem>

#include "container.h"

#pragma GCC diagnostic pop

ribi::QtKeyboardFriendlyGraphicsView::QtKeyboardFriendlyGraphicsView(QWidget* parent)
  : QGraphicsView(new QGraphicsScene,parent)
{
  assert(scene());
}

void ribi::AddSelectRandomItem(
  QtKeyboardFriendlyGraphicsView& q,
  QKeyEvent * const event
)
{
  assert(event);
  const auto selectable_items = GetSelectableVisibleItems(q.GetScene());
  if (selectable_items.empty())
  {
    event->ignore();
    return;
  }
  if (selectable_items.size() == 1)
  {
    SetRandomSelectedness(q, event); //Handles acceptance of event
    return;
  }
  //Filter for items that are not yet selected
  QList<QGraphicsItem *> unselected_items;
  std::copy_if(
    std::begin(selectable_items), std::end(selectable_items),
    std::back_inserter(unselected_items),
      [](const auto item) { return !item->isSelected(); }
  );
  if (unselected_items.empty())
  {
    //Are there still items left to add-select?
    event->ignore();
    return;
  }
  static std::mt19937 rng_engine{0};
  std::uniform_int_distribution<int> distribution(0, static_cast<int>(unselected_items.size()) - 1);
  const int i{distribution(rng_engine)};
  assert(i >= 0);
  assert(i < unselected_items.size());
  auto& new_focus_item = unselected_items[i];
  assert(!new_focus_item->isSelected());
  new_focus_item->setSelected(true);
}

QList<QGraphicsItem *> ribi::CollectFocusableAndSelectableItems(
  const QtKeyboardFriendlyGraphicsView& v)
{
  //Collect focusable items
  const QList<QGraphicsItem *> all_items = v.items();
  QList<QGraphicsItem *> items;
  std::copy_if(std::begin(all_items),std::end(all_items),std::back_inserter(items),
    [](const QGraphicsItem* const item)
    {
      return (item->flags() & QGraphicsItem::ItemIsFocusable)
        && (item->flags() & QGraphicsItem::ItemIsSelectable)
        && item->isVisible();
    }
  );
  return items;
}

std::unique_ptr<QGraphicsItem> ribi::CreateFocusableAndSelectableItem(
  const std::string tooltip
)
{
  std::unique_ptr<QGraphicsItem> item{
    new QGraphicsRectItem
  };
  item->setToolTip(tooltip.c_str());
  item->setFlag(QGraphicsItem::ItemIsFocusable);
  item->setFlag(QGraphicsItem::ItemIsSelectable);
  return item;
}

void ribi::DoSelect(QGraphicsItem * const nsi)
{
  if (nsi)
  {
    assert(!nsi->isSelected());
    nsi->setSelected(true);
    if (!nsi->isSelected())
    {
      qDebug() << "Warning: nsi not selected";
    }
  }
}

void ribi::DoFocus(QGraphicsItem * const nsi)
{
  if (nsi) {
    nsi->setFocus();
    if (!nsi->hasFocus())
    {
      qDebug() << "Warning: nsi has not received focus";
    }
  }
}

QGraphicsItem* ribi::GetClosest(
  const QGraphicsItem* const focus_item,
  const std::vector<QGraphicsItem *>& items) noexcept
{
  if (items.empty()) return nullptr;
  assert(std::count(items.begin(),items.end(),focus_item) == 0);

  QGraphicsItem* best = nullptr;
  double best_distance = std::numeric_limits<double>::max();
  for (QGraphicsItem* const item: items)
  {
    if (!(item->flags() & QGraphicsItem::ItemIsFocusable)) continue;
    if (!(item->isVisible())) continue;

    assert(item != focus_item);
    const double distance = GetDistance(focus_item->pos(),item->pos());
    if (distance < best_distance)
    {
      best_distance = distance;
      best = item;
    }
  }

  assert(best != focus_item);
  return best; //best can be nullptr
}

double ribi::GetDistance(const QPointF& a, const QPointF& b)
{
  const double dx = a.x() - b.x();
  const double dy = a.y() - b.y();
  return std::sqrt((dx * dx) + (dy * dy));
}

QGraphicsItem * ribi::GetClosestNonselectedItem(
  const QtKeyboardFriendlyGraphicsView& q,
  const QGraphicsItem* const focus_item,
  const int key
)
{
  QGraphicsItem * cnsi = nullptr; //closest_nonselected_item
  switch (key)
  {
    case Qt::Key_Up:
      cnsi
        = GetClosestNonselectedItem(q, focus_item, Direction::above);
      break;
    case Qt::Key_Right:
      cnsi
        = GetClosestNonselectedItem(q, focus_item, Direction::right);
      break;
    case Qt::Key_Down:
      cnsi
        = GetClosestNonselectedItem(q, focus_item, Direction::below);
      break;
    case Qt::Key_Left:
      cnsi
        = GetClosestNonselectedItem(q, focus_item, Direction::left);
      break;
    default:
      return nullptr;
  }
  return cnsi;
}

QGraphicsItem * ribi::GetClosestNonselectedItem(
  const QtKeyboardFriendlyGraphicsView& q,
  const QGraphicsItem* const focus_item,
  const Direction direction
)
{
  std::vector<QGraphicsItem *> v = Look(q, GetStrictSearchFunction(direction));

  //If nothing found, look more loosely
  if (v.empty())
  {
    v = Look(q, GetLooseSearchFunction(direction));
  }
  if (v.empty()) return nullptr;

  assert(Container().AllUnique(v));
  QGraphicsItem * const closest_item = GetClosest(focus_item,v);
  if (!closest_item) return nullptr;
  assert(closest_item != focus_item);
  assert(!closest_item->isSelected());
  return closest_item;
}

std::function<bool(const double, const double)> ribi::GetLooseSearchFunction(
  const Direction direction
)
{
  const auto f_loose_above  = [](const double /* dx */, const double dy) { return dy < 0.0; };
  const auto f_loose_below  = [](const double /* dx */, const double dy) { return dy > 0.0; };
  const auto f_loose_left  = [](const double dx, const double /* dy */) { return dx < 0.0; };
  const auto f_loose_right  = [](const double dx, const double /* dy */) { return dx > 0.0; };

  switch (direction)
  {
    case Direction::above: return f_loose_above;
    case Direction::below: return f_loose_below;
    case Direction::left: return f_loose_left;
    case Direction::right: return f_loose_right;
  }
  assert(!"Should not get here");
  throw std::logic_error("Cannot get here");
}

std::vector<QGraphicsItem *> ribi::GetNonSelectedNonFocusItems(
  const QtKeyboardFriendlyGraphicsView& q
) noexcept
{
  const QList<QGraphicsItem *> all_items = q.items();

  std::vector<QGraphicsItem *> nonselected_items;
  std::copy_if(
    std::begin(all_items),
    std::end(all_items),
    std::back_inserter(nonselected_items),
    [](const QGraphicsItem * const item) { return !item->isSelected(); }
  );
  //Remove the focus item
  nonselected_items.erase(
    std::remove(
      std::begin(nonselected_items),
      std::end(nonselected_items),
      q.GetScene().focusItem()
    ),
    std::end(nonselected_items)
  );
  assert(
    std::count(
      std::begin(nonselected_items),
      std::end(nonselected_items),
      q.GetScene().focusItem()
    )
    == 0
  );
  return nonselected_items;
}

QGraphicsScene& ribi::QtKeyboardFriendlyGraphicsView::GetScene() noexcept
{
  assert(scene());
  return *scene();
}

const QGraphicsScene& ribi::QtKeyboardFriendlyGraphicsView::GetScene() const noexcept
{
  assert(scene());
  return *scene();
}

std::string ribi::GetQtKeyboardFriendlyGraphicsViewVersion() noexcept
{
  return "1.4";
}

std::vector<std::string> ribi::GetQtKeyboardFriendlyGraphicsViewVersionHistory() noexcept
{
  return {
    "2012-12-13: version 1.0: initial version",
    "2012-12-31: version 1.1: improved moving focus",
    "2015-08-24: version 1.2: move item with CTRL, add selected with SHIFT, "
      "can move multiple items",
    "2015-09-18: version 1.3: added verbosity",
    "2015-08-16: version 1.4: keyPressEvent may throw"
  };
}

QList<QGraphicsItem *> ribi::GetSelectableVisibleItems(const QGraphicsScene& s) noexcept
{
  const auto all_items = s.items();
  QList<QGraphicsItem *> items;
  std::copy_if(all_items.begin(),all_items.end(),std::back_inserter(items),
    [](const QGraphicsItem* const item)
    {
      return (item->flags() & QGraphicsItem::ItemIsSelectable)
        && item->isVisible();
    }
  );
  return items;
}

std::function<bool(const double, const double)> ribi::GetStrictSearchFunction(
  const Direction direction
)
{
  const auto f_strict_above = [](const double dx, const double dy)
  {
    return dy < 0.0 && std::abs(dx) < std::abs(dy);
  };
  const auto f_strict_below = [](const double dx, const double dy)
  {
    return dx > 0.0 && std::abs(dx) < std::abs(dy);
  };
  const auto f_strict_left = [](const double dx, const double dy)
  {
    return dx < 0.0 && std::abs(dy) < std::abs(dx);
  };
  const auto f_strict_right = [](const double dx, const double dy)
  {
    return dx > 0.0 && std::abs(dy) < std::abs(dx);
  };

  switch (direction)
  {
    case Direction::above: return f_strict_above;
    case Direction::below: return f_strict_below;
    case Direction::left: return f_strict_left;
    case Direction::right: return f_strict_right;
  }
  assert(!"Should not get here");
  throw std::logic_error("Cannot get here");
}

void ribi::QtKeyboardFriendlyGraphicsView::keyPressEvent(QKeyEvent *event)
{
  if (event->modifiers() & Qt::ControlModifier) {
    KeyPressEventCtrl(*this, event);
  }
  else if (event->modifiers() & Qt::ShiftModifier) {
    KeyPressEventShift(*this, event);
  }
  else {
    KeyPressEventNoModifiers(*this, event);
  }
  this->repaint();
  this->update();
}

void ribi::KeyPressEventCtrl(
  QtKeyboardFriendlyGraphicsView& q,
  QKeyEvent * const event
) noexcept
{
  //CTRL: Move items
  assert(event->modifiers() & Qt::ControlModifier);

  //Do special movements
  if (event->key() == Qt::Key_Space)
  {
    SetRandomSelectedness(q, event);
    return;
  }


  double delta_x{0.0};
  double delta_y{0.0};
  switch (event->key())
  {
    case Qt::Key_Up:
      delta_y = -10.0;
      break;
    case Qt::Key_Right:
      delta_x =  10.0;
      break;
    case Qt::Key_Down:
      delta_y =  10.0;
      break;
    case Qt::Key_Left:
      delta_x = -10.0;
      break;
    default:
      event->ignore();
      return;
  }
  for (const auto item: q.GetScene().selectedItems())
  {
    assert(item);
    if (!(item->flags() & QGraphicsItem::ItemIsMovable)) { continue; }
    item->setPos(item->pos() + QPointF(delta_x,delta_y));
  }
  q.GetScene().update();
}

void ribi::KeyPressEventNoModifiers(
  QtKeyboardFriendlyGraphicsView& q,
  QKeyEvent * const event
) noexcept
{
  assert(!(event->modifiers() & Qt::ShiftModifier));
  assert(!(event->modifiers() & Qt::ControlModifier));

  switch (event->key())
  {
    case Qt::Key_Space:
      SetRandomFocus(q, event); //If you want to select a random item, use CTRL-space
      return;
    case Qt::Key_Up:
    case Qt::Key_Right:
    case Qt::Key_Left:
    case Qt::Key_Down:
      KeyPressEventNoModifiersArrowKey(q, event);
      return;
    default:
      event->ignore();
      return;
  }
}

void ribi::KeyPressEventNoModifiersArrowKey(
  QtKeyboardFriendlyGraphicsView& q,
  QKeyEvent *event
) noexcept
{
  QGraphicsItem* const current_focus_item = q.GetScene().focusItem(); //Can be nullptr
  if (!current_focus_item) {
    event->ignore();
    return;
  }

  QGraphicsItem * const nsi // new_selected_item
    = GetClosestNonselectedItem(q, current_focus_item,event->key());
  assert(nsi != current_focus_item);

  //Unselect currently selected
  const auto csi = q.GetScene().selectedItems(); //current_selected_items
  for (const auto item: csi)
  {
    assert(item->isSelected());
    item->setSelected(false);
  }
  assert(!current_focus_item->isSelected() && "Focus item must have lost focus now");

  //Select newly selected
  DoSelect(nsi);
  //Transfer focus
  current_focus_item->clearFocus();
  DoFocus(nsi);
}

void ribi::KeyPressEventShift(
  QtKeyboardFriendlyGraphicsView& q,
  QKeyEvent *event
) noexcept
{
  assert(event->modifiers() & Qt::ShiftModifier);
  if (event->key() == Qt::Key_Space)
  {
    AddSelectRandomItem(q, event);
    return;
  }

  const std::set<int> keys_accepted = { Qt::Key_Up, Qt::Key_Right, Qt::Key_Down, Qt::Key_Left };
  if (keys_accepted.count(event->key()) == 0)
  {
    event->ignore();
    return;
  }

  //Add selectedness to items
  //Can be nullptr
  QGraphicsItem* const current_focus_item = q.GetScene().focusItem();
  if (!current_focus_item)
  {
    event->ignore();
    return;
  }

  QGraphicsItem * const nasi //new_added_selected_item
    = GetClosestNonselectedItem(q, current_focus_item,event->key())
  ;
  assert(!nasi || nasi != current_focus_item);

  //Add selectedness
  if (nasi)
  {
    assert(!nasi->isSelected());
    nasi->setSelected(true);
  }

  //Transfer focus
  assert(current_focus_item);
  current_focus_item->clearFocus();
  if (nasi) { nasi->setFocus(); }
  q.GetScene().update();
}

std::vector<QGraphicsItem *> ribi::Look(
  const QtKeyboardFriendlyGraphicsView& q,
  const std::function<bool(const double, const double)>& f
)
{
  const std::vector<QGraphicsItem *> nonselected_items{
    GetNonSelectedNonFocusItems(q)
  };

  std::vector<QGraphicsItem *> v;
  for(QGraphicsItem* const item: nonselected_items)
  {
    const auto focus_item = q.GetScene().focusItem();
    const double dx = item->pos().x() - focus_item->pos().x();
    const double dy = item->pos().y() - focus_item->pos().y();
    if (f(dx,dy))
    {
      assert(item != focus_item);
      if (!item->isSelected()) { v.push_back(item); }
    }
  }
  return v;
}

#ifdef BELIEVE_THIS_IS_A_GOOD_IDEA_20170809
void ribi::ReallyLoseFocus(QtKeyboardFriendlyGraphicsView& q) noexcept
{
  if (QGraphicsItem* const item = q.GetScene().focusItem())
  {
    assert(item);
    //Really lose focus
    //item->setSelected(false); // #239
    item->setEnabled(false);
    //assert(item->isSelected()); //Not true
    item->clearFocus();
    item->setEnabled(true);
  }
}
#endif // BELIEVE_THIS_IS_A_GOOD_IDEA_20170809

void ribi::SetRandomFocus(
  QtKeyboardFriendlyGraphicsView& q,
  QKeyEvent * const event
)
{
  const auto items = CollectFocusableAndSelectableItems(q);
  if (items.empty())
  {
    event->ignore();
    return;
  }

  //ReallyLoseFocus(q);
  q.GetScene().clearFocus();

  for (auto item: q.GetScene().selectedItems())
  {
    assert(item->isSelected());
    item->setSelected(false);
  }
  assert(!items.empty());

  //Let a random item receive focus
  static std::mt19937 rng_engine{0};
  std::uniform_int_distribution<int> distribution(0, static_cast<int>(items.size()) - 1);
  const int i{distribution(rng_engine)};
  assert(i >= 0);
  assert(i < items.size());
  auto& new_focus_item = items[i];
  assert(!new_focus_item->isSelected());
  assert(new_focus_item->flags() & QGraphicsItem::ItemIsFocusable);
  assert(new_focus_item->flags() & QGraphicsItem::ItemIsSelectable);
  assert(new_focus_item->isVisible());
  new_focus_item->setFocus(Qt::TabFocusReason);
  new_focus_item->setSelected(true);
  new_focus_item->setFocus(Qt::TabFocusReason);
  new_focus_item->setSelected(true);
  //#define REALLY_LET_ME_KNOW
  #ifdef REALLY_LET_ME_KNOW
  if (!new_focus_item->isSelected())
  {
    qDebug() << "Warning: setSelected did not select the item";
  }
  if (!new_focus_item->hasFocus())
  {
    qDebug() << "Warning: setFocus did not set focus to the item";
  }
  #endif // REALLY_LET_ME_KNOW
}

void ribi::SetRandomSelectedness(
  QtKeyboardFriendlyGraphicsView& q,
  QKeyEvent * const event
)
{
  assert(event);

  //Choose a random item visible item to receive selectedness
  const QList<QGraphicsItem *> items = GetSelectableVisibleItems(q.GetScene());
  if (items.empty())
  {
    event->ignore();
    return;
  }
  UnselectAllItems(q);

  //ReallyLoseFocus(q);
  q.GetScene().clearFocus();

  assert(q.GetScene().selectedItems().size() == 0);
  assert(!items.empty());
  static std::mt19937 rng_engine{0};
  std::uniform_int_distribution<int> distribution(0, static_cast<int>(items.size()) - 1);
  const int i{distribution(rng_engine)};
  assert(i >= 0);
  assert(i < items.size());
  auto& new_focus_item = items[i];
  assert(!new_focus_item->isSelected());
  new_focus_item->setSelected(true);
  assert(q.GetScene().selectedItems().size() == 1);
}

void ribi::UnselectAllItems(
  QtKeyboardFriendlyGraphicsView& q
)
{
  for (auto item: q.GetScene().items())
  {
    item->setSelected(false);
  }
  assert(q.GetScene().selectedItems().size() == 0);
}
