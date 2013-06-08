#include "x86_mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    setenv("FONTS", "/usr/share/fonts/TTF/", 0);
    QApplication a(argc, argv);
    EmuMainWindow w;
    w.show();
    
    return a.exec();
}


extern "C" void ElfDestroy()
{

}
