QT          += core gui webkit network
TARGET       = Grooveshark
TEMPLATE     = app

SOURCES += cookiejar.cpp \
    main.cpp \
    Grooveshark.cpp

HEADERS += Grooveshark.h \
    cookiejar.h

RESOURCES += resources.qrc
