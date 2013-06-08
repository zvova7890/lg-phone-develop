TARGET = MainMenu.elf
TEMPLATE = app
CONFIG -= qt

INCLUDEPATH +=

# уберём дефолтные флаги
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE -= -O2
#QMAKE_LFLAGS_APP -= -s

QMAKE_CXXFLAGS += -O2 -flto -std=c++11  -U__STRICT_ANSI__ -D__STDC_VERSION__=200001
QMAKE_CFLAGS_RELEASE += -O2 -std=gnu99
QMAKE_LFLAGS +=

LIBS   += -lcrt -lscrt -lgcc -lc -lpng -lz -lm -lmips -lconfig -lgl -lft -lprochandler -lc++ -lsigc++ -lsupc++

SOURCES += \
    main.cpp \
    Core/TimerCounter.cpp \
    Core/Timer.cpp \
    Core/Thread.cpp \
    Core/Application.cpp \
    Graph/Image.cpp \
    Graph/Brush.cpp \
    Keyboard/KeyboardRU.cpp \
    Keyboard/KeyboardEnum.cpp \
    Keyboard/KeyboardEN.cpp \
    Keyboard/Keyboard.cpp \
    Widget/Widget.cpp \
    Widget/TabBox.cpp \
    Widget/Separator.cpp \
    Widget/MainWindow.cpp \
    Widget/ListMenuStyle.cpp \
    Widget/ListMenu.cpp \
    Widget/Layout.cpp \
    Widget/HTextScroller.cpp \
    Widget/EventManager.cpp \
    Widget/ButtonStyle.cpp \
    Widget/Button.cpp \
    Core/ResourceManager.cpp \
    png.c \
    actionhandler.cpp \
    EffectManager.cpp \
    Widget/ScrollList.cpp \
    Core/Shared.cpp \
    Core/SharedData.cpp \
    tab.cpp \
    bar.cpp \
    cmd.cpp \
    MenuWidget.cpp \
    PhoneSettings.cpp \
    DisplaySettings.cpp \
    Contacts.cpp \
    Applications.cpp

HEADERS += \
    MSOEM_Player.h \
    Core/TimerCounter.h \
    Core/Timer.h \
    Core/Thread.h \
    Core/Rect.h \
    Core/Point.h \
    Core/compatible.h \
    Core/Application.h \
    Graph/Rect.h \
    Graph/Image.h \
    Graph/Brush.h \
    Keyboard/KeyboardRU.h \
    Keyboard/KeyboardEnum.h \
    Keyboard/KeyboardEN.h \
    Keyboard/Keyboard.h \
    signals/signal.h \
    Widget/Widget.h \
    Widget/TabBox.h \
    Widget/Separator.h \
    Widget/MainWindow.h \
    Widget/ListMenuStyle.h \
    Widget/ListMenu.h \
    Widget/Layout.h \
    Widget/HTextScroller.h \
    Widget/EventManager.h \
    Widget/ButtonStyle.h \
    Widget/Button.h \
    Core/ResourceManager.h \
    main.h \
    actionhandler.h \
    EffectManager.h \
    Widget/ScrollList.h \
    Core/Shared.h \
    Core/SharedData.h \
    tab.h \
    png_ops.h \
    bar.h \
    MenuWidget.h \
    PhoneSettings.h \
    DisplaySettings.h \
    Contacts.h \
    Applications.h
