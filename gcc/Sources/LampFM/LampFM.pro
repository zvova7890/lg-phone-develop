

TARGET = fm.elf
TEMPLATE = app
CONFIG -= qt

INCLUDEPATH += actionlib

# уберём дефолтные флаги
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE -= -O2
# QMAKE_LFLAGS_APP -= -s

QMAKE_CXXFLAGS += -O2 -std=c++11  -U__STRICT_ANSI__ -D__STDC_VERSION__=200001
QMAKE_CFLAGS_RELEASE += -O2 -std=gnu99
QMAKE_LFLAGS += -Wl,-allow-multiple-definition

LIBS   += -lscrt -lgcc -lc -lpng -lz -lm -lgl -lft -lc++ -lsupc++

HEADERS += \
    signals/signal.h \
    actionlib/TimerWrap.h \
    actionlib/TimedTrack.h \
    actionlib/ScrollArea.h \
    actionlib/ActiveArea.h \
    Ui/UActiveArea.h \
    Ui/ActiveList.h \
    Ui/UButton.h \
    Ui/ListMenu.h \
    Ui/EventManager.h \
    Ui/ListMenuStyle.h \
    Sys/Timer.h \
    Sys/Thread.h \
    Graph/Brush.h \
    Rect.h \
    png_ops.h \
    XTouchFiled.h \
    ExtManager.h \
    TouchListViewWidget.h \
    EffectManager.h \
    ViewControl.h \
    ViewEngine.h \
    FileViewWidget.h \
    GlobalMenuButton.h \
    ResourceManager.h \
    main.h \
    FSEntryInfo.h \
    FileViewWidgetEngine.h \
    FileViewWidgetListEngine.h \
    FileViewWidgetAbstractItem.h \
    FileViewWidgetIconEngine.h \
    QuestionDialog.h \
    Notify.h \
    FSProtocol.h \
    LocalFSProtocol.h \
    ClipBoard.h \
    ProgressDialog.h \
    ThreadWorker.h \
    Graph/Image.h

SOURCES += \
    main.cpp \
    actionlib/TimerWrap.c \
    actionlib/TimedTrack.c \
    actionlib/ScrollArea.c \
    actionlib/ActiveArea.c \
    Ui/UActiveArea.cpp \
    Ui/ActiveList.cpp \
    Ui/UButton.cpp \
    Ui/ListMenu.cpp \
    Ui/EventManager.cpp \
    Ui/ListMenuStyle.cpp \
    Sys/Timer.cpp \
    Sys/Thread.cpp \
    Graph/Brush.cpp \
    ExtManager.cpp \
    png.c \
    FileViewWidget.cpp \
    EffectManager.cpp \
    GlobalMenuButton.cpp \
    ResourceManager.cpp \
    FileViewWidgetListEngine.cpp \
    FileViewWidgetEngine.cpp \
    FileViewWidgetIconEngine.cpp \
    QuestionDialog.cpp \
    Notify.cpp \
    FSProtocol.cpp \
    LocalFSProtocol.cpp \
    ClipBoard.cpp \
    ProgressDialog.cpp \
    ThreadWorker.cpp \
    FileViewWidget_fs.cpp \
    FileViewWidget_filecontext.cpp \
    Graph/Image.cpp
