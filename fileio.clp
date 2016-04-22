PROJECTNAME = fileio

include($$(CDPBASE)/qmakefeatures/cdplibrary.pri)

HEADERS += fileio.h \
           fileiobuilder.h \
           FileIOServer.h \
           gpio.h

SOURCES += fileiobuilder.cpp \
           fileioserver.cpp \
           gpio.cpp

OTHER_FILES += \
        fileio.xml \
        fileio.prf \
        models/*.xml

DISTFILES += \
    models/FileIOServer.xml \
    models/FileIO.GPIO.xml
