


#include "FileViewWidgetEngine.h"
#include "FileViewWidget.h"




FileViewWidgetEngine::FileViewWidgetEngine(FileViewWidget *parent) :
    _fparent(parent)
{

}



FileViewWidgetEngine::~FileViewWidgetEngine()
{

}


int FileViewWidgetEngine::fileSystemEntriesCount()
{
    return fileViewParent()->fsEntriesCount();
}
