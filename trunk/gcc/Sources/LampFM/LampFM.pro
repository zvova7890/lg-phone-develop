

TARGET = fm.elf
TEMPLATE = app
CONFIG -= qt

INCLUDEPATH += actionlib

# уберём дефолтные флаги
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE -= -O2
#QMAKE_LFLAGS_APP -= -s

QMAKE_CXXFLAGS += -O3 -std=c++11  -U__STRICT_ANSI__ -D__STDC_VERSION__=200001
QMAKE_CFLAGS_RELEASE += -O3 -std=gnu99
QMAKE_LFLAGS +=

LIBS   += -lscrt -lgcc -lc -lpng -lz -lm -lgl -lft -lc++ -lsigc++ -lsupc++

HEADERS += \
    Rect.h \
    png_ops.h \
    actionlib/TimerWrap.h \
    actionlib/TimedTrack.h \
    actionlib/ScrollArea.h \
    XTouchFiled.h \
    ExtManager.h \
    TouchListViewWidget.h \
    EffectManager.h \
    ViewControl.h \
    actionlib/ActiveArea.h \
    UActiveArea.h \
    ViewEngine.h \
    ActiveList.h \
    UButton.h \
    FileViewWidget.h \
    GlobalMenuButton.h \
    ResourceManager.h \
    main.h \
    GlobalMenu.h \
    ListMenu.h \
    FSEntryMenu.h \
    EventManager.h \
    FSEntryInfo.h \
    FileViewWidgetEngine.h \
    FileViewWidgetListEngine.h \
    FileViewWidgetAbstractItem.h \
    FileViewWidgetIconEngine.h

SOURCES += \
    main.cpp \
    actionlib/TimerWrap.c \
    actionlib/TimedTrack.c \
    actionlib/ScrollArea.c \
    ExtManager.cpp \
    png.c \
    actionlib/ActiveArea.c \
    UActiveArea.cpp \
    ActiveList.cpp \
    UButton.cpp \
    FileViewWidget.cpp \
    EffectManager.cpp \
    GlobalMenuButton.cpp \
    ResourceManager.cpp \
    GlobalMenu.cpp \
    ListMenu.cpp \
    FSEntryMenu.cpp \
    EventManager.cpp \
    FileViewWidgetListEngine.cpp \
    FileViewWidgetEngine.cpp \
    FileViewWidgetIconEngine.cpp