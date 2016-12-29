CDPVERSION = 4.1.0
TYPE = library

DEPS += \

HEADERS += GPIOPinIO.h \
           GPIOServer.h \
           GPIOPin.h \
           GPIOPinIOBuilder.h

SOURCES += \
           GPIOServer.cpp \
           GPIOPin.cpp \
           GPIOPinIOBuilder.cpp

load(cdp)
