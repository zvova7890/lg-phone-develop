TARGET = libprochandler.so
TEMPLATE = app
CONFIG -= qt

INCLUDEPATH +=

# уберём дефолтные флаги
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE -= -O2
# QMAKE_LFLAGS_APP -= -s

QMAKE_CXXFLAGS += -fPIC -O3 -std=c++11  -U__STRICT_ANSI__ -D__STDC_VERSION__=200001
QMAKE_CFLAGS_RELEASE += -fPIC -O3 -std=gnu99


QMAKE_LFLAGS = -s -Wl,-marmelf,-zmax-page-size=1,-nostdlib -fPIC -nostartfiles -shared -Wl,-shared,-Bsymbolic,-Bsymbolic-function,-soname=libprochandler.so
LIBS   += -lscrt -lgcc -lc

SOURCES += \
    main.c \
    access.c \
    hook.S \
    manager.c

HEADERS += \
    access.h
