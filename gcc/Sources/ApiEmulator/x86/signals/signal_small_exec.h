#ifndef SIGNAL_H
#define SIGNAL_H


#include <functional>
#include <list>


namespace signal_slot {


class simple_object
{
    void func();
};



template <class Object, typename FuncDecl>
class signal_container
{
public:

    signal_container() {
        object = 0;
        obj_function = 0;
        function = 0;
    }

    template<typename T>
    signal_container(Object obj, T func) {
        object = obj;
        obj_function = (decltype(obj_function))func;
    }


    template<typename T>
    signal_container(T func) {
        object = 0;
        function = func;
    }

    template <typename... Args>
    void trigger(Args... args) {

        if(object) {
            auto call = (void (simple_object::*)(Args...))obj_function;
            simple_object *o = (simple_object *)object;
            (o->*call)(args...);

        } else {
            function(args...);
        }
    }

    bool operator==(const signal_container<simple_object, FuncDecl> &c) {
        if(c.object) {
            if(c.object == object && c.obj_function == obj_function)
                return true;
        } else {
            if(c.function == function)
                return true;
        }

        return false;
    }

private:
    Object object;
    void (simple_object::*obj_function)();
    std::function<FuncDecl> function;
    //void (*function)();
};



template <typename FuncDecl>
class signal
{
public:

    signal() :
        _slot(0) {

    }

    ~signal() {
        if(_slot)
            delete _slot;
    }

    template <typename t>
    void connect( t func )
    {
        if(_slot)
            delete _slot;

        _slot = new signal_container<simple_object*, FuncDecl>(func);
    }

    template <class ObjType, class Obj, typename Func>
    void connect(Obj obj, Func func )
    {
        if(_slot)
            delete _slot;

        _slot = (signal_container<simple_object*, FuncDecl> *)new signal_container<ObjType, FuncDecl>(obj, func);
    }

    void disconnect()
    {
        if(_slot)
            delete _slot;

        _slot = 0;
    }

    template <typename... Args>
    void trigger(Args... args) {
        if(_slot)
            _slot->trigger(args...);
    }

    signal_container<simple_object*, FuncDecl> *_slot;
};



template <typename FuncDecl>
class multi_signal
{
public:


    typedef signal_container<simple_object*, FuncDecl> template_container;
    typename std::list<signal_container<simple_object*, FuncDecl>*>::iterator iterator;

    typedef decltype(iterator) slot;

    ~multi_signal() {
        clear();
    }

    void clear()
    {
        for(template_container * _slot : _slots )
            delete _slot;

        _slots.clear();
    }



    template <typename t>
    auto connect( t func ) -> decltype(iterator)
    {
        _slots.push_back( new template_container(func) );
        return (--_slots.end());
    }

    template <class Obj, typename Func>
    auto connect(Obj obj, Func func ) -> decltype(iterator)
    {
        _slots.push_back((template_container *)new signal_container<Obj, FuncDecl>(obj, func));
        return (--_slots.end());
    }

    template <class Iterator>
    void disconnect(Iterator it) {
        signal_container<simple_object*, FuncDecl> *obj = (*it);
        _slots.erase(it);
        delete obj;
    }

    template <typename... Args>
    void trigger(Args... args) {

        for(template_container * slot : _slots )
            slot->trigger(args...);
    }

    std::list<signal_container<simple_object*, FuncDecl> *> _slots;
};


} // signal_slot


#endif // SIGNAL_H
