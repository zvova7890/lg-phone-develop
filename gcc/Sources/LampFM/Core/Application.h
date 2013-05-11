#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>


class Application
{
public:

    enum {
        KEY_UP = 1,
        KEY_DOWN
    };

public:
    Application();
    virtual ~Application();

    void construct(int argc, char *argv[], const std::string &name = "");
    virtual void constructEvent(int argc, char *argv[]);
    virtual bool eventFilter(unsigned long, unsigned long, unsigned long);
    virtual void paintEvent();
    virtual void initEvent();
    virtual void releaseEvent();
    virtual void suspendEvent();
    virtual void resumeEvent();
    virtual void motionSensorEvent(int orientation);
    virtual void keyEvent(int type, int key);
    virtual void touchEvent(int action, int x, int y);

    std::string applicationDir() const;
    std::string applicationName() const;

protected:
    static int event_listener(unsigned long event_id, unsigned long wparam, unsigned long lparam);

protected:
    int m_applicationId;
    std::string m_appDir;
    std::string m_appName;
};

#endif // APPLICATION_H
