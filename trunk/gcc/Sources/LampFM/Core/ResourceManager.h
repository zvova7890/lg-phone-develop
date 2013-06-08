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


    void setImagesDir(const std::string &d);
    
    
private:

    std::map<std::string, Image *> m_images;
    std::string m_myDir;
    std::string m_imagesDir;
};

#endif // RESOURCEMANAGER_H
