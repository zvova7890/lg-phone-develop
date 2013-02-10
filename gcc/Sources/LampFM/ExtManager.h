#ifndef EXTMANAGER_H
#define EXTMANAGER_H

#include <string>
#include <map>
#include <vector>


class ExtManager
{
public:
    ExtManager(const std::string &dir);

    int loadConfig(const std::string &conf);
    int run(const std::string &path);

private:

    struct ExtInfo
    {
        std::string ext;
        std::string action;
        std::string s_icon;
        std::string b_icon;
    };

    std::map <std::string, std::vector<ExtInfo> > _ext_map;
    const std::string &_dir;
};

#endif // EXTMANAGER_H
