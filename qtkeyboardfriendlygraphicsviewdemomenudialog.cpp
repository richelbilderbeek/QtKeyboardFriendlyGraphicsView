#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtkeyboardfriendlygraphicsviewdemomenudialog.h"
#include "qtkeyboardfriendlygraphicsviewmenudialog.h"

#include <sstream>

#include <QDesktopWidget>
#include <QKeyEvent>
#include <QTimer>

#include "about.h"
#include "qtaboutdialog.h"
#include "qtarrowitem.h"
#include "qtdisplaypositem.h"
#include "qtleftrightrectitem.h"
#include "qtpatharrowitem.h"
#include "qtquadbezierarrowitem.h"
#include "qtroundedrectitem.h"
#include "qtroundededitrectitem.h"
#include "qtkeyboardfriendlygraphicsviewdemowidget.h"
#include "qtkeyboardfriendlygraphicsviewdemomenudialog.h"
#include "ui_qtkeyboardfriendlygraphicsviewdemomenudialog.h"
#pragma GCC diagnostic pop

namespace ribi {
  namespace testqtkeyboardfriendlygraphicsviewmenudialog {
    QKeyEvent CreateCtrlLeft() noexcept
    {
      return QKeyEvent(QEvent::KeyPress,Qt::Key_Left,Qt::ControlModifier);
    }
    QKeyEvent CreateCtrlRight() noexcept
    {
      return QKeyEvent(QEvent::KeyPress,Qt::Key_Right,Qt::ControlModifier);
    }
    QKeyEvent CreateShift() noexcept
    {
      return QKeyEvent(QEvent::KeyPress,Qt::Key_Shift,Qt::NoModifier);
    }
    QKeyEvent CreateShiftLeft() noexcept
    {
      return QKeyEvent(QEvent::KeyPress,Qt::Key_Left,Qt::ShiftModifier);
    }
    QKeyEvent CreateShiftRight() noexcept
    {
      return QKeyEvent(QEvent::KeyPress,Qt::Key_Right,Qt::ShiftModifier);
    }
    QKeyEvent CreateDown() noexcept
    {
      return QKeyEvent(QEvent::KeyPress,Qt::Key_Down,Qt::NoModifier);
    }
    QKeyEvent CreateLeft() noexcept
    {
      return QKeyEvent(QEvent::KeyPress,Qt::Key_Left,Qt::NoModifier);
    }
    QKeyEvent CreateRight() noexcept
    {
      return QKeyEvent(QEvent::KeyPress,Qt::Key_Right,Qt::NoModifier);
    }
    QKeyEvent CreateSpace() noexcept
    {
      return QKeyEvent(QEvent::KeyPress,Qt::Key_Space,Qt::NoModifier);
    }
    QKeyEvent CreateUp() noexcept
    {
      return QKeyEvent(QEvent::KeyPress,Qt::Key_Up,Qt::NoModifier);
    }
    QKeyEvent CreateX() noexcept
    {
      return QKeyEvent(QEvent::KeyPress,Qt::Key_X,Qt::NoModifier);
    }
    QKeyEvent CreateRandomKey() noexcept {
      switch (std::rand() % 10)
      {
        case 0: return CreateCtrlLeft();
        case 1: return CreateCtrlRight();
        case 2: return CreateShift();
        case 3: return CreateShiftLeft();
        case 4: return CreateShiftRight();
        case 5: return CreateLeft();
        case 6: return CreateRight();
        case 7: return CreateSpace();
        case 8: return CreateUp();
        case 9: return CreateX();
      }
      return CreateSpace();
    }
  }
}


ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog
  ::QtTestKeyboardFriendlyGraphicsViewMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestKeyboardFriendlyGraphicsViewMenuDialog),
  m_timer_virtual_bastard{new QTimer(this)},
  m_widget{new Widget}
{
  ui->setupUi(this);
  {
    m_widget->m_signal_request_about.connect(
      boost::bind(&ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::ShowAbout,this));
    m_widget->m_signal_request_quit.connect(
      boost::bind(&ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::Quit,this));
    m_widget->m_signal_request_virtual_bastard.connect(
      boost::bind(
        &ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::ToggleVirtualBastard,
        this
      )
    );
    ui->layout->addWidget(m_widget,0,0);
  }
  //Make this dialog big and centered
  {
    const QRect rect = QDesktopWidget().geometry();
    this->setGeometry(rect.adjusted(0,32,0,-32));
  }
  //Create a polling timer
  {
    QTimer * const timer{new QTimer(this)};
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(OnTimer()));
    timer->setInterval(100);
    timer->start();
  }
  {
    QObject::connect(
      m_timer_virtual_bastard,
      SIGNAL(timeout()),
      this,
      SLOT(OnVirtualBastard())
    );
    m_timer_virtual_bastard->setInterval(100);
    //Do not start the m_timer_virtual_bastard
  }
}

ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog
  ::~QtTestKeyboardFriendlyGraphicsViewMenuDialog() noexcept
{
  delete ui;
  m_widget->m_signal_request_about.disconnect(
    boost::bind(&ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::ShowAbout,this));
  m_widget->m_signal_request_quit.disconnect(
    boost::bind(&ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::Quit,this));
}

void ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) close();
}

void ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::OnTimer()
{
  const auto scene = m_widget->scene();
  std::stringstream s;
  s << "#Items: " << scene->items().size() << '\n'
    << "#Selected: " << scene->selectedItems().size() << '\n'
  ;
  for (const auto item: scene->selectedItems())
  {
    assert(item);
    const std::string t{item->toolTip().toStdString()};
    s << " * " << t << '\n';
  }
  const std::string f{(scene->focusItem()
    ? scene->focusItem()->toolTip().toStdString()
    : std::string("[none]"))
  };
  s << "Focus: " << f << '\n';
  ui->plainTextEdit->setPlainText(s.str().c_str());
}

void ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::OnVirtualBastard()
{
  QKeyEvent event{
    testqtkeyboardfriendlygraphicsviewmenudialog::CreateRandomKey()
  };
  m_widget->keyPressEvent(&event);
}

void ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::ShowAbout()
{
  About about = TestKeyboardFriendlyGraphicsViewMenuDialog().GetAbout();
  about.AddLibrary("QtArrowItem version: " + QtArrowItem::GetVersion());
  about.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  about.AddLibrary("QtDisplayPosItem version: " + QtDisplayPosItem::GetVersion());
  about.AddLibrary("QtKeyboardFriendlyGraphicsView version: "
    + GetTestKeyboardFriendlyGraphicsViewVersion()
  );
  about.AddLibrary("QtLeftRightRectItem version: " + QtLeftRightRectItem::GetVersion());
  about.AddLibrary("QtPathArrowItem version: " + QtPathArrowItem::GetVersion());
  about.AddLibrary("QtQuadBezierArrowItem version: " + QtQuadBezierArrowItem::GetVersion());
  about.AddLibrary("QtRoundedRectItem version: " + QtRoundedRectItem::GetVersion());
  about.AddLibrary("QtRoundedEditRectItem version: " + QtRoundedEditRectItem::GetVersion());
  QtAboutDialog d(about);
  d.setWindowIcon(this->windowIcon());
  this->ShowChild(&d);
}

void ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::ToggleVirtualBastard()
{
  if (m_timer_virtual_bastard->isActive()) {
    m_timer_virtual_bastard->stop();
  }
  else {
    m_timer_virtual_bastard->start();
  }
}

void ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::Quit()
{
  close();
}


std::string ribi::GetTestKeyboardFriendlyGraphicsViewVersion() noexcept
{
  return "1.1";
}

std::vector<std::string>
  ribi::GetTestKeyboardFriendlyGraphicsViewVersionHistory() noexcept
{
  return {
    "2012-12-13: version 0.1: initial version",
    "2012-12-17: version 0.2: initial release, added about sceen, adding items, showing help",
    "2012-12-19: version 0.3: improved looks, added QtArrowItem, "
      "QtPathArrowItem, QtRoundedTextRect",
    "2013-11-05: version 0.4: conformized for ProjectRichelBilderbeekConsole",
    "2015-10-02: version 1.0: moved to own GitHub TestKeyboardFriendlyGraphicsView",
    "2016-09-11: version 1.1: moved to own GitHub QtKeyboardFriendlyGraphicsView"
  };
}
