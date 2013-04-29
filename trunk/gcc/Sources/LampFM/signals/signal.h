#ifndef SIGNAL_H
#define SIGNAL_H


#include <functional>
#include <list>
#include <assert.h>

namespace signal_slot {

    
    

template <typename... Arguments>
class signal_base
{
public:

    signal_base() {
        _caller = [](Arguments...) {};
    }

    signal_base(const std::function<void(Arguments...)> &f) {
        _caller = f;
    }


    template <class Object, typename Func, typename... PlaceHolders>
    signal_base(Object obj, Func func, PlaceHolders... place) {
        _caller = std::bind(func, obj, place...);
    }


    template <typename... Args>
    void trigger(Args... args) {
        _caller(args...);
    }

    void erase() {
        _caller = [](Arguments...) {};
    }

    signal_base & operator =(const signal_base<Arguments...> & s) {
        _caller = s._caller;
        return *this;
    }


private:
    std::function<void(Arguments...)> _caller;
};


template <typename... Arguments>
class signal
{

public:

    void connect(const std::function<void(Arguments...)> &f) {
        sig = f;
    }


    template <class Object, typename Func, typename... PlaceHolders>
    void connect(Object obj, Func func, PlaceHolders... place) {
        sig = std::function<void(Arguments...)>(std::bind(func, obj, place...));
    }


    void disconnect() {
        sig.erase();
    }

    template <typename... Args>
    void trigger(Args... args) {
        sig.trigger(args...);
    }



private:
    signal_base<Arguments...> sig;
};


template <typename... Arguments>
class multi_signal
{
    typedef std::list <signal_base<Arguments...> > _slots;

public:

    multi_signal() : blocked(false) {

    }

    typename std::list <signal_base<Arguments...> >::iterator _iterator;
    typedef typename std::list <signal_base<Arguments...> >::iterator slot;

    auto connect(const std::function<void(Arguments...)> &f) -> decltype(_iterator)
    {
        assert(blocked == false);
        list.push_back( f );
        return (--list.end());
    }


    template <class Object, typename Func, typename... PlaceHolders>
    auto connect(Object obj, Func func, PlaceHolders... place) -> decltype(_iterator)
    {
        list.push_back( std::function<void(Arguments...)>(std::bind(func, obj, place...)) );
        return (--list.end());
    }


    void disconnect(const multi_signal::slot & it) {
        if(blocked)
            need_disconnect.push_back(it);
        else
            list.erase(it);
    }

    template <typename... Args>
    void trigger(Args... args) {

        /* on triggering, calients can disconnecting signals, it`s may provide a carsh, when remove on iterating
         * so, we make another list of disconnecters, and after iterating, we disconnect it
        */
        blockDisconnecting();
        for(signal_base<Arguments...> & c : list)
            c.trigger(args...);

        unblockDisconnecting();
    }


    multi_signal & operator = (const multi_signal<Arguments...> & s) {
        list = s.list;
    }


    void clear() {
        list.clear();
        need_disconnect.clear();
    }

private:
    inline void blockDisconnecting() {
        blocked = true;
    }

    void unblockDisconnecting() {
        blocked = false;
        for(const slot &s : need_disconnect)
            list.erase(s);

        need_disconnect.clear();
    }

private:
    _slots list;
    bool blocked;
    std::list <slot> need_disconnect;
};


} // signals

#endif // SIGNAL_H
