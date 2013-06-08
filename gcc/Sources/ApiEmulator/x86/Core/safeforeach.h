#ifndef SAFEFOREACH_H
#define SAFEFOREACH_H


template <typename T>
class SafeForeachContainer
{
public:

  SafeForeachContainer(T &t) :
    type(t)
  {
    it = type.begin();
    inext = it++;
  }


  bool isEnd() const {
    return inext == type.end();
  }


  void operator ++() {

    if(it != type.end())
      inext = it++;
    else
      inext = it;
  }


  void toEnd() {
    inext = type.end();
  }

  typename T::iterator iterator() {
    return inext;
  }


  typename T::iterator it, inext;
  T &type;
};


template <typename T>
class SafeRevertForeachContainer
{
public:

  SafeRevertForeachContainer(T &t) :
    type(t)
  {
    it = type.rbegin();
    inext = it++;
  }


  bool isEnd() const {
    return inext == type.rend();
  }


  void operator ++() {
    if(it != type.rend()) {
      inext = it++;
    } else {
      inext = it;
    }
  }

  void toEnd() {
    inext = type.rend();
  }

  typename T::reverse_iterator iterator() {
    return inext;
  }


  typename T::reverse_iterator it, inext;
  T &type;
};


#define safe_for_each(type, element, container) \
    for(SafeForeachContainer <__typeof__(container)>__iterator(container); !__iterator.isEnd();  __iterator.toEnd()) \
      for(type element = (*__iterator.iterator()); !__iterator.isEnd(); ++__iterator, element = (*__iterator.iterator()) )



#define safe_revert_for_each(type, element, container) \
    for(SafeRevertForeachContainer <__typeof__(container)>__iterator(container); !__iterator.isEnd();  __iterator.toEnd()) \
      for(type element = (*__iterator.iterator()); !__iterator.isEnd(); ++__iterator, element = (*__iterator.iterator()) )



#endif // SAFEFOREACH_H
