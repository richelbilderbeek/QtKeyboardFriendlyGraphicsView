#include "qtkeyboardfriendlygraphicsviewmenudialog.h"

#include <cassert>
#include <iostream>

int ribi::TestKeyboardFriendlyGraphicsViewMenuDialog
  ::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc != 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  std::cout << "TestKeyboardFriendlyGraphicsViewMenuDialog does not have "
    << "a command-line version\n"
  ;
  return 0;
}

ribi::About ribi::TestKeyboardFriendlyGraphicsViewMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestKeyboardFriendlyGraphicsView",
    "tests QtKeyboardFriendlyGraphicsView",
    "the 2nd of October 2015",
    "2012-2016",
    "http://www.richelbilderbeek.nl/ToolTestKeyboardFriendlyGraphicsView.htm",
    GetVersion(),
    GetVersionHistory()
  );
  return a;
}

ribi::Help ribi::TestKeyboardFriendlyGraphicsViewMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

std::string ribi::TestKeyboardFriendlyGraphicsViewMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi
  ::TestKeyboardFriendlyGraphicsViewMenuDialog::GetVersionHistory() const noexcept
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
