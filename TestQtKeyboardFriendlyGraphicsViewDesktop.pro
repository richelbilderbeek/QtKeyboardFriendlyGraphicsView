CONFIG += debug_and_release

include(../RibiLibraries/DesktopApplicationNoWeffcpp.pri)

include(../RibiClasses/CppAbout/CppAbout.pri)
include(../RibiClasses/CppFileIo/CppFileIo.pri)
include(../RibiClasses/CppHelp/CppHelp.pri)
include(../RibiClasses/CppMenuDialog/CppMenuDialog.pri)

include(../RibiLibraries/GeneralDesktop.pri)
include(../RibiLibraries/Apfloat.pri)
include(../RibiLibraries/BoostAll.pri)

include(../RibiClasses/CppCounter/CppCounter.pri)
include(../RibiClasses/CppContainer/CppContainer.pri)
include(../RibiClasses/CppGeometry/CppGeometry.pri)
include(../RibiClasses/CppPlane/CppPlane.pri)
include(../RibiClasses/CppRibiRegex/CppRibiRegex.pri)
include(../RibiClasses/CppRibiSystem/CppRibiSystem.pri)
include(../RibiClasses/CppRibiTime/CppRibiTime.pri)

include(../RibiClasses/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../RibiClasses/CppGrabber/CppGrabber.pri)
include(../RibiClasses/CppQtArrowItem/CppQtArrowItem.pri)
include(../RibiClasses/CppQtDisplayPosItem/CppQtDisplayPosItem.pri)
include(QtKeyboardFriendlyGraphicsView.pri)
include(../RibiClasses/CppQtLeftRightRectItem/CppQtLeftRightRectItem.pri)
include(../RibiClasses/CppQtPathArrowItem/CppQtPathArrowItem.pri)
include(../RibiClasses/CppQtQuadBezierArrowItem/CppQtQuadBezierArrowItem.pri)
include(../RibiClasses/CppQtRoundedEditRectItem/CppQtRoundedEditRectItem.pri)
include(../RibiClasses/CppQtRoundedRectItem/CppQtRoundedRectItem.pri)

include(TestQtKeyboardFriendlyGraphicsViewDesktop.pri)

SOURCES += qtmain.cpp
