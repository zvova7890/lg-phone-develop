#ifndef __PXEAPI_MISC_H__
#define __PXEAPI_MISC_H__

/* *****************************************************************************

 � ���� ����� ������������ PXE API, ��������� � LG KP501 V10H_00.
 ������� � ���������:
  ������ ����� aka Dimadze

***************************************************************************** */

#define FREEZETIMER_PARAM          0
#define FREEZETIMER_ACTION_DISABLE 0
#define FREEZETIMER_ACTION_ENABLE  2

#define TOUCHPAD_SENSITIVITY_DEFAULT 0
#define TOUCHPAD_SENSITIVITY_SET     1

//�������� ����� ��������
__pxeapi int SetUP_GetHandle()
__pxe_api_ret_noargs(0x344/4, 0x15C/4, int)

//��������� ������� �� ������� ��� ��������������, ���� type = TOUCHPAD_SENSITIVITY_SET, �� ������� ����� ��������� 
//������ ����� ���������� sensitivity ��������, ����� ������� �������������� ��������� ��������������
__pxeapi int SetUP_SetTouchpadSensitivity(int handle, unsigned char type, unsigned short sensitivity)
__pxe_api_ret(0x344/4, 0x214/4, int, handle, type, sensitivity)

//������� ����� ��������
__pxeapi void SetUP_CloseHandle(int handle)
__pxe_api_void_onearg(0x344/4, 0x164/4, handle);

//���������� �������� �������� �� IDLE � ������� ���������
__pxeapi int FreezeTimerControl(int param, int state)
__pxe_api_ret(0x13C/4, 0x14/4, int, param, state)

//��������� ������ API �� �����
__pxeapi int *GetAPIByName(const unsigned short *name_api)
__pxe_api_ret_onearg(0x30/4, 0x08/4, int *, name_api)



#endif // __PXEAPI_MISC_H__


