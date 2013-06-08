#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H


#include <string>
#include <functional>
#include <map>



class ActionHandler
{
public:
    ActionHandler();

    void action(const std::string &action);

    void registerActionType(const std::string &name, std::function<void(ActionHandler *, const std::string &)> f);
    void registerAction(const std::string &name, std::function<void(const std::string &)> f);




    std::map< std::string, std::function<void(ActionHandler *, const std::string &)> > m_bindMap;
    std::map< std::string, std::function<void(const std::string &)> > m_menuActions;
};

#endif // ACTIONHANDLER_H
