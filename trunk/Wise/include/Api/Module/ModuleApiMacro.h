#ifndef __MODULEAPIMACRO_H__
#define __MODULEAPIMACRO_H__


#define __mapi static inline

//Непосредственный вызов функции по адресу
#define __mapi_adr_imm_noargs(adr)                ((int (*)())((adr)))()
#define __mapi_adr_imm_onearg(adr, arg)           ((int (*)(int))((adr)))((int)arg)
#define __mapi_adr_imm(adr, arg0, ...)            ((int (*)(int, ...))((adr)))((int)arg0, __VA_ARGS__)

//Определение функции по адресу для вызова
#define __mapi_adr_void_noargs(adr)               { ((void (*)())((adr)))(); }
#define __mapi_adr_void_onearg(adr, arg)          { ((void (*)(int))((adr)))((int)arg); }
#define __mapi_adr_void(adr, arg0, ...)           { ((void (*)(int, ...))((adr)))((int)arg0, __VA_ARGS__); }

//Определение функции по адресу для вызова с возвратным значением
#define __mapi_adr_ret_noargs(adr, ret)           { return ((ret (*)())((adr)))(); }
#define __mapi_adr_ret_onearg(adr, ret, arg)      { return ((ret (*)(int))((adr)))((int)arg); }
#define __mapi_adr_ret(adr, ret, arg0, ...)       { return ((ret (*)(int, ...))((adr)))((int)arg0, __VA_ARGS__); }


#endif // __MODULEAPIMACRO_H__

