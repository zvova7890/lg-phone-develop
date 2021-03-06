#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <Graph/Image.h>
#include <string>
#include <map>


class ResourceManager
{
public:
    ResourceManager(const std::string & my_dir);
    ~ResourceManager();

    Image & image(const std::string & name, const std::string &subfolder = "", bool full_way = false);



private:

    std::map<std::string, Image *> m_images;
    const std::string & m_myDir;
};

#endif // RESOURCEMANAGER_H
