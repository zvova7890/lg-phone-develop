#-------------------------------------------------
#
# Project created by QtCreator 2012-12-26T15:34:09
#
#-------------------------------------------------

QT       += core gui
INCLUDEPATH += /usr/include/libpng12/ /usr/include/freetype2 ./actionlib ./Widget ./Core ./gl lg-spec


QMAKE_LFLAGS += -m32 -L/usr/lib32
QMAKE_CFLAGS += -m32 -D__NO_ASM_OPTIMIZE -D__USE_XOPEN2K -D__USE_BSD -D__PC_BUILD__ -std=c99
#QMAKE_CFLAGS_RELEASE += -O3 -march=native -mtune=native -std=c99
QMAKE_CXXFLAGS += -m32 -std=c++11 -D__USE_XOPEN2K -D__USE_BSD -D__PC_BUILD__

LIBS += -lfreetype -ldl -lpng12 -lpthread -lconfig

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gl
TEMPLATE = app


SOURCES +=\
    gl/glcontext.c \
    gl/glline.c \
    gl/glcolor.c \
    gl/glrectangle.c \
    gl/glalphablend.c \
    gl/glcircle.c \
    gl/glarc.c \
    gl/glpolygon.c \
    gl/tables.c \
    gl/glellipse.c \
    gl/gltriangle.c \
    gl/glbitmap.c \
    gl/cfreetype.c \
    gl/fontbase.c \
    gl/freetype.c \
    gl/glstring.c \
    gl/clip.c \
    gl/queuelist.c \
    gl/glstringengine.c \
    gl/glfill.c \
    gl/glgradient.c \
    gl/glroundedrect.c \
    Widget/Widget.cpp \
    Core/Timer.cpp \
    Widget/EventManager.cpp \
    Core/TimerCounter.cpp \
    png.c \
    Core/Thread.cpp \
    Graph/Image.cpp \
    Graph/Brush.cpp \
    Widget/ListMenuStyle.cpp \
    Widget/ListMenu.cpp \
    lg-spec/impl/api/pxe_uni.c \
    lg-spec/impl/api/pxe_fs.c \
    lg-spec/impl/pxe_grphics.c \
    lg-spec/impl/loader.c \
    lg-spec/impl/fs.c \
    lg-spec/impl/nucleus.c \
    Keyboard/Keyboard.cpp \
    Widget/ButtonStyle.cpp \
    Widget/Button.cpp \
    Keyboard/KeyboardEN.cpp \
    Widget/Layout.cpp \
    Widget/ScrollList.cpp \
    Keyboard/KeyboardRU.cpp \
    Keyboard/KeyboardEnum.cpp \
    emu/x86_mainwindow.cpp \
    emu/x86_main.cpp \
    main.cpp \
    Widget/TabBox.cpp \
    Widget/Separator.cpp \
    Widget/MainWindow.cpp \
    Widget/HTextScroller.cpp \
    Core/ResourceManager.cpp \
    EffectManager.cpp \
    actionhandler.cpp \
    emu/App.c \
    emu/lgos_timer.c \
    emu/taskapi.c \
    emu/Indicator.cpp \
    Core/Shared.cpp \
    Core/SharedData.cpp \
    tab.cpp \
    bar.cpp \
    MenuWidget.cpp \
    cmd.cpp \
    PhoneSettings.cpp \
    DisplaySettings.cpp \
    Contacts.cpp \
    Applications.cpp \
    emu/t_cmd.c \
    text_render_test.cpp \
    gl/ftmetrics.c

HEADERS  += emu/x86_mainwindow.h \
    gl/gl.h \
    gl/freetype_engine.h \
    gl/queuelist.h \
    signals/signal.h \
    Widget/Widget.h \
    Core/Timer.h \
    Widget/EventManager.h \
    Core/Rect.h \
    Core/Point.h \
    Core/TimerCounter.h \
    Core/Thread.h \
    Core/compatible.h \
    Graph/Rect.h \
    Graph/Image.h \
    Graph/Brush.h \
    Widget/ListMenuStyle.h \
    Widget/ListMenu.h \
    lg-spec/Api/ApiLinkLib/UniLib.h \
    lg-spec/Api/ApiLinkLib/Types.h \
    lg-spec/Api/ApiLinkLib/FsLib.h \
    lg-spec/Api/ApiLinkLib/ApiLink.h \
    lg-spec/fs.h \
    Widget/TabBox.h \
    Widget/Separator.h \
    Widget/ScrollList.h \
    Widget/MainWindow.h \
    Widget/Layout.h \
    Widget/HTextScroller.h \
    Widget/ButtonStyle.h \
    Widget/Button.h \
    Core/ResourceManager.h \
    main.h \
    png_ops.h \
    EffectManager.h \
    actionhandler.h \
    Core/Shared.h \
    Core/SharedData.h \
    tab.h \
    bar.h \
    Core/safeforeach.h \
    cmd.h \
    MenuWidget.h \
    PhoneSettings.h \
    DisplaySettings.h \
    Contacts.h \
    Applications.h


OTHER_FILES +=

FORMS += \
    emu/mainwindow.ui
