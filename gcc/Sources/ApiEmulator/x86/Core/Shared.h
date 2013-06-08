#ifndef SHARED_H
#define SHARED_H


#include <list>
#include <functional>

class Shared;

class RefID
{
public:
    typedef std::list <Shared *>::iterator ref_t;

    RefID() :
        valid(false) {
    }

    RefID(ref_t &r) :
        valid(true) {
        operator =(r);
    }


    RefID &operator =(ref_t & r) {
        ref = r;
        valid = true;
        return *this;
    }

    void erase(std::list <Shared *> &l) {
        if(valid) {
            l.erase(ref);
            valid = false;
        }
    }

    bool valid;
    ref_t ref;
};




class Shared
{
public:
    Shared();
    Shared(const Shared &);
    virtual ~Shared();

    void clear();
    bool isRefed() const {
        return m_refed;
    }

protected:
    virtual void atref(const Shared *) {

    }

    virtual void atderef() {

    }

    void ref(const Shared *parent );
    void deref();
    void unrefers();

    void setRefed(bool is = true) {
        m_refed = is;
    }

protected:
    const Shared *m_parent;
    mutable std::list <Shared *> m_refers;
    RefID ref_id;
    bool m_refed;
};

#endif // SHARED_H
