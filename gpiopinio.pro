TYPE = library
PROJECTNAME = GPIOPinIO

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
