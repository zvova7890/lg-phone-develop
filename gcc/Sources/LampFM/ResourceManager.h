#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "png_ops.h"
#include <string>
#include <map>


class ResourceManager
{
public:
    ResourceManager(const std::string & my_dir);
    ~ResourceManager();

    image_t & image(const std::string & name);



private:

    image_t _null_image_resource;
    std::map<std::string, image_t *> _images;
    const std::string & _my_dir;
};

#endif // RESOURCEMANAGER_H
