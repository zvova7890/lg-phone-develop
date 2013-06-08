#include "actionhandler.h"




ActionHandler::ActionHandler()
{

}


void ActionHandler::action(const std::string &act)
{

    std::string a, name;
    int at = act.find_first_of("://");
    if(at > -1) {
        a = act.substr(at+3);
        name = act.substr(0, at);
    }

    auto p = m_bindMap.find(name);
    if(p != m_bindMap.end()) {
        if(!a.empty())
            p->second(this, a);
    }
}


void ActionHandler::registerAction(const std::string &name, std::function<void (const std::string &)> f)
{
    m_menuActions[name] = f;
}


void ActionHandler::registerActionType(const std::string &name, std::function<void(ActionHandler *, const std::string &)> f)
{
    m_bindMap[name] = f;
}

