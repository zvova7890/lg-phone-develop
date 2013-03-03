


#include "FileViewWidgetEngine.h"
#include "FileViewWidget.h"




FileViewWidgetEngine::FileViewWidgetEngine(FileViewWidget *parent) :
    m_widgetParent(parent)
{

}



FileViewWidgetEngine::~FileViewWidgetEngine()
{

}


int FileViewWidgetEngine::fileSystemEntriesCount()
{
    return fileViewParent()->fsEntriesCount();
}
