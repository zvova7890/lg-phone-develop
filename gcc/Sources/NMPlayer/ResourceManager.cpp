#include "ResourceManager.h"



ResourceManager::ResourceManager(const std::string &my_dir) :
    m_myDir(my_dir)
{
    m_images.clear();
}


ResourceManager::~ResourceManager()
{
    for( std::pair<std::string, Image *> p : m_images)
    {
        if(p.second) {
            delete p.second;
        }
    }

    m_images.clear();
}


Image &ResourceManager::image(const std::string & name)
{
    Image *i = m_images[name];

    if(!i) {

        i = new Image((m_myDir+"imgs/"+name+".png").c_str());
        if(i) {
            if(!i->isEmpty())
                m_images[name] = i;
            else {
                delete i;
                i = 0;
            }
        }
    }

    if(!i) {
        return Image::null;
    }

    return *i;
}
