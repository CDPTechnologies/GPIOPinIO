PROJECTNAME = fileio
CDPVERSION = 4.0.0

include($$(CDPBASE)/qmakefeatures/cdplibrary.pri)

HEADERS += fileio.h \
           FileIOServer.h \
           gpio.h \
           fileioBuilder.h

SOURCES += \
           fileioserver.cpp \
           gpio.cpp \
           fileioBuilder.cpp

OTHER_FILES += \
        fileio.xml \
        fileio.prf \
        Models/*.xml

DISTFILES += \
    Models/FileIOServer.xml \
    Models/FileIO.GPIO.xml
