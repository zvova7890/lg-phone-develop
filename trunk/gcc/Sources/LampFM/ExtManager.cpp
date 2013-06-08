#include <Api/ApiLinkLib/ApiLink.h>
#include "ExtManager.h"
#include <stdio.h>
#include <loader.h>

#define printf(x, ...)


ExtManager::ExtManager(const std::string &dir) :
    m_dir(dir)
{
    loadConfig(m_dir+"conf/extension.cfg");
}


int ExtManager::run(const std::string &path)
{
    std::string s = path;
    auto pos = s.find_last_of('.');
    if(pos == std::string::npos)
        return -1;


    s = s.assign(s.begin()+pos+1, s.end());

    //printf("Runable? '%s'\n", s.c_str());

    if(s == "elf") {
        execelf(path.c_str(), 0, 0, 0, 0);

    } else if(s == "pxo") {
        U_CHAR lol[256];
	UniLib_UTF8ToUCS2((char*)path.c_str(), lol);
	
	

        App_RunEx(lol, 0, FOREGROUND_PRIORITY, TRUE);

    } else {

        const std::vector<ExtInfo> & v = m_extMap[s];

        for(const ExtInfo &extinfo : v)
        {
            printf( " -> RUN %s \naction: %s\nsmall_icon: %s\nbig_icon: %s\n",
                   extinfo.ext.c_str(), extinfo.action.c_str(), extinfo.s_icon.c_str(), extinfo.b_icon.c_str());

            const char *argv[2] = {extinfo.action.c_str(), path.c_str()};
            execelf(extinfo.action.c_str(), 2, (char**)argv, 0, 0);
        }
    }


    return 0;
}



const ExtManager::ExtInfo *ExtManager::extension(const std::string &ext)
{
    if(ext.empty())
        return 0;

    auto a = m_extMap.find(ext);

    if(a != m_extMap.end()) {

        const std::vector<ExtInfo> &v = (*a).second;

        if(v.empty())
            return 0;

        return &(v.at(0));
    }

    return 0;
}


#undef isspace
#define isspace(c) ((c >= 0x09 && c <= 0x0D) || c == 0x20 )



#define is_ends(s) (*s == 0x0A || *s == 0x0D)

#define skeep_spaces(s)         \
    while(isspace(*s) && *s) {  \
        if(is_ends(s)) {        \
            skeep_ends(s);      \
            continue;           \
        }                       \
        ++s;                    \
    }

#define skeep_spaces_and_comments(s)    \
    while((isspace(*s) || *s == '#') && *s) {   \
        skeep_spaces(s);                \
        if(*s == '#')                   \
            skeep_coment(s);            \
        skeep_spaces(s);                \
    }

#define goto_space(s) \
    while(!isspace(*s) && *s) ++s;

#define goto_space_or_char(s, c) \
    while((!isspace(*s) && *s != c) && *s) ++s;

#define goto_end(s) \
    while(*s != '\r' && *s != '\n' && *s) ++s;

#define skeep_ends(s) \
    while(*s) { \
        if(*s != '\r' && *s != '\n')        \
            break;                          \
                                            \
        if(*s == '\r' && *(s+1) == '\n') {  \
            s += 2;                         \
            ++line;                         \
        }                                   \
                                            \
        if(*s == '\n')                      \
            ++line;                         \
                                            \
        ++s;                                \
    }

#define skeep_coment(s) \
    goto_end(s) \
    skeep_ends(s)


int ExtManager::loadConfig(const std::string &conf)
{
    FILE *fp = fopen(conf.c_str(), "r");
    if(!fp) {
        printf("warning: can`t open extension config '%s'\n", conf.c_str());
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    int sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buf = new char[sz+2];
    fread(buf, sz, 1, fp);
    buf[sz] = 0;
    buf[sz+1] = 0;

    fclose(fp);

    std::string ext, action, attr;

    char *s = buf;
    int line = 1;
    char *word = 0;

    while(*s)
    {
        //printf("\n ======= \n%s\n", s);
        skeep_spaces_and_comments(s);
        if(!*s)
            break;

        if(*s != '[') {
            printf("LampFM: config: error[%d]: Expected a '[', but got a '%c'\n", line, *s);
            break;
        }
        ++s;

        skeep_spaces_and_comments(s);
        word = s;
        goto_space_or_char(s, ']');

        ext.assign(word, 0, s-word);

        skeep_spaces_and_comments(s);
        if(*s != ']') {
            printf("LampFM: config: error[%d]: Expected a ']', but got a '%c'\n", line, *s);
            break;
        }

        goto_end(s);
        skeep_ends(s);
        skeep_spaces_and_comments(s);


        ExtInfo extinfo;
        extinfo.ext = ext;

        while(*s) {
            action.clear();
            attr.clear();
            word = s;

            //printf("word: %s\n", word);

            goto_space_or_char(s, '=');
            if(!*s)
                break;

            //char trololo
            attr.assign(word, 0, s-word);
            skeep_spaces_and_comments(s);

            printf("attr: %s\n", attr.c_str());

            if(*s != '=') {
                printf("LampFM: config: error[%d]: Expected a '=', but got a '%c'\n", line, *s);
                break;
            }
            ++s;

            skeep_spaces_and_comments(s);
            if(*s != '"') {
                printf("LampFM: config: error[%d]: Expected a '\"', but got a '%c'\n", line, *s);
                break;
            }
            ++s;

            word = s;

            while(*s != '\"' && *s) ++s;
            if(*s != '"' || !*s) {
                printf("LampFM: config: error[%d]: Unhandled character or file EOF\n", line);
                break;
            }

            action.assign(word, 0, s-word);
            ++s;

            printf("action: %s\n", action.c_str());

            if(attr == "action") {
                printf("LOOOOOOOOOOOOOOOOL\n");
                extinfo.action = action;
            } else if(attr == "small_icon") {
                extinfo.s_icon = action;
            } else if(attr == "big_icon") {
                extinfo.b_icon = action;
            } else {
                printf("LampFM: config: warning[%d]: unknow attribute '%s'\n", line, attr.c_str());
            }

            printf("extinfo.action: %s - %s\n", extinfo.action.c_str(), action.c_str());

            goto_end(s);
            skeep_ends(s);
            skeep_spaces_and_comments(s);

            if(*s == '[' || !*s)
                break;
        }

        m_extMap[ext].push_back(extinfo);
        printf(" ====== %s ======\naction: %s\nsmall_icon: %s\nbig_icon: %s\n",
               ext.c_str(), extinfo.action.c_str(), extinfo.s_icon.c_str(), extinfo.b_icon.c_str());

    }

    delete buf;

    return 0;
}

