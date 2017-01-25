TARGET = TestLib
TEMPLATE = lib

DEPENDPATH += .
INCLUDEPATH += .

CONFIG +=  staticlib \
           gpiopinio \
           cdpunit

include($$(QMAKEFEATURES)/common.pri)

CONFIG -= deploy qt

HEADERS += TestLib.h \
           TestLibBuilder.h \
           ModelSource/GPIOPinIOLoopbackTest.h

SOURCES += TestLibBuilder.cpp \
           ModelSource/GPIOPinIOLoopbackTest.cpp
