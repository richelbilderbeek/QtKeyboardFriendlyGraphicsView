//---------------------------------------------------------------------------
/*
TestKeyboardFriendlyGraphicsView, tests QtKeyboardFriendlyGraphicsView
Copyright (C) 2012-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestKeyboardFriendlyGraphicsView.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestqtkeyboardfriendlygraphicsviewmenudialog.h"

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
#include "testtimer.h"
#include "qttestqtkeyboardfriendlygraphicsviewwidget.h"
#include "testqtkeyboardfriendlygraphicsviewmenudialog.h"
#include "trace.h"
#include "ui_qttestqtkeyboardfriendlygraphicsviewmenudialog.h"
#pragma GCC diagnostic pop

namespace ribi {
  namespace testqtkeyboardfriendlygraphicsviewmenudialog {
    QKeyEvent CreateCtrlLeft() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Left,Qt::ControlModifier); }
    QKeyEvent CreateCtrlRight() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Right,Qt::ControlModifier); }
    QKeyEvent CreateShift() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Shift,Qt::NoModifier); }
    QKeyEvent CreateShiftLeft() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Left,Qt::ShiftModifier); }
    QKeyEvent CreateShiftRight() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Right,Qt::ShiftModifier); }
    QKeyEvent CreateDown() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Down,Qt::NoModifier); }
    QKeyEvent CreateLeft() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Left,Qt::NoModifier); }
    QKeyEvent CreateRight() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Right,Qt::NoModifier); }
    QKeyEvent CreateSpace() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Space,Qt::NoModifier); }
    QKeyEvent CreateUp() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Up,Qt::NoModifier); }
    QKeyEvent CreateX() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_X,Qt::NoModifier); }
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


ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::QtTestKeyboardFriendlyGraphicsViewMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestKeyboardFriendlyGraphicsViewMenuDialog),
  m_timer_virtual_bastard{new QTimer(this)},
  m_widget{new Widget}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  {
    m_widget->m_signal_request_about.connect(
      boost::bind(&ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::ShowAbout,this));
    m_widget->m_signal_request_quit.connect(
      boost::bind(&ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::Quit,this));
    m_widget->m_signal_request_virtual_bastard.connect(
      boost::bind(&ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::ToggleVirtualBastard,this));
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
    QObject::connect(m_timer_virtual_bastard,SIGNAL(timeout()),this,SLOT(OnVirtualBastard()));
    m_timer_virtual_bastard->setInterval(100);
    //Do not start the m_timer_virtual_bastard
  }
}

ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::~QtTestKeyboardFriendlyGraphicsViewMenuDialog() noexcept
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
  const std::string f{(scene->focusItem() ? scene->focusItem()->toolTip().toStdString() : std::string("[none]"))};
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
  about.AddLibrary("QtKeyboardFriendlyGraphicsView version: " + QtKeyboardFriendlyGraphicsView::GetVersion());
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

#ifndef NDEBUG
void ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
