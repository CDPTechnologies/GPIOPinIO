PROJECTNAME = fileio

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
        models/*.xml

DISTFILES += \
    models/FileIOServer.xml \
    models/FileIO.GPIO.xml
