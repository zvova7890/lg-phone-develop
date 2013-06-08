#include <string.h>
#include "SharedData.h"



SharedData::SharedData() :
    m_data(0)
{
}


SharedData::SharedData(const SharedData &r) :
    Shared(r)
{
}




void SharedData::atref(const Shared *ref)
{
    SharedData *d = (SharedData *)ref;
    m_data = d->m_data;
    m_len = d->m_len;
}


void SharedData::atderef()
{
    char *d = m_data;
    m_data = new char[m_len];
    memcpy(m_data, d, m_len);
}


