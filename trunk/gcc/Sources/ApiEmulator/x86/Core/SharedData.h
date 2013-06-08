#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#include "Shared.h"



class SharedData : public Shared
{
public:

    SharedData();
    SharedData(char *, int len);
    SharedData(const SharedData &);

    const char *constData() const {
        return m_data;
    }

    char *data() {
        deref();
        return m_data;
    }

protected:
    void atref(const Shared *);
    void atderef();

private:
    char *m_data;
    int m_len;
};

#endif // SHAREDDATA_H
