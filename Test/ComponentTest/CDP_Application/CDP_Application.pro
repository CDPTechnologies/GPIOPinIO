TARGET = ComponentTest
include($$(QMAKEFEATURES)/cdpapplication.pri)

CONFIG += cdpunit \
          gpiopinio

LIBS += ../TestLib/$$OBJECTS_DIR/libTestLib$${EXT}.a

HEADERS += Libraries.h
SOURCES += CDPMain.cpp


