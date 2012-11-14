#ifndef __PXEAPI_KPDCTRL_H__
#define __PXEAPI_KPDCTRL_H__

__pxeapi int pxeapi_kpdctrl_isvisible(int arg0)
__pxe_api_ret_onearg(0x74/4, 0x64/4, int, arg0)

__pxeapi int pxeapi_kpdctrl_getstate(int arg0)
__pxe_api_ret_onearg(0x74/4, 0x60/4, int, arg0)


#endif // __PXEAPI_KPDCTRL_H__


