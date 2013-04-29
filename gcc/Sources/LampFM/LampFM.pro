

TARGET = fm.elf
TEMPLATE = app
CONFIG -= qt

INCLUDEPATH += Core Widget

# уберём дефолтные флаги
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE -= -O2
# QMAKE_LFLAGS_APP -= -s

QMAKE_CXXFLAGS += -O3 -std=c++11  -U__STRICT_ANSI__ -D__STDC_VERSION__=200001
QMAKE_CFLAGS_RELEASE += -O3 -std=gnu99
QMAKE_LFLAGS += -Wl,-allow-multiple-definition

LIBS   += -lscrt -lgcc -lc -lpng -lz -lm -lmips -lgl -lft -lc++ -lsupc++

HEADERS += \
    signals/signal.h \
    Core/Timer.h \
    Core/Thread.h \
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
    Graph/Image.h \
    Ui/UButtonStyle.h \
    HTextScroller.h \
    EInformationDialog.h \
    Widget/Widget.h \
    Widget/VScrollArea.h \
    Widget/EventManager.h \
    Core/TimerCounter.h \
    Widget/ButtonStyle.h \
    Widget/Button.h \
    Widget/ListMenuStyle.h \
    Widget/ListMenu.h \
    Keyboard/KeyboardEN.h \
    Keyboard/Keyboard.h \
    AsyncProgressivelyWork.h \
    String.h \
    RenameDialog.h

SOURCES += \
    main.cpp \
    Core/Timer.cpp \
    Core/Thread.cpp \
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
    Graph/Image.cpp \
    HTextScroller.cpp \
    EInformationDialog.cpp \
    Widget/Widget.cpp \
    Widget/VScrollArea.cpp \
    Widget/EventManager.cpp \
    Core/TimerCounter.cpp \
    Widget/ButtonStyle.cpp \
    Widget/Button.cpp \
    Widget/ListMenuStyle.cpp \
    Widget/ListMenu.cpp \
    Keyboard/KeyboardEN.cpp \
    Keyboard/Keyboard.cpp \
    AsyncProgressivelyWork.cpp \
    String.cpp \
    RenameDialog.cpp
