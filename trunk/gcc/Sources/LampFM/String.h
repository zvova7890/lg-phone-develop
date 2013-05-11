#ifndef STRING_H
#define STRING_H

#include <functional>
#include <list>


class String
{
public:
    String();
    String(int reserve);
    String(const String &);
    String(const String *);
    String(const char *, bool copy = false);

    ~String();


    String operator +(const String &);
    String operator +(const char *);
    String operator +(int);

    String & operator +=(const String &);
    String & operator +=(const char *);
    String & operator +=(int);

    String & operator =(const String &);
    String & operator =(const char *);

    static String from(int );
    static String copy(const String &str);

    char *data();

    int length() const {
        return m_length;
    }

    bool isEmpty() const {
        return m_length == 0;
    }

    const char *constData() const {
        return m_data;
    }

protected:
    void updateLength();
    void reparentToNext(char act = 0);
    void free();
    void ref(const String &);
    void unref(bool clear = false);
    void incrementSize(int );
    void modify(bool clear = false);

    std::list<String*>::iterator push(const String *s) {
        m_myRefs.push_back((String*)s);
        return (--m_myRefs.end());
    }

    void pop(const String *s) {
        if(m_refed)
            m_myRefs.erase(s->m_listId);
    }

private:
    String *m_parent;

    mutable std::list<String*> m_myRefs;
    std::list<String*>::iterator m_listId;

    char *m_data;
    //int m_size;
    int m_length;

    bool m_refed;
    bool m_dataConstant;
};

#endif // STRING_H
