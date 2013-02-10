#include "ResourceManager.h"



ResourceManager::ResourceManager(const std::string &my_dir) :
    _my_dir(my_dir)
{
    memset(&_null_image_resource, 0, sizeof(_null_image_resource));
    _images.clear();
}


ResourceManager::~ResourceManager()
{
    for( std::pair<std::string, image_t *> p : _images)
    {
        if(p.second) {
            if(p.second->bitmap)
                delete (char *)p.second->bitmap;
            delete p.second;
        }
    }

    _images.clear();
}


image_t & ResourceManager::image(const std::string & name)
{
    image_t *i = _images[name];

    if(!i) {

        i = load_png((_my_dir+"images/"+name+".png").c_str(), 0);
        if(i) {
            _images[name] = i;
        }
    }

    if(!i) {
        return _null_image_resource;
    }

    return *i;
}
