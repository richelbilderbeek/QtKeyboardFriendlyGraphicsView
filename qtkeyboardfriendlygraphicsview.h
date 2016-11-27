#ifndef QTKEYBOARDFRIENDLYGRAPHICSVIEW_H
#define QTKEYBOARDFRIENDLYGRAPHICSVIEW_H

#include <functional>
#include <memory>
#include <vector>
#include <QGraphicsView>

struct QGraphicsItem;

namespace ribi {

///The widget holding the items
struct QtKeyboardFriendlyGraphicsView : public QGraphicsView
{
  Q_OBJECT //!OCLINT

public:
  explicit QtKeyboardFriendlyGraphicsView(QWidget* parent = 0);

  virtual ~QtKeyboardFriendlyGraphicsView() noexcept {}

  ///Obtain the QGraphicsScene, which is always present
  const QGraphicsScene& GetScene() const noexcept;
        QGraphicsScene& GetScene() noexcept;

  ///Respond to a key press
  virtual void keyPressEvent(QKeyEvent *event) override;
};

///Add a random item to the selected items
///Occurs when pressing SHIFT-space
void AddSelectRandomItem(
  QtKeyboardFriendlyGraphicsView& q,
  QKeyEvent * const event
);

///Collect the items that are focusable and selectable
QList<QGraphicsItem *> CollectFocusableAndSelectableItems(
  const QtKeyboardFriendlyGraphicsView& v)
;

///Creates a focusable and selectable item
std::unique_ptr<QGraphicsItem> CreateFocusableAndSelectableItem(
  const std::string tooltip = "Item"
);

void DoFocus(QGraphicsItem * const nsi);

void DoSelect(QGraphicsItem * const nsi);

///Obtain the closest item in the collection
///Returns nullptr if there is no focusable item in the items
QGraphicsItem* GetClosest(
  const QGraphicsItem* const focus_item,
  const std::vector<QGraphicsItem *>& items
) noexcept;

///Calculate the Euclidian distance between two points
double GetDistance(const QPointF& a, const QPointF& b);

enum class Direction { above, below, left, right };

QGraphicsItem * GetClosestNonselectedItem(
  const QtKeyboardFriendlyGraphicsView& q,
  const QGraphicsItem* const focus_item,
  int key
);

QGraphicsItem * GetClosestNonselectedItem(
  const QtKeyboardFriendlyGraphicsView& q,
  const QGraphicsItem* const focus_item,
  const Direction direction
);

std::function<bool(const double, const double)> GetLooseSearchFunction(
  const Direction direction
) noexcept;

std::vector<QGraphicsItem *> GetNonSelectedNonFocusItems(
  const QtKeyboardFriendlyGraphicsView& q
) noexcept;

std::string GetQtKeyboardFriendlyGraphicsViewVersion() noexcept;
std::vector<std::string> GetQtKeyboardFriendlyGraphicsViewVersionHistory() noexcept;

QList<QGraphicsItem *> GetSelectableVisibleItems(const QGraphicsScene& s) noexcept;

std::function<bool(const double, const double)> GetStrictSearchFunction(
  const Direction direction
) noexcept;

void KeyPressEventCtrl(
  QtKeyboardFriendlyGraphicsView& q,
  QKeyEvent * const event
) noexcept;

void KeyPressEventNoModifiers(
  QtKeyboardFriendlyGraphicsView& q,
  QKeyEvent * const event
) noexcept;

void KeyPressEventNoModifiersArrowKey(
  QtKeyboardFriendlyGraphicsView& q,
  QKeyEvent * const event
) noexcept;

void KeyPressEventShift(
  QtKeyboardFriendlyGraphicsView& q,
  QKeyEvent * const event
) noexcept;

std::vector<QGraphicsItem *> Look(
  const QtKeyboardFriendlyGraphicsView& q,
  const std::function<bool(const double, const double)>& f
);

void ReallyLoseFocus(QtKeyboardFriendlyGraphicsView& q) noexcept;

///Give focus to a random item
void SetRandomFocus(
  QtKeyboardFriendlyGraphicsView& q,
  QKeyEvent * const event
);

///Give selectedness to one random item,
///event will be ignored if there are no items to selec
void SetRandomSelectedness(
  QtKeyboardFriendlyGraphicsView& q,
  QKeyEvent * const event
);

void UnselectAllItems(QtKeyboardFriendlyGraphicsView& q);

} //~namespace ribi

#endif // QTKEYBOARDFRIENDLYGRAPHICSVIEW_H
