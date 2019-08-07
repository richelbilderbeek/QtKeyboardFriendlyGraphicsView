include(../RibiClasses/CppAbout/CppAbout.pri)
include(../RibiClasses/CppFileIo/CppFileIo.pri)
include(../RibiClasses/CppHelp/CppHelp.pri)
include(../RibiClasses/CppMenuDialog/CppMenuDialog.pri)
include(../RibiClasses/CppQtAboutDialog/CppQtAboutDialog.pri)
include(../RibiClasses/CppQtHideAndShowDialog/CppQtHideAndShowDialog.pri)

#include(../RibiLibraries/BoostAll.pri)

include(../RibiClasses/CppCounter/CppCounter.pri)
include(../RibiClasses/CppContainer/CppContainer.pri)
include(../RibiClasses/CppGeometry/CppGeometry.pri)
include(../plane/plane.pri)
include(../RibiClasses/CppRibiRegex/CppRibiRegex.pri)
include(../RibiClasses/CppRibiSystem/CppRibiSystem.pri)
include(../RibiClasses/CppRibiTime/CppRibiTime.pri)

include(../RibiClasses/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../RibiClasses/CppGrabber/CppGrabber.pri)
include(../RibiClasses/CppQtArrowItem/CppQtArrowItem.pri)
include(../RibiClasses/CppQtDisplayPosItem/CppQtDisplayPosItem.pri)
include(QtKeyboardFriendlyGraphicsView.pri)
include(QtKeyboardFriendlyGraphicsViewDemoDesktop.pri)
include(../RibiClasses/CppQtLeftRightRectItem/CppQtLeftRightRectItem.pri)
include(../RibiClasses/CppQtPathArrowItem/CppQtPathArrowItem.pri)
include(../RibiClasses/CppQtQuadBezierArrowItem/CppQtQuadBezierArrowItem.pri)
include(../RibiClasses/CppQtRoundedEditRectItem/CppQtRoundedEditRectItem.pri)
include(../RibiClasses/CppQtRoundedRectItem/CppQtRoundedRectItem.pri)


# QtNode
test_qt_note {
  INCLUDEPATH += ../boost_graph_cookbook_1/boost_graph_cookbook_1
  include(../boost_graph_cookbook_1/boost_graph_cookbook_1/boost_graph_cookbook_1_helper.pri)
  include(../boost_graph_cookbook_1/boost_graph_cookbook_1/boost_graph_cookbook_1_no_properties.pri)
  include(../RibiClasses/CppXml/CppXml.pri)
  include(../RibiClasses/CppQtImage/CppQtImage.pri)
  include(../ConceptMap/ConceptMap.pri)
  include(../QtConceptMap/QtConceptMap.pri)
  include(gsl.pri)
}

SOURCES += qtmain.cpp


CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

# Qt and Qwt do not go well with -Weffc++
# -Wshadow does not go well with Qwt
QMAKE_CXXFLAGS += -Wall -Wextra -Wnon-virtual-dtor -pedantic -Werror

# Debug and release mode
CONFIG += debug_and_release

# In release mode, define NDEBUG
CONFIG(release, debug|release) {
  DEFINES += NDEBUG
}

# In debug mode, turn on gcov and UBSAN
CONFIG(debug, debug|release) {

  # gcov
  QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
  LIBS += -lgcov

  # UBSAN
  QMAKE_CXXFLAGS += -fsanitize=undefined
  QMAKE_LFLAGS += -fsanitize=undefined
  LIBS += -lubsan
}

# Boost.Graph
LIBS += \
  -lboost_graph \
  -lboost_date_time \
  -lboost_graph \
  -lboost_regex

# Qt5
QT += core gui widgets svg

# Prevent Qt for failing with this error:
# qrc_[*].cpp:400:44: error: ‘qInitResources_[*]__init_variable__’ defined but not used
# [*]: the resource filename
QMAKE_CXXFLAGS += -Wno-unused-variable

# Fixes
#/usr/include/boost/math/constants/constants.hpp:277: error: unable to find numeric literal operator 'operator""Q'
#   BOOST_DEFINE_MATH_CONSTANT(half, 5.000000000000000000000000000000000000e-01, "5.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-01")
#   ^
QMAKE_CXXFLAGS += -fext-numeric-literals

# Qt:
# QtConcurrent::filterInternal(Sequence&, KeepFunctor, ReduceFunctor)’:
# /usr/include/qt4/QtCore/qtconcurrentfilter.h:108:47: error: typedef ‘Iterator’ locally defined but not used [-Werror=unused-local-typedefs]
# typedef typename Sequence::const_iterator Iterator;
QMAKE_CXXFLAGS += -Wno-unused-local-typedefs

