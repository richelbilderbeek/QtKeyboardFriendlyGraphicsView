#ifndef QTTESTKEYBOARDFRIENDLYGRAPHICSVIEWMENUDIALOG_H
#define QTTESTKEYBOARDFRIENDLYGRAPHICSVIEWMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestKeyboardFriendlyGraphicsViewMenuDialog;
}

namespace ribi {

class QtTestKeyboardFriendlyGraphicsViewWidget;

class QtTestKeyboardFriendlyGraphicsViewMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT //!OCLINT
  
public:
  explicit QtTestKeyboardFriendlyGraphicsViewMenuDialog(QWidget *parent = 0);
  QtTestKeyboardFriendlyGraphicsViewMenuDialog(
    const QtTestKeyboardFriendlyGraphicsViewMenuDialog&
  ) = delete;
  QtTestKeyboardFriendlyGraphicsViewMenuDialog& operator=(
    const QtTestKeyboardFriendlyGraphicsViewMenuDialog&
  ) = delete;
  ~QtTestKeyboardFriendlyGraphicsViewMenuDialog() noexcept;

  void ShowAbout();
  void ToggleVirtualBastard();
  void Quit();

private slots:
  void keyPressEvent(QKeyEvent* e);
  void OnTimer();
  void OnVirtualBastard();


private:
  Ui::QtTestKeyboardFriendlyGraphicsViewMenuDialog *ui;

  using Widget = QtTestKeyboardFriendlyGraphicsViewWidget;
  QTimer * const m_timer_virtual_bastard;
  Widget * m_widget;
};

std::string GetTestKeyboardFriendlyGraphicsViewVersion() noexcept;
std::vector<std::string> GetTestKeyboardFriendlyGraphicsViewVersionHistory() noexcept;

} //~namespace ribi

#endif // TESTKEYBOARDFRIENDLYGRAPHICSVIEWMENUDIALOG_H
