#include "Shared.h"


Shared::Shared() :
    m_parent(0),
    m_refed(false)
{

}


Shared::Shared(const Shared &r) :
    m_parent(0),
    m_refed(false)
{
    ref(&r);
}


Shared::~Shared()
{
    unrefers();
    ref_id.erase(m_parent->m_refers);
}



void Shared::clear()
{
    unrefers();
    if(m_parent && ref_id.valid) {
        ref_id.erase(m_parent->m_refers);
    }

    m_refed = false;
}


void Shared::ref(const Shared *parent)
{
    m_parent = parent;
    m_parent->m_refers.push_back(this);
    ref_id = (--m_parent->m_refers.end());
    m_refed = true;

    atref(parent);
}


void Shared::deref()
{
    unrefers();

    if(m_parent && (ref_id.valid || m_refed)) {
        ref_id.erase(m_parent->m_refers);
        atderef();
    }

    m_refed = false;
}


void Shared::unrefers()
{
    // TODO make reparent

    int sz = m_refers.size();

    for(auto p = m_refers.begin(); p != m_refers.end(); ) {
        auto c = p++;
        (*c)->deref();
    }

    m_refers.clear();
}
