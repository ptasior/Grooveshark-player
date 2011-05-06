QT			+= core gui webkit network
TARGET		= Grooveshark
TEMPLATE	= app

SOURCES += main.cpp \
	cookiejar.cpp \
	grooveshark.cpp

HEADERS += grooveshark.h \
	cookiejar.h

RESOURCES += resources.qrc