
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "String.h"



String::String() :
    m_data(0),
    //m_size(0),
    m_length(0),
    m_refed(false),
    m_dataConstant(false)
{

}


String::String(int reserve) :
    m_data(new char[reserve]),
    //m_size(reserve),
    m_length(0),
    m_refed(false),
    m_dataConstant(false)
{

}


String::String(const String &s) :
    m_data(0),
    //m_size(0),
    m_length(0),
    m_refed(false),
    m_dataConstant(false)
{
    ref(s);
}


String::String(const String *s) :
    m_data(0),
    //m_size(0),
    m_length(0),
    m_refed(false),
    m_dataConstant(false)
{
    ref(*s);
}


String::String(const char *s, bool copy) :
    m_parent(0),
    m_refed(!copy)
{
    m_length = strlen(s);

    if(m_refed) {
        m_data = (char *)s;
        m_dataConstant = true;
        //m_size = m_length;

    } else {
        m_dataConstant = false;
        m_data = new char[m_length + 1];
        printf("data = new char\n");

        //m_size = m_length;

        memcpy(m_data, s, m_length);
        m_data[m_length] = 0;
    }
}


String::~String()
{
    reparentToNext(0);
    free();
}



void String::reparentToNext(char act)
{
    if(!m_myRefs.empty())
    {
        // make reparent
        String *new_p = *m_myRefs.begin();

        if(m_refed) {
            if(m_parent)
                m_parent->pop(this);

            m_refed = false;

            if(m_parent)
                m_parent->push(new_p);

            m_parent = 0;

        } else
            new_p->m_parent = 0;

        if(act == 0) {
            m_length = 0;
            m_data = 0;
            //m_size = 0;
        }

        if(act == 1) {
            auto save = m_data;
            m_data = new char[m_length+1];
            printf("data = new char\n");

            memcpy(m_data, save, m_length);
            m_data[m_length] = 0;
        }

        new_p->m_dataConstant = m_dataConstant;

        new_p->m_refed = false;
        auto i = ++m_myRefs.begin();

        std::list<String*>::iterator last_it;
        bool is_empty = true;

        for(; i != m_myRefs.end(); ++i) {
            if(!is_empty)
                m_myRefs.erase(last_it);

            String *str = (*i);

            // reparent child
            new_p->m_myRefs.push_back(str);

            // set new child parent
            str->m_parent = new_p;
            str->m_data = new_p->m_data;
            str->m_dataConstant = new_p->m_dataConstant;

            // set new list id
            str->m_listId = (--new_p->m_myRefs.end());


            last_it = i;
            is_empty = false;
        }

        m_myRefs.clear();
    }
}



void String::free()
{
    if(m_refed) {
        if(m_parent)
            m_parent->pop(this);
    } else {

        if(m_length && !m_dataConstant) {
            printf("delete data\n");
            delete m_data;
        }
    }

    m_data = 0;
    m_refed = false;
    m_length = 0;
    //m_size = 0;
}

void String::ref(const String &s)
{
    String::free();

    m_listId = ((String &)s).push(this);
    m_data = s.m_data;
    m_refed = true;
    m_length = s.m_length;
    //m_size = s.m_size;
    m_parent = (String*)&s;
}


void String::unref(bool clear)
{
    if(m_refed) {

        if(clear) {
            m_length = 0;
            m_data = 0;
            //m_size = 0;

        } else {

            auto save = m_data;
            m_data = new char[m_length+1];
            printf("data = new char\n");

            memcpy(m_data, save, m_length);
            m_data[m_length] = 0;
        }

        m_refed = false;

        if(m_parent)
            m_parent->pop(this);
    }
}


void String::modify(bool clear)
{
    (void) clear;
    reparentToNext(1);
}


void String::updateLength()
{
    m_length = strlen(m_data);
}


char *String::data()
{
    modify(false);
    return m_data;
}


String String::from(int v)
{
    String data(24);

    sprintf(data.data(), "%d", v);

    data.updateLength();

    return data;
}


String String::copy(const String &str)
{
    String s;

    s.m_refed = 0;
    s.m_length = str.m_length;
    s.m_data = new char[s.m_length];
    printf("data = new char\n");

    memcpy(s.m_data, str.m_data, s.m_length);
    return s;
}


String & String::operator =(const String &s)
{
    modify(true);

    ref(s);
    return *this;
}


String & String::operator =(const char *s)
{
    modify();

    m_length = strlen(s);
    m_data = new char[m_length+1];
    printf("data = new char\n");

    memcpy(m_data, s, m_length);
    m_data[m_length] = 0;
    return *this;
}


String String::operator +(const String &s)
{
    String str(this);

    /*if(m_refed) {

        m_data = new char[m_length + s.length()];

        memcpy(m_data, m_parent->m_data, m_length);
        memcpy(m_data+m_length, s.m_data, s.length());


        m_length += s.length();

        m_parent->pop(this);
    } else {

        m_data = (char*)realloc(m_data, m_length + s.length());
        memcpy(m_data+m_length, s.m_data, s.length());

        m_length += s.length();
    }*/

    str += s;
    return str;
}


String String::operator +(const char *s)
{
    String str(this);
    str += s;
    return str;
}


String String::operator +(int v)
{
    String str(this);
    str += v;
    return str;
}

void String::incrementSize(int add)
{
    reparentToNext(2);


    if(m_refed) {

        auto save = m_data;
        m_data = new char[m_length + add + 1];
        printf("data = new char\n");

        memcpy(m_data, save, m_length);

        if(m_parent)
            m_parent->pop(this);

        m_refed = false;
    } else {

        if(m_dataConstant) {

            auto save = m_data;
            m_data = new char[m_length + add + 1];
            printf("data = new char\n");

            memcpy(m_data, save, m_length);
            m_dataConstant = false;

        } else {
            m_data = (char*)realloc(m_data, m_length + add);
        }
    }
}


String &String::operator +=(const String &s)
{
    int len = s.length();

    incrementSize(len);

    memcpy(m_data+m_length, s.constData(), len);
    m_length += len;

    m_data[m_length] = 0;
    return *this;
}


String &String::operator +=(const char *str)
{
    int len = strlen(str);

    incrementSize(len);

    memcpy(m_data+m_length, str, len);
    m_length += len;

    m_data[m_length] = 0;
    return *this;
}


String &String::operator +=(int v)
{
    operator +=(from(v));
    return *this;
}
