#include "qtkeyboardfriendlygraphicsviewdemowidget.h"

#include <boost/math/constants/constants.hpp>

#include <QKeyEvent>

#include "qtarrowitem.h"

#ifdef TEST_QT_NODE
#include "qtconceptmapqtnode.h"
#endif

#include "qtdisplaypositem.h"
#include "qtleftrightrectitem.h"
#include "qtpatharrowitem.h"
#include "qtquadbezierarrowitem.h"
#include "qtroundededitrectitem.h"
#include "qtroundedrectitem.h"

ribi::QtTestKeyboardFriendlyGraphicsViewWidget::QtTestKeyboardFriendlyGraphicsViewWidget()
  : m_signal_request_about{},
    m_signal_request_quit{},
    m_signal_request_virtual_bastard{}
{
  AddLegend(*this);
  AddGraphicsRectItems(*this);
  AddRoundedRectItems(*this);
  AddRoundedTextRectItems(*this);
  AddLeftRightRectItems(*this);
  AddDisplayPosItems(*this);
  AddQtNodes(*this);
  AddQuadBezierArrows(*this);
  AddArrowItems(*this);
  AddPathArrowItems(*this);
  AddRoundedEditRectItems(*this);
}

void ribi::AddArrowItems(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept
{
  typedef QtArrowItem Item;
  const double midx = -174.0;
  const double midy =  300.0;
  const int n = 3;
  const double ray = 100.0;
  QGraphicsTextItem * const text = new QGraphicsTextItem("QtArrowItem");
  text->setPos(
    midx - text->boundingRect().center().x(),
    midy - text->boundingRect().center().y()
  );
  widget.scene()->addItem(text);
  QGraphicsEllipseItem * const circle{
    new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray)
  };
  widget.scene()->addItem(circle);

  for (int i=0; i!=n; ++i)
  {
    const double pi = boost::math::constants::pi<double>();
    const double angle{
      2.0 * pi * static_cast<double>(i) / static_cast<double>(n)
    };
    const double x1 = midx + std::sin(angle) * 0.5 * ray;
    const double y1 = midy - std::cos(angle) * 0.5 * ray;
    const double x2 = midx + std::sin(angle) * 0.9 * ray;
    const double y2 = midy - std::cos(angle) * 0.9 * ray;
    Item * const item = new Item(x1,y1,false,x2,y2,true);
    widget.scene()->addItem(item);
    item->setToolTip(
      (std::string("QtArrowItem #") + std::to_string(i)).c_str()
    );
  }
}

void ribi::AddDisplayPosItems(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept
{
  typedef QtDisplayPosItem Item;
  const double midx =  174.0;
  const double midy = -100.0;
  const int n = 3;
  const double ray = 100.0;
  QGraphicsTextItem * const text = new QGraphicsTextItem("QtDisplayPosItem");
  text->setPos(
    midx - text->boundingRect().center().x(),
    midy - text->boundingRect().center().y()
  );
  widget.scene()->addItem(text);
  QGraphicsEllipseItem * const circle{
    new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray)
  };
  widget.scene()->addItem(circle);
  for (int i=0; i!=n; ++i)
  {
    const double pi = boost::math::constants::pi<double>();
    const double angle = 2.0 * pi * static_cast<double>(i) / static_cast<double>(n);
    const double x = midx + (std::sin(angle) * 0.5 * ray);
    const double y = midy - (std::cos(angle) * 0.5 * ray);
    Item * const item = new Item;
    item->setPos(x - item->boundingRect().center().x(),y - item->boundingRect().center().y());
    item->setToolTip(
      (std::string("QtDisplayPosItem #") + std::to_string(i)).c_str()
    );
    widget.scene()->addItem(item);
  }
}

