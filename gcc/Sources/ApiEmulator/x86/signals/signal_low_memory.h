#ifndef SIGNAL_H
#define SIGNAL_H


#include <functional>
#include <list>


namespace signal_slot {


class simple_object
{
    void func();
};




class signal_templ_container
{
public:

    virtual ~signal_templ_container() {

    }

    virtual bool objected() {
        return false;
    }
};



template <typename Object, typename... Arguments>
class signal_objcall_container : public signal_templ_container
{
public:

    signal_objcall_container() {
        object = 0;
    }

    template <typename T>
    signal_objcall_container(Object *obj, T func) {
        object = obj;
        this->func = (void(simple_object::*)(Arguments...))func;
    }

    template <typename... Args>
    void trigger(Args... args) {

        if(object) {
            //auto call = (void (simple_object::*)(Arguments...))func;
            simple_object *o = (simple_object *)object;
            (o->*func)(args...);
        }
    }

    bool operator==(const signal_objcall_container<simple_object, Arguments...> &c) {
        if(c.object == object && c.func == func)
                return true;

        return false;
    }

    bool objected() {
        return true;
    }

private:
    Object *object;
    void (simple_object::*func)(Arguments...);
};



template <typename... Arguments>
class signal_call_container : public signal_templ_container
{
public:
    signal_call_container() {

    }

    template<typename T>
    signal_call_container(T func) {
        function = func;
    }

    template <typename... Args>
    void trigger(Args... args) {
        function(args...);
    }

    bool operator==(const signal_call_container<Arguments...> &c) {
        if(c.function == function)
            return true;

        return false;
    }

    bool objected() {
        return false;
    }

private:
    std::function<void(Arguments...)> function;
};



template <class ObjectType, typename... Arguments>
class signal_container
{
public:

    signal_container(const signal_container<ObjectType, Arguments...> &c) :
        container(c.container),
        refed(false)
    {

    }

    signal_container() :
        container(0),
        refed(false)
    {
    }

    ~signal_container() {
        erase();
    }

    template<class Object, typename Func>
    signal_container(Object obj, Func func, bool ref = false) :
        refed(ref)
    {
        auto p = new signal_objcall_container<ObjectType, Arguments...>(obj, func);
        container = (signal_templ_container*) (p);
    }


    template<typename Func>
    signal_container(Func func, bool ref = false) :
        refed(ref)
    {
        auto p = new signal_call_container<Arguments...>(func);
        container = (signal_templ_container*) (p);
    }

    template <typename... Args>
    void trigger(Args... args) {
        if(container) {
            if(container->objected()) {
                auto p = (signal_objcall_container<simple_object*, Arguments...>*)container;
                p->trigger(args...);
            } else {
                auto p = (signal_call_container<Arguments...>*)container;
                p->trigger(args...);
            }
        }
    }

    /*bool operator==(const signal_container<simple_object, FuncDecl> &c) {

        return false;
    }*/

    signal_container &operator =(const signal_container<ObjectType, Arguments...> & c) {
        erase();
        container = c.container;
        return *this;
    }

    void erase() {
        if(container && !refed)
            delete container;
        container = 0;
    }

private:
    signal_templ_container *container;
    bool refed;
};



template <typename... Arguments>
class signal
{
public:

    template <typename t>
    void connect( t func )
    {
        _slot = signal_container<Arguments...>(func, true);
    }

    template <class ObjType, class Obj, typename Func>
    void connect(Obj obj, Func func )
    {
        _slot = signal_container<Arguments...>(obj, func, true);
    }

    void disconnect()
    {
        _slot.erase();
    }

    template <typename... Args>
    void trigger(Args... args) {
        _slot.trigger(args...);
    }

    signal_container<simple_object, Arguments...> _slot;
};



template <typename... Arguments>
class multi_signal
{
public:


    typedef signal_container<simple_object, Arguments...> template_container;
    typename std::list<signal_container<simple_object, Arguments...> >::iterator iterator;

    typedef decltype(iterator) slot;

    void clear() {
        _slots.clear();
    }


    template <typename t>
    auto connect( t func ) -> decltype(iterator)
    {
        _slots.push_back( template_container(func, true) );
        return (--_slots.end());
    }

    template <class Object, typename Func>
    auto connect(Object *obj, Func func ) -> decltype(iterator)
    {
        _slots.push_back( signal_container<Object, Arguments...>(obj, func, true) );
        return (--_slots.end());
    }


    template <class Iterator>
    void disconnect(Iterator it) {
        _slots.erase(it);
    }

    template <typename... Args>
    void trigger(Args... args) {

        for(template_container &slot : _slots )
            slot.trigger(args...);
    }

    std::list<signal_container<simple_object, Arguments...> > _slots;
};


} // signal_slot


#endif // SIGNAL_H
