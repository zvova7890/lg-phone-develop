#ifndef EXTMANAGER_H
#define EXTMANAGER_H

#include <string>
#include <map>
#include <vector>


class ExtManager
{
public:
    class ExtInfo
    {
    public:
        std::string ext;
        std::string action;
        std::string s_icon;
        std::string b_icon;

        ExtInfo & operator =(const ExtInfo &r) {
            ext = r.ext;
            action = r.action;
            s_icon = r.s_icon;
            b_icon = r.b_icon;
            return *this;
        }
    };

public:
    ExtManager(const std::string &dir);

    int loadConfig(const std::string &conf);
    int run(const std::string &path);

    const ExtInfo *extension(const std::string & ext);

private:


    std::map <std::string, std::vector<ExtInfo> > m_extMap;
    std::string m_dir;
};

#endif // EXTMANAGER_H
