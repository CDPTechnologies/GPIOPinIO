CDPVERSION = 4.0.0
DEPS += \

HEADERS += fileio.h \
           FileIOServer.h \
           gpio.h \
           fileioBuilder.h

SOURCES += \
           fileioserver.cpp \
           gpio.cpp \
           fileioBuilder.cpp

DISTFILES += \
    Models/*

include($$(CDPBASE)/qmakefeatures/cdplibrary.pri)