void ribi::AddGraphicsRectItems(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept
{
  //QGraphicsRectItems
  typedef QGraphicsRectItem Item;
  const double midx =    0.0;
  const double midy = -200.0;
  const int n = 3;
  const double ray = 100.0;
  QGraphicsTextItem * const text = new QGraphicsTextItem("QGraphicsRectItem");
  text->setToolTip("QGraphicsRectItem text");
  text->setPos(
    midx - text->boundingRect().center().x(),
    midy - text->boundingRect().center().y()
  );
  widget.scene()->addItem(text);
  QGraphicsEllipseItem * const circle{
    new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray)
  };
  circle->setToolTip("QGraphicsRectItem circle");
  widget.scene()->addItem(circle);

  for (int i=0; i!=n; ++i)
  {
    const double pi = boost::math::constants::pi<double>();
    const double angle = 2.0 * pi * static_cast<double>(i) / static_cast<double>(n);
    const double x = midx + (std::sin(angle) * 0.5 * ray);
    const double y = midy - (std::cos(angle) * 0.5 * ray);
    Item * const item = new Item;
    item->setPos(x,y);
    item->setRect(-16.0,-16.0,32.0,32.0);
    item->setFlags(QGraphicsItem::ItemIsFocusable
      | QGraphicsItem::ItemIsMovable
      | QGraphicsItem::ItemIsSelectable
    );
    item->setToolTip(
      (std::string("QGraphicsRectItem #") + std::to_string(i)).c_str()
    );
    widget.scene()->addItem(item);
  }
}


void ribi::AddLeftRightRectItems(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept
{
  //QtLeftRightRectItem
  typedef QtLeftRightRectItem Item;
  const double midx = 174.0;
  const double midy = 100.0;
  const int n = 3;
  const double ray = 100.0;
  QGraphicsTextItem * const text = new QGraphicsTextItem("QtLeftRightRectItem");
  text->setPos(midx - text->boundingRect().center().x(),midy - text->boundingRect().center().y());
  widget.scene()->addItem(text);
  QGraphicsEllipseItem * const circle{
    new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray)
  };
  widget.scene()->addItem(circle);
  for (int i=0; i!=n; ++i)
  {
    const double pi = boost::math::constants::pi<double>();
    const double angle = 2.0 * pi * static_cast<double>(i) / static_cast<double>(n);
    const double x = midx + (std::sin(angle) * 0.5 * ray);
    const double y = midy - (std::cos(angle) * 0.5 * ray);
    Item * const item = new Item;
    item->setPos(x,y);
    item->setToolTip(
      (std::string("QtLeftRightRectItem #") + std::to_string(i)).c_str()
    );
    widget.scene()->addItem(item);
  }
}

void ribi::AddLegend(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept
{
  const double midx = 0.0;
  const double midy = 0.0;
  const double ray = 100.0;
  QGraphicsEllipseItem * const circle{
    new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray)
  };
  circle->setToolTip("Legend circle");
  widget.scene()->addItem(circle);
  {
    QGraphicsTextItem * const item = new QGraphicsTextItem("ESC: Quit");
    item->setToolTip("ESC: Quit");
    widget.scene()->addItem(item);
    item->setPos(
      midx + 0.0 - item->boundingRect().center().x(),
      midy - 20.0 - item->boundingRect().center().y()
    );
  }
  {
    QGraphicsTextItem * const item = new QGraphicsTextItem("a: about");
    item->setToolTip("a: about");
    widget.scene()->addItem(item);
    item->setPos(
      midx + 0.0 - item->boundingRect().center().x(),
      midy +  0.0 - item->boundingRect().center().y()
    );
  }
  {
    QGraphicsTextItem * const item{
      new QGraphicsTextItem("b: start virtual bastard")
    };
    item->setToolTip("b: start virtual bastard");
    widget.scene()->addItem(item);
    item->setPos(
      midx + 0.0 - item->boundingRect().center().x(),
      midy + 20.0 - item->boundingRect().center().y()
    );
  }
}

void ribi::AddPathArrowItems(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept
{
  typedef QtPathArrowItem Item;
  const double midx = -348.0;
  const double midy =  200.0;
  const int n = 3;
  const double ray = 100.0;
  QGraphicsTextItem * const text{
    new QGraphicsTextItem("QtPathArrowItem")
  };
  text->setPos(
    midx - text->boundingRect().center().x(),
    midy - text->boundingRect().center().y()
  );
  widget.scene()->addItem(text);
  QGraphicsEllipseItem * const circle{
    new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray)
  };
  widget.scene()->addItem(circle);

  for (int i=0; i!=n; ++i)
  {
    const double pi = boost::math::constants::pi<double>();
    const double angle = 2.0 * pi * static_cast<double>(i) / static_cast<double>(n);
    const double x1 = midx + std::sin(angle) * 0.5 * ray;
    const double y1 = midy - std::cos(angle) * 0.5 * ray;

    const double x_mid = midx + std::sin(angle + 0.1) * 0.7 * ray;
    const double y_mid = midy - std::cos(angle + 0.1) * 0.7 * ray;

    const double x2 = midx + std::sin(angle) * 0.9 * ray;
    const double y2 = midy - std::cos(angle) * 0.9 * ray;
    Item * const item{
      new Item(QPointF(x1,y1),false, { QPointF(x_mid,y_mid) },true,QPointF(x2,y2))
    };
    item->setToolTip(
      (std::string("QtPathArrowItem #") + std::to_string(i)).c_str()
    );
    widget.scene()->addItem(item);
  }
}

