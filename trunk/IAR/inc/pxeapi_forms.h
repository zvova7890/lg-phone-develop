#ifndef __PXEAPI_FORMS_H__
#define __PXEAPI_FORMS_H__

/* *****************************************************************************

 � ���� ����� ������������ API ��� ������ � �������, ��������� � LG KP501 V10H_00.
 ������� � ���������:
  ������ ����� aka Dimadze

***************************************************************************** */

//�������������� ����� �������
#define CreateForm                  Forms_Create
#define DestroyForm                 Forms_Destroy
#define SetFormPosition             Forms_SetPosition
#define SetFormTitleText            Forms_SetTitleText
#define SetFormTitleFont            Forms_SetTitleFont
#define SetFormTitleHeight          Forms_SetTitleHeight
#define SetFormSoftKeys             Forms_SetSoftKeys
#define SetFormCreateList           Forms_CreateList
#define SetFormListStyle            Forms_SetListStyle
#define AddFormListItem             Forms_AddListItem
#define GetSelectFormListItem       Forms_GetSelectListItem
#define FormTouchHandling           Forms_TouchHandling
#define FormTouchHandling2          Forms_TouchHandling2
#define FormTouchHandling3          Forms_TouchHandling3


/* ************************************************************************** */


#define FORM_TITLE_FONT_NORMAL    24
#define FORM_TITLE_HEIGHT_NORMAL  42

//�������� �����
__pxeapi int Forms_Create()
__pxe_api_ret_noargs(0x88/4, 0x00/4, int)

//����������� �����
__pxeapi int Forms_Destroy(int form_handle)
__pxe_api_ret_onearg(0x88/4, 0x04/4, int, form_handle)

//������������ ������� �����
__pxeapi int Forms_SetPosition(int form_handle, short x, short y)
__pxe_api_ret(0x90/4, 0x10/4, int, form_handle, x, y)

//������������ ��������� �����
__pxeapi int Forms_SetTitleText(int form_handle, const unsigned short *title)
__pxe_api_ret(0x90/4, 0x2C/4, int, form_handle, title)

//������������ ������ ��������� �����
__pxeapi int Forms_SetTitleFont(int form_handle, unsigned char font)
__pxe_api_ret(0x90/4, 0x30/4, int, form_handle, font)

//������������ ������ ��������� �����
__pxeapi int Forms_SetTitleHeight(int form_handle, int height)
__pxe_api_ret(0x90/4, 0x34/4, int, form_handle, height)

//������������ ����-������ � ����� (�� 3-�) 
__pxeapi int Forms_SetSoftKeys(int form_handle, const unsigned  short *soft1, const unsigned short *soft2, const unsigned short *soft3)
__pxe_api_ret(0x88/4, 0x60/4, int, form_handle, soft1, soft2, soft3)

//�������� ������ � �����
__pxeapi int Forms_CreateList(int form_handle, int arg1, int arg2, int arg3, int arg4, int arg5)
__pxe_api_ret(0x88/4, 0x34/4, int, form_handle, arg1, arg2, arg3, arg4, arg5);

//��������� ����� ������
__pxeapi int Forms_SetListStyle(int list_handle, int arg1, int style)
__pxe_api_ret(0x90/4, 0x08/4, int, list_handle, arg1, style)

//���������� ������ �������� � ������
__pxeapi int Forms_AddListItem(int list_handle, const unsigned short *name, int item_id, int arg_FFFF)
__pxe_api_ret(0xB0/4, 0x78/4, int, list_handle, name, item_id, arg_FFFF);

//��������� ���������� �������� � ������
__pxeapi int Forms_GetSelectListItem(int list_handle)
__pxe_api_ret_onearg(0xB0/4, 0x58/4, int, list_handle);

//���������� ������ � ������� ��������� #1
__pxeapi int Forms_TouchHandling(int form_handle, int arg_0)
__pxe_api_ret(0x74/4, 0xB4/4, int, form_handle, arg_0)

//���������� ������ � ������� ��������� #2
__pxeapi int Forms_TouchHandling2(int form_handle, int action, int arg_0)
__pxe_api_ret(0x74/4, 0xB8/4, int, form_handle, action, arg_0)

//���������� ������ � ������� ��������� #3
__pxeapi int Forms_TouchHandling3(int form_handle, int action, int x, int y, int arg_4)
__pxe_api_ret(0x74/4, 0xC4/4, int, form_handle, action, x, y, arg_4)

#endif // __PXEAPI_FORMS_H__


