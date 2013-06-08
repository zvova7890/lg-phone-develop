TARGET = MessageSniffer.elf
TEMPLATE = app
CONFIG -= qt

INCLUDEPATH +=

# уберём дефолтные флаги
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_LFLAGS_APP -= -s

QMAKE_CXXFLAGS += -O3 -std=c++11  -U__STRICT_ANSI__ -D__STDC_VERSION__=200001
QMAKE_CFLAGS_RELEASE += -O3 -std=gnu99


LIBS   += -lcrt -lscrt -lgcc -lc -lpng -lz -lm -lmips -lgl -lft -lprochandler

SOURCES += \
    main.c

HEADERS += 
   
