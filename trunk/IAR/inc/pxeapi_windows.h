#ifndef __PXEAPI_WINDOWS_H__
#define __PXEAPI_WINDOWS_H__

/* *****************************************************************************

 � ���� ����� ������������ API ��� ������ � ������, ��������� � LG KP501 V10H_00.
 ������� � ���������:
  ������ ����� aka Dimadze

***************************************************************************** */

//�������������� ����� �������

/* ************************************************************************** */


//�������� ����
__pxeapi int Windows_Create(int window_id, int (*evt_handler)(int cmd, int subcmd, int status))
__pxe_api_ret(0x48/4, 0x18/4, int, window_id, evt_handler)

//������������� ���� (������� ������� �������������)
__pxeapi int Windows_Init(int window_id)
__pxe_api_ret_onearg(0x48/4, 0x1C/4, int, window_id)

//����������� ���� ���� ����������
__pxeapi int Windows_DestroyAll()
__pxe_api_ret_noargs(0x48/4, 0x14/4, int)

//��������������� ������� ���������� � ����
__pxeapi int Windows_TransEvent(int cmd, int subcmd, int status)
__pxe_api_ret(0x48/4, 0x0C/4, int, cmd, subcmd, status)

//�������� ������� � ����
__pxeapi int Windows_SendEvent(int window_id, int cmd, int subcmd, int status)
__pxe_api_ret(0x48/4, 0x00/4, int, window_id, cmd, subcmd, status)

//������ ����
__pxeapi int Windows_Run(int window_id)
__pxe_api_ret_onearg(0x48/4, 0x24/4, int, window_id)

#endif // __PXEAPI_WINDOWS_H__