void ribi::AddQuadBezierArrows(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept //!OCLINT will not invest in refactoring a demo for now
{
  using Item = QtQuadBezierArrowItem;
  using boost::math::constants::pi;
  const double midx = -174.0;
  const double midy =  100.0;
  const int n = 3;
  const double radius = 100.0;
  QGraphicsTextItem * const text = new QGraphicsTextItem("QtQuadBezierArrowItem");
  text->setPos(midx - text->boundingRect().center().x(),midy - text->boundingRect().center().y());
  widget.scene()->addItem(text);
  QGraphicsEllipseItem * const circle{
    new QGraphicsEllipseItem(midx - radius, midy - radius,2.0 * radius,2.0 * radius)
  };
  widget.scene()->addItem(circle);

  for (int i=0; i!=n; ++i)
  {
    const double angle = 2.0 * pi<double>() * static_cast<double>(i) / static_cast<double>(n);
    boost::array<QGraphicsItem *, 3> v;
    v.assign(nullptr);
    for (int j = 0; j != 3; ++j)
    {
      const double sub_ray = 90.0;
      const double sub_angle{
        angle
        + (2.0 * 2.0 * pi<double>() * static_cast<double>(j + 1)
            / static_cast<double>( (3 + 2) * n)
          )
      };
      const double x = midx + std::sin(sub_angle) * sub_ray;
      const double y = midy - std::cos(sub_angle) * sub_ray;
      QtRoundedRectItem * const item = new QtRoundedRectItem;
      item->SetOuterWidth(16.0);
      item->SetOuterHeight(8.0);
      //item->SetOuterRoundedRect(QRectF(-4.0,-4.0,8.0,8.0),1.0,1.0);
      item->SetCenterPos(x,y);
      widget.scene()->addItem(item);
      v[j] = item;
    }
    {
      assert(v[0] && v[1] && v[2]);
      Item * const item = new Item(v[0],false,v[1],true,v[2]);
      item->setToolTip(
        (std::string("QtQuadBezierArrow #") + std::to_string(i)).c_str()
      );
      widget.scene()->addItem(item);
    }
  }
}

void ribi::AddQtNodes(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept
{
  #ifdef TEST_QT_NODE
  using Item = ribi::cmap::QtNode;
  const double midx = 2.0 * 174.0;
  const double midy = -200.0;
  const int n = 3;
  const double ray = 100.0;
  QGraphicsTextItem * const text = new QGraphicsTextItem("QtNode");
  text->setPos(
    midx - text->boundingRect().center().x(),
    midy - text->boundingRect().center().y()
  );
  widget.scene()->addItem(text);
  QGraphicsEllipseItem * const circle{
    new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray, 2.0 * ray)
  };
  widget.scene()->addItem(circle);


  for (int i=0; i!=n; ++i)
  {
    const double pi = boost::math::constants::pi<double>();
    const double angle = 2.0 * pi * static_cast<double>(i) / static_cast<double>(n);
    const double x = midx + (std::sin(angle) * 0.5 * ray);
    const double y = midy - (std::cos(angle) * 0.5 * ray);
    auto * const item = new Item();
    item->setPos(x - item->boundingRect().center().x(),y - item->boundingRect().center().y());
    item->setToolTip(
      (std::string("QtNode #") + std::to_string(i)).c_str()
    );
    switch (i)
    {
      case 0:
        item->setFlags(ribi::cmap::CreateEditFlags(*item));
        item->SetText( { "Edit"} );
        break;
      case 1: item->setFlags(ribi::cmap::CreateRateFlags(*item));
        item->SetText( { "Rate"} );
        break;
      case 2: item->setFlags(ribi::cmap::CreateUninitializedFlags(*item));
        item->SetText( { "Uninitialized"} );
        break;
      default: assert(!"Should not get here");
    }
    widget.scene()->addItem(item);
  }
  #else
  assert(widget.size().width() >= 0.0); //Just something
  #endif
}

void ribi::AddRoundedEditRectItems(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept
{
  typedef QtRoundedEditRectItem Item;
  const double midx = 2.0 * 174.0;
  const double midy = 0.0;
  const int n = 3;
  const double ray = 100.0;
  QGraphicsTextItem * const text = new QGraphicsTextItem("QtRoundedEditRectItem");
  text->setPos(midx - text->boundingRect().center().x(),midy - text->boundingRect().center().y());
  widget.scene()->addItem(text);
  QGraphicsEllipseItem * const circle{
    new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray)
  };
  widget.scene()->addItem(circle);
  for (int i=0; i!=n; ++i)
  {
    const double pi = boost::math::constants::pi<double>();
    const double angle = 2.0 * pi * static_cast<double>(i) / static_cast<double>(n);
    const double x = midx + (std::sin(angle) * 0.5 * ray);
    const double y = midy - (std::cos(angle) * 0.5 * ray);
    Item * const item = new Item;
    item->SetCenterPos(x,y);
    std::vector<std::string> text;
    text.push_back("* *");
    for (int j=0; j!=i; ++j)
    {
      const std::string s = std::string(j+2,'*') + " *";
      text.push_back(s);
    }

    item->SetText(text);
    item->setToolTip(
      (std::string("QtRoundedEditRectItem #") + std::to_string(i)).c_str()
    );
    widget.scene()->addItem(item);
  }
}

void ribi::AddRoundedRectItems(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept
{
  //QtRoundedRectItem
  typedef QtRoundedRectItem Item;
  const double midx =   0.0;
  const double midy = 200.0;
  const int n = 3;
  const double ray = 100.0;
  QGraphicsTextItem * const text = new QGraphicsTextItem("QtRoundedRectItem");
  text->setPos(
    midx - text->boundingRect().center().x(),
    midy - text->boundingRect().center().y()
  );
  widget.scene()->addItem(text);
  QGraphicsEllipseItem * const circle{
    new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray)
  };
  widget.scene()->addItem(circle);
  for (int i=0; i!=n; ++i)
  {
    const double pi = boost::math::constants::pi<double>();
    const double angle = 2.0 * pi * static_cast<double>(i) / static_cast<double>(n);
    const double x = midx + (std::sin(angle) * 0.5 * ray);
    const double y = midy - (std::cos(angle) * 0.5 * ray);
    Item * const item = new Item;
    item->SetCenterPos(x,y);
    item->setToolTip(
      (std::string("QtRoundedRectItem #") + std::to_string(i)).c_str()
    );
    widget.scene()->addItem(item);
  }
}

void ribi::AddRoundedTextRectItems(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept
{
  typedef QtRoundedEditRectItem Item;
  const double midx = 174.0;
  const double midy = 300.0;
  const int n = 3;
  const double ray = 100.0;
  QGraphicsTextItem * const text{
    new QGraphicsTextItem("QtRoundedEditRectItem")
  };
  text->setPos(
    midx - text->boundingRect().center().x(),
    midy - text->boundingRect().center().y()
  );
  widget.scene()->addItem(text);
  QGraphicsEllipseItem * const circle{
    new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray)
  };
  widget.scene()->addItem(circle);
  for (int i=0; i!=n; ++i)
  {
    const double pi = boost::math::constants::pi<double>();
    const double angle = 2.0 * pi * static_cast<double>(i) / static_cast<double>(n);
    const double x = midx + (std::sin(angle) * 0.5 * ray);
    const double y = midy - (std::cos(angle) * 0.5 * ray);
    Item * const item = new Item;
    item->SetCenterPos(x,y);
    //item->setRect(-16.0,-16.0,32.0,32.0);
    item->setToolTip(
      (std::string("QtRoundedTextRectItem #") + std::to_string(i)).c_str()
    );
    widget.scene()->addItem(item);
  }
}

void ribi::QtTestKeyboardFriendlyGraphicsViewWidget::DoUpdateScene()
{
  scene()->update();
}




void ribi::QtTestKeyboardFriendlyGraphicsViewWidget::keyPressEvent(QKeyEvent *event) noexcept
{
  switch (event->key())
  {
    case Qt::Key_Escape: m_signal_request_quit(); break;
    case Qt::Key_A     : m_signal_request_about(); break;
    case Qt::Key_B     : m_signal_request_virtual_bastard(); break;
    default: break;
  }
  QtKeyboardFriendlyGraphicsView::keyPressEvent(event);
}

