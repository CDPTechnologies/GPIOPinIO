CDPVERSION = 4.1.0
TYPE = library

DEPS += \

HEADERS += GPIOPinIO.h \
           GPIOServer.h \
           GPIOPin.h \
           GPIOPinIOBuilder.h

SOURCES += \
           GPIOServer.cpp \
           GPIOPinIOBuilder.cpp

linux*:SOURCES += \
    Linux/GPIOPin.cpp

win*:SOURCES += \
    Win/GPIOPin.cpp

load(cdp)
