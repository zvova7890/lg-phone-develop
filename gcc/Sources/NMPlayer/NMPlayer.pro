TARGET = NMPlayer.elf
TEMPLATE = app
CONFIG -= qt

INCLUDEPATH += actionlib

# уберём дефолтные флаги
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE -= -O2
#QMAKE_LFLAGS_APP -= -s

QMAKE_CXXFLAGS += -O2 -std=c++11  -U__STRICT_ANSI__ -D__STDC_VERSION__=200001
QMAKE_CFLAGS_RELEASE += -O2 -std=gnu99


LIBS   += -lcrt -lscrt -lgcc -lc -lpng -lz -lm -lgl -lft -lmips -lc++ -lsigc++ -lsupc++

SOURCES += \
    main.cpp \
    access.c \
    hook.S \
    logger.c \
    Core/TimerCounter.cpp \
    Core/Timer.cpp \
    Core/Thread.cpp \
    Graph/Image.cpp \
    Graph/Brush.cpp \
    Widget/Widget.cpp \
    Widget/ScrollList.cpp \
    Widget/ListMenuStyle.cpp \
    Widget/ListMenu.cpp \
    Widget/Layout.cpp \
    Widget/EventManager.cpp \
    Widget/ButtonStyle.cpp \
    Widget/Button.cpp \
    Widget/HTextScroller.cpp \
    Widget/Separator.cpp \
    MediaPlayer.cpp \
    png.c \
    Widget/TabBox.cpp \
    ResourceManager.cpp \
    Core/Application.cpp \
    Positioner.cpp \
    Widget/MainWindow.cpp \
    MyMainWindow.cpp \
    Core/SharedData.cpp \
    Core/Shared.cpp

HEADERS += \
    access.h \
    MSOEM_Player.h \
    Core/TimerCounter.h \
    Core/Timer.h \
    Core/Thread.h \
    Core/Rect.h \
    Core/Point.h \
    Core/include.h \
    Graph/Rect.h \
    Graph/Image.h \
    Graph/Brush.h \
    signals/signal.h \
    Widget/Widget.h \
    Widget/ScrollList.h \
    Widget/ListMenuStyle.h \
    Widget/ListMenu.h \
    Widget/Layout.h \
    Widget/EventManager.h \
    Widget/ButtonStyle.h \
    Widget/Button.h \
    Widget/HTextScroller.h \
    Widget/Separator.h \
    MediaPlayer.h \
    Widget/TabBox.h \
    ResourceManager.h \
    Core/Application.h \
    Positioner.h \
    Widget/MainWindow.h \
    MyMainWindow.h \
    Core/SharedData.h \
    Core/Shared.h
