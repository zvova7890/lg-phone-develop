#ifndef __PXEAPI_MACRO_H__
#define __PXEAPI_MACRO_H__

#define PXEAPI_BASE 0x400000
#define PXEAPI ((unsigned int **)PXEAPI_BASE)

#define __pxeapi static inline

//Непосредственный вызов функции по адресу
#define __pxe_adr_imm_noargs(adr)                ((int (*)())((adr)))()
#define __pxe_adr_imm_onearg(adr, arg)           ((int (*)(int))((adr)))((int)arg)
#define __pxe_adr_imm(adr, arg0, ...)            ((int (*)(int, ...))((adr)))((int)arg0, __VA_ARGS__)

//Определение функции по адресу для вызова
#define __pxe_adr_void_noargs(adr)               { ((void (*)())((adr)))(); }
#define __pxe_adr_void_onearg(adr, arg)          { ((void (*)(int))((adr)))((int)arg); }
#define __pxe_adr_void(adr, arg0, ...)           { ((void (*)(int, ...))((adr)))((int)arg0, __VA_ARGS__); }

//Определение функции по адресу для вызова с возвратным значением
#define __pxe_adr_ret_noargs(adr, ret)           { return ((ret (*)())((adr)))(); }
#define __pxe_adr_ret_onearg(adr, ret, arg)      { return ((ret (*)(int))((adr)))((int)arg); }
#define __pxe_adr_ret(adr, ret, arg0, ...)       { return ((ret (*)(int, ...))((adr)))((int)arg0, __VA_ARGS__); }

//Непосредственный вызов функции из PXE API
#define __pxe_api_imm_noargs(gid, fid)           ((int (*)())((PXEAPI[gid][fid])))()
#define __pxe_api_imm_onearg(gid, fid, arg)      ((int (*)(int))((PXEAPI[gid][fid])))((int)arg)
#define __pxe_api_imm(gid, fid, arg0, ...)       ((int (*)(int, ...))((PXEAPI[gid][fid])))((int)arg0, __VA_ARGS__)

//Определение функции PXE API для вызова
#define __pxe_api_void_noargs(gid, fid)          { ((void (*)())((PXEAPI[gid][fid])))(); }
#define __pxe_api_void_onearg(gid, fid, arg)     { ((void (*)(int))((PXEAPI[gid][fid])))((int)arg); }
#define __pxe_api_void(gid, fid, arg0, ...)      { ((void (*)(int, ...))((PXEAPI[gid][fid])))((int)arg0, __VA_ARGS__); }

//Определение функции PXE API для вызова с возвратным значением
#define __pxe_api_ret_noargs(gid, fid, ret)      { return ((ret (*)())((PXEAPI[gid][fid])))(); }
#define __pxe_api_ret_onearg(gid, fid, ret, arg) { return ((ret (*)(int))((PXEAPI[gid][fid])))((int)arg); }
#define __pxe_api_ret(gid, fid, ret, arg0, ...)  { return ((ret (*)(int, ...))((PXEAPI[gid][fid])))((int)arg0, __VA_ARGS__); }

#define PXE_LOWORD(w) ( w >>  0) & 0xFFFF
#define PXE_HIWORD(w) ( w >> 16) & 0xFFFF

#endif // __PXEAPI_MACRO_H__

