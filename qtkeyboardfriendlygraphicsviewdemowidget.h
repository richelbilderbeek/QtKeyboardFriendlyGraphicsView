#ifndef QTTESTKEYBOARDFRIENDLYGRAPHICSVIEWWIDGET_H
#define QTTESTKEYBOARDFRIENDLYGRAPHICSVIEWWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

#include "qtkeyboardfriendlygraphicsview.h"

namespace ribi {

///QtTestKeyboardFriendlyGraphicsViewWidget displays my widgets and their relations
struct QtTestKeyboardFriendlyGraphicsViewWidget : public QtKeyboardFriendlyGraphicsView
{
  typedef QtTestKeyboardFriendlyGraphicsViewWidget This;

  QtTestKeyboardFriendlyGraphicsViewWidget();
  ~QtTestKeyboardFriendlyGraphicsViewWidget() noexcept {}

  ///Signal emitted when the user wants to see the about screen
  boost::signals2::signal<void()> m_signal_request_about;

  ///Signal emitted when the user wants to quit
  boost::signals2::signal<void()> m_signal_request_quit;

  ///Signal emitted when the user wants to start/stop the virtual bastard
  boost::signals2::signal<void()> m_signal_request_virtual_bastard;

  void keyPressEvent(QKeyEvent *event) noexcept;

private:

  ///Update the view
  void DoUpdateScene();
};

void AddArrowItems(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept;
void AddDisplayPosItems(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept;
void AddLeftRightRectItems(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept;
void AddLegend(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept;
void AddGraphicsRectItems(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept;
void AddPathArrowItems(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept;
void AddQuadBezierArrows(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept;
void AddRoundedEditRectItems(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept;
void AddRoundedRectItems(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept;
void AddRoundedTextRectItems(QtTestKeyboardFriendlyGraphicsViewWidget& widget) noexcept;

} //~namespace ribi

#endif // QTTESTKEYBOARDFRIENDLYGRAPHICSVIEWWIDGET_H
