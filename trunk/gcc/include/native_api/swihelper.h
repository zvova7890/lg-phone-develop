
#ifndef __SWI_HELPER_H__
#define __SWI_HELPER_H__

#ifdef __cplusplus
extern "C" const int __switab[];
#else
extern const int __switab[];
#endif



#ifdef __cplusplus

#define __pdef(point, ret, ...)  { \
    ((ret (*)(...))point)(__VA_ARGS__); }


#ifndef __NO_DIRECT_SWI
#define __inl static inline __attribute__((unused))
#else
#define __inl inline __attribute__((unused))
#endif

#define __inline inline


#else /*__cplusplus*/


#define __pdef(point, ret, ...)  { \
    ((ret (*)())point)(__VA_ARGS__); }

#ifndef __NO_DIRECT_SWI
#define __inl static inline __attribute__((unused))
#else
#define __inl  __attribute__((unused))
#endif

#define __inline static inline __attribute__((unused))

#endif /*__cplusplus*/


#ifndef __NO_DIRECT_SWI

#ifdef __cplusplus

//#define __def(id, ret, ...) { return ((ret (*)(...))((__switab[id])))(__VA_ARGS__); }
#define __def(id, ret, ...) \
  {\
      if(id >= 0x8000)\
        return (ret)(__switab[id-0x8000]); \
      else\
        return ((ret (*)(...))((__switab[id])))(__VA_ARGS__); \
  }\

#define __defn(id, ...) { ((void (*)(...))((__switab[id])))(__VA_ARGS__); }

#define __cdef(id, ret, ...) (ret)((ret (*)(...))((__switab[id])))(__VA_ARGS__)
#define __cdefn(id, ...) ((void (*)(...))((__switab[id])))(__VA_ARGS__)

#define __nul_def(id, ret) { return ((ret (*)())((__switab[id])))(); }
#define __nul_defn(id) { ((void (*)())((__switab[id])))(); }

#define __def_noinline(id, ret, ...) \
      if(id >= 0x8000)\
        return (ret)(__switab[id-0x8000]); \
      else\
        return ((ret (*)(...))((__switab[id])))(__VA_ARGS__); \

//#define __ldr(id, ret) { return (ret)(__switab[id-0x8000]); }

#else /*__cplusplus*/

//#define __def(id, ret, ...) { return ((ret (*)())((__switab[id])))(__VA_ARGS__); }
#define __def(id, ret, ...) \
  {\
      if(id >= 0x8000)\
        return (ret)(__switab[id-0x8000]); \
      else\
        return ((ret (*)())((__switab[id])))(__VA_ARGS__); \
  }\

#define __defn(id, ...) { ((void (*)())((__switab[id])))(__VA_ARGS__); }

/* использовать для функций типа sprintf, но не юзать для рамных функций! */
#define __cdef(id, ret, ...) (ret)((ret (*)())((__switab[id])))(__VA_ARGS__)
#define __cdefn(id, ...) ((void (*)())((__switab[id])))(__VA_ARGS__)


#define __nul_def(id, ret) { return ((ret (*)())((__switab[id])))(); }

#define __def_noinline(id, ret, ...) \
      if(id >= 0x8000)\
        return (ret)(__switab[id-0x8000]); \
      else\
        return ((ret (*)())((__switab[id])))(__VA_ARGS__); \

#define __nul_defn(id) { ((void (*)())((__switab[id])))(); }

//#define __ldr(id, ret) { return (ret)(__switab[id-0x8000]); }

#endif /*__cplusplus */

#else /*__NO_DIRECT_SWI */


#define __def(id, ret, ...) \
        __attribute__((swi(id)));

#define __defn(id, ...) \
        __attribute__((swi(id)));

#define __nul_def(id, ret) \
        __attribute__((swi(id)));

#define __nul_defn(id) \
        __attribute__((swi(id)));

#endif /*__USE_SWI */


#endif
